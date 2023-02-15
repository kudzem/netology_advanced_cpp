#include <iostream>
#include <algorithm>
#include <vector>

struct Print
{
    void operator()(int val) { std::cout << val << "\t"; }
};

int main() {
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
    std::for_each(v.begin(), v.end(), [](int& val) { if (val % 2) val *= 3; });
    std::for_each(v.begin(), v.end(), Print());
}