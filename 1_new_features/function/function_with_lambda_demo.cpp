#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <functional>
#include <vector>

std::function<double(const double&)> rad_to_degree([](const double& rads) {
    return rads / M_PI * 180;
    });

std::function<double(const double&)> mysin([](const double& rads) {
    return sin(rads);
    });

std::function<double(const double&)> mytan([](const double& rads) {
    return tan(rads);
    });

std::vector<std::function<double(const double&)>> functions{ rad_to_degree, mysin, mytan };

int main() {

    std::vector<double> angles{ 0.523599, 1.0472, 1.5708, 3.14159, 6.28319 };
    for (const auto& angle : angles) {
        std::cout << angle << ":\t";
        for (const auto& f : functions)
            std::cout << f(angle) << "\t\t";
        std::cout << std::endl;
    }
}