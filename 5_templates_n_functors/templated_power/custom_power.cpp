#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
double
custom_pow(const T& v, int e) {
    double res = 1;

    if (e > 0) {
        while (e) {
            res *= v;
            --e;
        };
    }
    else if (e < 0) {
        while (e) {
            res /= v;
            ++e;
        };
    }

    return res;
}

double
custom_pow(bool v, int e) {
    return v;
}

template <typename VT>
std::vector<VT>
custom_pow(const std::vector<VT>& v, int e)
{
    std::vector<VT> res;
    std::transform(v.cbegin(), v.cend(), std::back_inserter(res),
        [e](VT item) { return custom_pow(item, e); });

    return res;
}

int main() {
   std::cout << custom_pow(2,2) << "\n";
   std::cout << custom_pow(2.0, 2) << "\n";
   std::cout << custom_pow(2, -1) << "\n";
   std::cout << custom_pow(2, 0) << "\n";
   std::cout << custom_pow('0', 1) << "\n";

   std::vector<int> v{ -1,2,3 };
   v = custom_pow(v, 3);
   
   for(const auto& item: v) std::cout << item << "\t";
}