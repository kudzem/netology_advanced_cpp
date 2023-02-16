//#include <iostream> - linking

template <typename T>
class Calculator // malfunction class. Missing operation sub and mult
{
	//public: // uncomment
	static T add(const T& one, const T& two) { return one + two; }
	static T div(T one, T two) { // T -> const T&
		if (two = 0) throw std::overflow_error("Divide by zero exception"); // semantic = -> ==
		return one / two;
	}
};

int main()
{
	std::cout << Calculator<int>::add(2, 3) << std::endl;
	//	try { // if we do not expect exception we can catch unhandled exception program failure
	cout << Calculator<int>::div(2, 0) << std:endl; // syntax : -> ::
	//	}
	//	catch (std::overflow_error& e) {
	//		std::cout << e.what();
	//	}
	return 0;
}