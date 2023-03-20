#include <iostream>
#include "big_num.h"


int main()
{
    BigNum bn("512345512345512345512345512345");
    BigNum other(std::move(bn));

    BigNum yet_another("0");
    yet_another = std::move(other);
    std::cout << yet_another << std::endl;

    BigNum sum = yet_another + yet_another + BigNum("11111111111111111111111111111111");
    std::cout << sum << std::endl;

    BigNum twice = yet_another * 500;
    std::cout << twice << std::endl;

    return 0;
}