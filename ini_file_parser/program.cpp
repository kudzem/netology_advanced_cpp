#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <variant>
#include <optional>

bool is_integer(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool is_number(const std::string& s) {
    return std::regex_match(s, std::regex(("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?")));
}

class ini_parser {
    std::map<std::string, std::map<std::string, std::variant<int, double, std::string>>> config;

    void
    load_file(const std::string& filename,
              std::vector<std::string>& content)
    {
        std::ifstream fin(filename);

        if (!fin.is_open()) {
            std::cout << "Can't open config file " << filename << std::endl;
            std::cerr << "Error: " << strerror(errno);
            return;
        }

        for (std::string line; std::getline(fin, line); )
        {
            content.push_back(line);
        }

        fin.close();
    }

    void clean_spaces_in_line(std::string& line) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    }

    void remove_comments_in_line(std::string& line) {
        auto comment_start_pos = std::find(line.cbegin(), line.cend(), ';');
        if (comment_start_pos != line.cend()) {
            line.erase(comment_start_pos, line.end());
        }
    }

    void find_section(std::string& line, std::string& current_section) {
        if (line[0] == '[' && *line.rbegin() == ']') {
            current_section = std::string(line.cbegin() + 1, line.cend() - 1);
            if (config.find(current_section) == config.end()) {
                config[current_section] = {};
            }
            std::cout << "Add section " << current_section << std::endl;
        }
    }

    void find_parameter(std::string& line, const std::string& current_section) {
        auto equal_pos = std::find(line.cbegin(), line.cend(), '=');
        if (equal_pos != line.cend()) {
            std::string prm_name(line.cbegin(), equal_pos);
            std::string prm_value(line, std::distance(line.cbegin(), equal_pos + 1));

            config[current_section][prm_name] = prm_value;
            std::cout << "Add prm=" << prm_name << ", val=" << prm_value << std::endl;

            if (is_integer(prm_value)) {
                std::cout << "Integer" << std::endl;
                config[current_section][prm_name] = std::stoi(prm_value);
            }
            else if (is_number(prm_value)) {
                std::cout << "Double" << std::endl;
                config[current_section][prm_name] = std::stod(prm_value);
            }
            else {
                std::cout << "String" << std::endl;
                config[current_section][prm_name] = prm_value;
            }
        }

    }

    void
    analyze_lines(std::vector<std::string>& content)
    {
        std::string current_section = "global";
        config[current_section] = {};

        for (auto& line : content) {

            clean_spaces_in_line(line);
            remove_comments_in_line(line);

            if (line.empty()) { continue; }

            find_section(line, current_section);

            find_parameter(line, current_section);
        }
    }

public:
    template <typename T>
    std::optional<T>
    get_value(std::string section_prm) {
        auto dot_pos = std::find(section_prm.cbegin(), section_prm.cend(), '.');
        if (dot_pos != section_prm.cend()) {

            std::string section_name(section_prm.cbegin(), dot_pos);
            std::string prm_name(section_prm, std::distance(section_prm.cbegin(), dot_pos + 1));

            auto section = config.find(section_name);
            if (section != config.end()) {
                auto prm = section->second.find(prm_name);
                if (prm != section->second.end()) {
                    return std::get<T>(prm->second);
                }
            }
        }
        return std::nullopt;
    }

    ini_parser(const std::string& filename) {
        std::vector<std::string> content;
        load_file(filename, content);
        analyze_lines(content);
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    ini_parser parser("../../../config.ini");
    auto value = parser.get_value<int>("Section2.var1");
    if (value) {
        std::cout << *value;
    }

    auto value2 = parser.get_value<double>("Section1.var1");
    if (value2) {
        std::cout << *value2;
    }
    auto value3 = parser.get_value<std::string>("Section1.var3");
    if (value3) {
        std::cout << *value3;
    }
}