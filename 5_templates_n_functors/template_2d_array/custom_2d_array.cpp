#include <iostream>

template <class T>
class Table {
	size_t _rows, _cols;
	T** data;
public:
	Table(size_t rows, size_t cols) : _rows(rows), _cols(cols), data(nullptr)
	{
		data = new T*[rows];
		for (size_t r = 0; r < _rows; ++r) {
			data[r] = new T[cols];
		}
	}

	~Table() {
		if (!data) return;
		for (size_t r = 0; r < _rows; ++r) {
			if (data[r]) delete [] data[r];
		}
		delete[] data;
		data = nullptr;
	}

	T* operator[](size_t idx) { return data[idx]; }
	const T* operator[](size_t idx) const { return data[idx]; }

	size_t size() const { return _rows * _cols; }
};

int main() {
	Table<int> t(2, 3);
	t[0][0] = 3;
	std::cout << t[0][0] << std::endl;
	std::cout << t.size() << std::endl;
}