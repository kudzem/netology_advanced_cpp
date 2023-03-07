#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

template <class T, int N>
class CountMultiplesOf {
	T _sum;
	size_t _quantity;
public:
	CountMultiplesOf(): _sum(0), _quantity(0) {}

	void operator() (T new_entry) {
		if (std::fmod(new_entry, N) == 0) {
			_sum += new_entry; ++_quantity;
		};
	}

	T get_sum() const { return _sum; }
	size_t get_count() const { return _quantity; }
};

typedef CountMultiplesOf<double, 3> CountMultiplesOf3;
typedef CountMultiplesOf<int, 5> CountMultiplesOf5;

int main() 
{
	CountMultiplesOf3 Mof3;
	std::vector v{ 1,2,3,4,5 };
	std::vector v2{ 11,12,13,14,15 };
	Mof3 = std::for_each(v.cbegin(), v.cend(), Mof3);
	Mof3 = std::for_each(v2.cbegin(), v2.cend(), Mof3);

	std::cout << "Multiples of 3" << std::endl;
	std::cout << "Sum = " << Mof3.get_sum() << std::endl;
	std::cout << "Count = " << Mof3.get_count() << std::endl;

	CountMultiplesOf5 Mof5;
	Mof5 = std::for_each(v.cbegin(), v.cend(), Mof5);
	Mof5 = std::for_each(v2.cbegin(), v2.cend(), Mof5);

	std::cout << "Multiples of 5" << std::endl;
	std::cout << "Sum = " << Mof5.get_sum() << std::endl;
	std::cout << "Count = " << Mof5.get_count() << std::endl;

	return 0;
}