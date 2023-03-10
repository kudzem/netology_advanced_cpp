#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void make_vector_uniq(std::vector<T>& v) {
	std::sort(v.begin(), v.end());
	auto last = std::unique(v.begin(), v.end());
	v.erase(last, v.end());
}

int main()
{
	std::vector<int> ints { 1, 5, 2, 4, 3, 3, 4, 1, 4, 5 };
	make_vector_uniq(ints);

	for (auto i : ints) {
		std::cout << i << std::endl;
	}

	return 0;
}