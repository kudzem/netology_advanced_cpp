#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>

std::set<std::string> test_set = { "one", "two", "three", "four" };
std::list<std::string> test_list = { "one", "two", "three", "four" };
std::vector<std::string> test_vector = { "one", "two", "three", "four" };

template<class ForwardIt>
void print_container(ForwardIt first, ForwardIt end) {
	for (ForwardIt it = first; it != end; ++it) {
		std::cout << *it << std::endl;
	}
}

int main()
{
	print_container(test_set.begin(), test_set.end());
	print_container(test_list.cbegin(), test_list.cend());
	print_container(test_vector.rbegin(), test_vector.rend());
	return 0;
}