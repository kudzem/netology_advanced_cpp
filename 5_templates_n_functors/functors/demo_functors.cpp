#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

template <class C, class T>
class Summator {
public:
	T operator() (const C& data) {
		return std::accumulate(data.begin(), data.end(), 0);
	}
};

template <class C>
class Summator<C, std::string> {
public:
	std::string operator() (const C& data) {
		std::string str_sum;
		std::for_each(data.begin(), data.end(), [&str_sum](auto str) { str_sum += str + " "; });
		return str_sum;
	}
};

template <class C>
class Counter {
public:
	size_t operator() (const C& data) {
		return data.size();
	}
};

int main() {
  {
	Summator<std::vector<int>, double> get_sum;
	std::vector v{ 1,2,3,4,5 };
	std::cout << "Sum = " << get_sum(v) << std::endl;

	Counter<std::vector<int>> get_count;
	std::cout << "Count = " << get_count(v) << std::endl;
  }

  {
	Summator<std::vector<std::string>, std::string> get_sum;
	std::vector<std::string> v{ "Hello", ",", "World" , "!!!"};
	std::cout << get_sum(v);
  }
}