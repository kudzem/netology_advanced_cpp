#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#include <functional>

class CountSymbols {
	std::map<char, size_t> _symbol2quantity;
	std::multimap<size_t, char, std::greater<size_t>> _quantity2symbol;
public:

	CountSymbols(const std::string& str) {
		for_each(str.cbegin(), str.cend(), [this](char symbol) { ++_symbol2quantity[symbol]; });
		for_each(_symbol2quantity.cbegin(), _symbol2quantity.cend(), [this](const std::pair<char,size_t>& data) {
			_quantity2symbol.insert(std::make_pair(data.second, data.first)); });
	}

	void Print() const {
		for (const auto& item : _quantity2symbol) {
			std::cout << item.second << ": " << item.first << std::endl;
		}
	}

};

int main()
{
	CountSymbols c("Hello, World!");
	c.Print();

	return 0;
}