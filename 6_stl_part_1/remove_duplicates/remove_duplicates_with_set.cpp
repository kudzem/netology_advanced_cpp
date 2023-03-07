#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <array>
#include <vector>

template <typename T>
class RemoveDuplicates {
	std::set<T, std::greater<T>> uniq_entries;
public:

	RemoveDuplicates() {}

	void operator()(T new_entry) {
		uniq_entries.insert(new_entry);
	}

	void Print() const {
		for (const auto& item : uniq_entries) {
			std::cout << item << std::endl;
		}
	}

};

int main()
{
	RemoveDuplicates <char> rd;
	std::string s("Hello, World!");
	rd = for_each(s.cbegin(), s.cend(), rd);
	rd.Print();

	RemoveDuplicates <int> rd2;
	std::array<int, 5> input_data = { 1, -2, 3, -4, 5 };
	rd2 = for_each(input_data.cbegin(), input_data.cend(), rd2);
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

	RemoveDuplicates <int> rd3;
	rd3 = for_each(user_data.cbegin(), user_data.cend(), rd3);
	std::cout << "Your data unique items:" << std::endl;
	rd3.Print();

	return 0;
}