#include <iostream>
#include <vector>
#include <memory>


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

    return 0;
}