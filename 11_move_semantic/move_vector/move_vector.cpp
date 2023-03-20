#include <iostream>
#include <vector>
#include <memory>

class A {

public:
    A(A&& other) {
        std::cout << "Move constructor" << std::endl;
    }

    A(const A& other) = default;

    A(){}
};

template <typename T, typename U=T>
void
move_vectors(std::vector<T>& dest, std::vector<U>& src)
{
    if (&dest == &src) return;

    dest.clear();
    for (auto& item : src) {
        dest.push_back(std::move(item));
    }
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;

    move_vectors(two, one);
    move_vectors(two, two);

    for (auto& item : two) {
        std::cout << item << std::endl;
    }

    //-------------------
    std::vector <A> oneA = { {}, {} };
    std::vector <A> twoA;

    move_vectors(twoA, oneA);

    std::cout << twoA.size() << std::endl;



    return 0;
}