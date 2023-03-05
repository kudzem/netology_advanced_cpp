#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

template <class C, class T, int N>
class CountMultiplesOf {
	T _sum;
	size_t _quantity;
public:
	CountMultiplesOf(): _sum(0), _quantity(0) {}

	void operator() (const C & data) {
		std::for_each(data.begin(), data.end(),
			          [this](const auto& item) 
			          { if (item % N == 0) 
		                { _sum += item; ++_quantity; }; 
			          });
	}

	T get_sum() const { return _sum; }
	size_t get_count() const { return _quantity; }
};

typedef CountMultiplesOf<std::vector<int>, double, 3> CountMultiplesOf3;
typedef CountMultiplesOf<std::vector<int>, double, 5> CountMultiplesOf5;

int main() 
{
	CountMultiplesOf3 Mof3;
	std::vector v{ 1,2,3,4,5 };
	std::vector v2{ 11,12,13,14,15 };
	Mof3(v);
	Mof3(v2);

	std::cout << "Sum = " << Mof3.get_sum() << std::endl;
	std::cout << "Count = " << Mof3.get_count() << std::endl;

	CountMultiplesOf5 Mof5;
	Mof5(v);
	Mof5(v2);

	std::cout << "Sum = " << Mof5.get_sum() << std::endl;
	std::cout << "Count = " << Mof5.get_count() << std::endl;

	return 0;
}