#pragma once
#include <list>

class BigNum {
	std::list<int> digits;

	BigNum() {}

public:
	//BigNum(int number) {
	//	while (number) {
	//		int digit = number % 10;
	//		digits.push_front(digit);
	//		number /= 10;
	//	}
	//}

	BigNum(const std::string& number) {
		for(auto it = number.rbegin(); it != number.rend(); ++it) {
			int digit = (*it) - 48;
			digits.push_front(digit);
		}
	}

	BigNum(BigNum& other) {
		digits = other.digits;
	}

	BigNum(BigNum&& other) noexcept {
		std::swap(digits, other.digits);
	}

	BigNum operator+(const BigNum& other) {
		BigNum result;
		bool overflow = false;

		auto it2 = other.digits.rbegin();
		for (auto it = digits.rbegin(); it != digits.rend() || it2 != other.digits.rend();)
		{
			int a = (it != digits.rend()) ? *it : 0;
			int b = (it2 != other.digits.rend()) ? *it2 : 0;

			int digit_sum = (a + b + overflow) % 10;
			overflow = (a + b + overflow) > 9;
			result.digits.push_front(digit_sum);

			if (it != digits.rend()) ++it;
			if (it2 != other.digits.rend())	++it2;
		}

		if (overflow) {
			result.digits.push_front(1);
		}

		return result;
	}

	BigNum operator*(int multiplier) {
		BigNum result;

		while (multiplier) {
			result = result + *this;
			--multiplier;
		}

		return result;
	}

	BigNum&
	operator=(BigNum&& other) noexcept {
		digits.clear();
		std::swap(digits, other.digits);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& is, BigNum& num);
};

std::ostream& operator<<(std::ostream& os, BigNum& num) {
	for (auto& digit : num.digits) {
		os << digit;
	}
	return os;
}