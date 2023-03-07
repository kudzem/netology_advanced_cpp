#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <array>
#include <vector>

template <typename C, typename T>
class RemoveDuplicates {
	std::set<T, std::greater<T>> uniq_numbers;
public:

	RemoveDuplicates(const C& source) {
		for_each(source.cbegin(), source.cend(), [this](auto item) { uniq_numbers.insert(item); });
	}

	void Print() const {
		for (const auto& item : uniq_numbers) {
			std::cout << item << std::endl;
		}
	}

};

int main()
{
	RemoveDuplicates <std::string, char> rd("Hello, World!");
	rd.Print();

	std::array<int, 5> input_data = { 1, -2, 3, -4, 5 };
	RemoveDuplicates <std::array<int,5>, int> rd2(input_data);
	rd2.Print();

	size_t user_data_size = 0;
	std::cout << "Let's remove duplicates from your integer data" << std::endl;
	std::cout << "Enter data size" << std::endl;
	std::cin >> user_data_size;

	std::vector<int> user_data;
	user_data.resize(user_data_size);

	while (user_data_size) {
		std::cout << "Enter new data item[" << user_data_size - 1 << "]" << std::endl;
		std::cin >> user_data[user_data_size-1];
		--user_data_size;
	}

	RemoveDuplicates <std::vector<int>, int> rd3(user_data);
	std::cout << "Your data unique items:" << std::endl;
	rd3.Print();

	return 0;
}