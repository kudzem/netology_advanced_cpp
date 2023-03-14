#include "inifile_parser.h"

using namespace netology_course_work;

int main() {

    setlocale(LC_ALL, "Russian");

    try {
        ini_parser parser("../../../config.ini");

        auto value = parser.get_value<int>("Section2.var1");
        if (value) {
            std::cout << *value << std::endl;
        }

        auto value6 = parser.get_value<std::string>("Section1.var2");
        if (value6) {
            std::cout << *value6 << std::endl;
        }

        auto value2 = parser.get_value<double>("Section1.var1");
        if (value2) {
            std::cout << *value2 << std::endl;
        }

        auto value3 = parser.get_value<std::string>("Section1.var3");
        if (value3) {
            std::cout << *value3 << std::endl;
        }

        auto value4 = parser.get_value<bool>("core.ignorecase");
        if (value4) {
            std::cout << std::boolalpha << *value4 << std::endl;
        }

        auto value5 = parser.get_value<bool>("Section4.Mode");
        if (value5) {
            std::cout << *value5 << std::endl;
        }

    }
    catch (FileReadingException e) {
        std::cout << e.what() << std::endl;
    }
    catch (NoValueException e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
}