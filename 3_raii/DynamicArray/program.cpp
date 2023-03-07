#include "dynamic_array.h"

int main() {
    DynamicArray<int> da(3);
    da[1] = 3;
    std::cout << da;

    DynamicArray<int> dada(da);
    dada[0] = 5;
    dada = da;
    std::cout << dada;


    int a[] = { 1,2,3,4,5,6,7,8,9,10 };
    DynamicArray<int> da2(a, 10);
    std::cout << da2;

    DynamicArray<int> da3(a, 10, 8);
    std::cout << da3;

    da3.resize(20);
    std::cout << da3;

    da3.resize(5);
    std::cout << da3;

    da3.push_back(6);
    std::cout << da3;

    da3.push_back(7);
    da3.push_back(8);
    std::cout << da3;

    da3.push_back(9);
    std::cout << da3;

    da3.pop_back();
    std::cout << da3;

    da3.clear();
    da3.push_back(9);
    da3.pop_back();
    std::cout << da3;

    da3.push_back(1);
    da3.push_back(2);
    da3.push_back(3);
    da3.pop_front();
    std::cout << da3;

    da3.push_back(1);
    da3.push_back(2);
    da3.push_back(3);
    std::cout << da3;


}