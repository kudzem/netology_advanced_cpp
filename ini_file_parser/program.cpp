#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

class ini_parser {
    //std::map<std::string<std::map<std::string, std::variant<int,double,std::string>>
    std::map<std::string, std::map<std::string, std::string>> config;

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

    void
    analyze_lines(std::vector<std::string>& content)
    {
        std::string current_section = "global";
        config[current_section] = {};

        for (auto& line : content) {

            // clean spaces
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            // remove comments
            auto comment_start_pos = std::find(line.cbegin(), line.cend(), ';');
            if (comment_start_pos != line.cend()) {
                line.erase(comment_start_pos, line.end());
            }

            // skip empty lines
            if (line.empty()) { continue; }

            // detect section
            if (line[0] == '[' && *line.rbegin() == ']') {
                current_section = std::string(line.cbegin() + 1, line.cend() - 1);
                config[current_section] = {};
                std::cout << "Add section " << current_section << std::endl;
            }

            // detect variable and value
            auto equal_pos = std::find(line.cbegin(), line.cend(), '=');
            if (equal_pos != line.cend()) {
                std::string prm_name(line.cbegin(), equal_pos);
                std::string prm_value(line, std::distance(line.cbegin(), equal_pos + 1));

                config[current_section][prm_name] = prm_value;
                std::cout << "Add prm=" << prm_name << ", val=" << prm_value << std::endl;
                line.erase(comment_start_pos, line.end());
            }
        }
    }

public:
    template <typename T>
    T get_value(std::string section_prm) {
        auto dot_pos = std::find(section_prm.cbegin(), section_prm.cend(), '.');
        if (dot_pos != section_prm.cend()) {

            std::string section_name(section_prm.cbegin(), dot_pos);
            std::string prm_name(section_prm, std::distance(section_prm.cbegin(), dot_pos + 1));

            auto section = config.find(section_name);
            if (section != config.end()) {
                std::cout << "Found section" << std::endl;
                auto prm = section->second.find(prm_name);
                std::cout << "Look for prm " << prm_name << std::endl;
                if (prm != section->second.end()) {
                    std::cout << "Found " << section_prm << std::endl;
                    return prm->second;
                }
            }
        }
        return "";
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
    auto value = parser.get_value<std::string>("Section2.var1");

    std::cout << value;
}