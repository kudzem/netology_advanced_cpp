#include <iostream>
#include <algorithm>
#include <vector>

struct Print
{
    void operator()(int val) { std::cout << val << "\t"; }
};

int main() {
    std::vector<int> v{ 1,2,3,4,5,6,7,8 };
    std::for_each(v.begin(), v.end(), [](int& val) { if (val % 2) val *= 3; });
    std::for_each(v.begin(), v.end(), Print());
    std::cout << std::endl;

    //auto f{ [&]() mutable { v.push_back(-1); } };
    //f();

    //int low = 4, high = 6;
    //int cnt = count_if(v.begin(), v.end(), [&low, high](int& v)
    //    { return v >= low && v <= high; });
    //std::cout << cnt << std::endl;

    //std::for_each(v.begin(), v.end(), Print());

    //auto mymod{ [](const int& a) -> double { if (a < 0) return 0.0; return a; } };
    //std::cout << mymod(-4) << std::endl;

}