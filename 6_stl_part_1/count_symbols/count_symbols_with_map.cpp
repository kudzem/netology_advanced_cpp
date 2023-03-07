#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <functional>

class CountSymbols {
	std::map<char, size_t> _symbol2quantity;
	std::map<size_t, std::list<char>, std::greater<size_t>> _quantity2symbol;
public:

	CountSymbols(const std::string& str) {
		for_each(str.cbegin(), str.cend(), [this](char symbol) { ++_symbol2quantity[symbol]; });
		for_each(_symbol2quantity.cbegin(), _symbol2quantity.cend(), [this](const std::pair<char,size_t>& data) {
			_quantity2symbol[data.second].push_back(data.first); });
	}

	void Print() const {
		for (const auto& item : _quantity2symbol) {
			for (const auto& symbol : item.second) {
				std::cout << symbol << ": " << item.first << std::endl;
			}
		}
	}

};

int main()
{
	CountSymbols c("Hello, World!");
	c.Print();

	return 0;
}