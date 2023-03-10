#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <variant>
#include <optional>

namespace netology_course_work
{
    class FileReadingException : std::exception {

        std::string _filename;
        std::string _error;
    public:
        FileReadingException(const std::string& filename, 
                             const std::string& error) : _filename(filename), 
                                                         _error(error) {}

        std::string what() {
            return "Can't open config file " + _filename + ": " + _error;
        }
    };

    class NoValueException : std::exception {

        std::string _section;
        std::string _param;
    public:
        NoValueException(const std::string& section,
            const std::string& param) : _section(section),
            _param(param) {}

        std::string what() {
            return "Param " + _section + "." + _param + " has no value";
        }
    };

    bool is_integer(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }

    bool is_number(const std::string& s) {
        return std::regex_match(s, std::regex(("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?")));
    }

    class inifile_line_formatter {
    public:

        static
        void clean_spaces_in_line(std::string& line) {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        }

        static
        void remove_comments_in_line(std::string& line) {
            auto comment_start_pos = std::find(line.cbegin(), line.cend(), ';');
            if (comment_start_pos != line.cend()) {
                line.erase(comment_start_pos, line.end());
            }
        }

        static inline void ltrim(std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
                }));
        }

        // trim from end (in place)
        static inline void rtrim(std::string& s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
                }).base(), s.end());
        }

        // trim from both ends (in place)
        static inline void trim(std::string& s) {
            rtrim(s);
            ltrim(s);
        }
    };

    class ini_parser {
        std::map<std::string, std::map<std::string, std::variant<int, double, std::string, bool>>> config;

        void
        read_config_file(const std::string& filename,
                         std::vector<std::string>& config_lines) const
        {
            std::ifstream fin(filename);

            if (!fin.is_open()) {
                throw FileReadingException(filename, strerror(errno));
            }

            for (std::string line; std::getline(fin, line); ) {
                config_lines.push_back(line);
            }

            fin.close();
        }

        bool find_and_save_section(std::string& line, std::string& current_section) {
            if (line[0] == '[' && *line.rbegin() == ']') {
                current_section = std::string(line.cbegin() + 1, line.cend() - 1);

                inifile_line_formatter::clean_spaces_in_line(current_section);
                if (config.find(current_section) == config.end()) {

                    //std::cout << "Section=`" << current_section << "`" << std::endl;
                    config[current_section] = {};
                }
                return true;
            }
            return false;
        }

        std::optional<std::pair< std::string, std::string>>
        find_parameter(std::string& line, const std::string& current_section) {
            auto equal_pos = std::find(line.cbegin(), line.cend(), '=');
            if (equal_pos != line.cend()) {
                std::string prm_name(line.cbegin(), equal_pos);
                inifile_line_formatter::clean_spaces_in_line(prm_name);

                std::string prm_value(line, std::distance(line.cbegin(), equal_pos + 1));

                inifile_line_formatter::trim(prm_value);

                return make_pair(prm_name, prm_value);
            }

            return std::nullopt;
        }

        void
        save_parameter(std::pair<std::string, std::string>& prm, const std::string& current_section) {

            std::string prm_name(prm.first);
            std::string prm_value(prm.second);

            //std::cout << "Prm=`" << prm_name <<  "`, value=`" << prm_value << "`" << std::endl;

            if (prm.second == "true") {
                config[current_section][prm_name] = true;
            }
            else if (prm_value == "false") {
                config[current_section][prm_name] = false;
            }
            else if (is_integer(prm_value)) {
                config[current_section][prm_name] = std::stoi(prm_value);
            }
            else if (is_number(prm_value)) {
                config[current_section][prm_name] = std::stod(prm_value);
            }
            else {
                config[current_section][prm_name] = prm_value;
            }
        }

        void
        parse_config(std::vector<std::string>& config_lines)
        {
            std::string current_section = "global";
            config[current_section] = {};

            for (auto& line : config_lines) {

                inifile_line_formatter::remove_comments_in_line(line);

                if (line.empty()) { 
                    continue;
                }
                
                auto prm = find_parameter(line, current_section);
                if (prm) {
                    save_parameter(*prm, current_section);
                    continue;
                }

                find_and_save_section(line, current_section);
            }
        }

    public:
        template <typename T>
        std::optional<T>
            get_value(std::string section_prm) const {
            auto dot_pos = std::find(section_prm.cbegin(), section_prm.cend(), '.');
            if (dot_pos != section_prm.cend()) {

                std::string section_name(section_prm.cbegin(), dot_pos);
                std::string prm_name(section_prm, std::distance(section_prm.cbegin(), dot_pos + 1));

                auto section = config.find(section_name);
                if (section != config.end()) {
                    auto prm = section->second.find(prm_name);
                    if (prm != section->second.end()) {

                        auto value = std::get_if<std::string>(&prm->second);
                        if (value && *value == "") {
                            throw NoValueException(section_name, prm_name);
                        }

                        return std::get<T>(prm->second);
                    }
                }
            }
            return std::nullopt;
        }

        ini_parser(const std::string& filename) {
            std::vector<std::string> config_lines;
            read_config_file(filename, config_lines);
            parse_config(config_lines);
        }
    };

}