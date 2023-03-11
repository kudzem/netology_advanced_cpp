#include "inifile_parser.h"

using namespace netology_course_work;

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