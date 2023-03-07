#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <array>
#include <utility>
#include <functional>

template <typename T>
class CountSymbols {
	std::map<T, size_t> _symbol2quantity;
	std::multimap<size_t, T, std::greater<size_t>> _quantity2symbol;
public:

	CountSymbols() {}

	void operator()(const T& item) {
		++_symbol2quantity[item];
	}

	void Sort() {
		for_each(_symbol2quantity.cbegin(), _symbol2quantity.cend(), [this](const std::pair<T, size_t>& data) {
			_quantity2symbol.insert(std::make_pair(data.second, data.first)); });
		_symbol2quantity.clear();
	}

	void Print() const {
		for (const auto& item : _quantity2symbol) {
			std::cout << item.second << ": " << item.first << std::endl;
		}
	}
};

int main()
{
	CountSymbols<char> c;
	std::string str{ "Hello, World!" };
	c = std::for_each(str.cbegin(), str.cend(), c);
	c = std::for_each(str.cbegin(), str.cend(), c);
	c.Sort();
	c.Print();

	CountSymbols<int> c2;
	std::array<int,10> ints { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
	c2 = std::for_each(ints.cbegin(), ints.cend(), c2);
	c2.Sort();
	c2.Print();

	return 0;
}