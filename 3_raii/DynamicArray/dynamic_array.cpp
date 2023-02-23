#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

class DynamicArray {
private:
    int* _data;
    int* _first;
    size_t _size;
    size_t _capacity;

    void release_memory() {
        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
    }

    void extend()
    {
        if (_size == 0) {
            resize(1);
        }
        else if (_size == 1) {
            resize(2);
        }
        else {
            resize(pow(2, int(log2(_size) + 1)));
        }
    }
public:
    DynamicArray() : _data(nullptr), _first(nullptr), _size(0), _capacity(0) {}

    DynamicArray(int* data, size_t size, size_t capacity = 0) {
        if (capacity == 0 && size > 0) {
            _capacity = pow(2, int(log2(size) + 1));
        }
        else {
            _capacity = capacity;
        }
        _data = new int[_capacity];
        _first = _data;
        _size = std::min(_capacity, size);
        memcpy(_data, data, _size * sizeof(int));
    }

    DynamicArray(size_t size) : DynamicArray() {
        if (size > 0) {
            _capacity = pow(2, int(log2(size) + 1));
            _data = new int[_capacity];
            _first = _data;
            _size = std::min(_capacity, size);
            std::memset(_data, 0, _size * sizeof(int));
        }
    }

    void resize(size_t new_capacity) {
        int* _new_data = new int[new_capacity];
        _capacity = new_capacity;
        _size = std::min(_capacity, _size);
        std::memcpy(_new_data, _data, _size * sizeof(int));
        std::swap(_data, _new_data);
        if (_new_data) {
            delete[] _new_data;
        }
        _first = _data;
    }

    int& operator[] (size_t idx) {
        if (idx > _size) {
            throw std::out_of_range("Idx out of array range");
        }
        return _data[idx];
    }

    void push_back(int item) {
        if (_size == _capacity) {
            extend();
        }
        _data[_size++] = item;
    }

    void pop_back() {
        if (_size == 0) return;
        --_size;

        if (2 * _size <= _capacity) {
            resize(_size);
        }
    }

    void pop_front() {
        if (_size == 0) return;

        --_size;
        int* _new_data = new int[_size];
        std::memcpy(_new_data, _data + 1, _size * sizeof(int));
        std::swap(_data, _new_data);
        if (_new_data) {
            delete[] _new_data;
        }

        if (2 * _size <= _capacity) {
            resize(_size);
        }
    }

    void clear() {
        release_memory();
        _size = 0;
        _capacity = 0;
    }

    size_t get_size() const {
        return _size;
    }

    size_t get_capacity() const {
        return _capacity;
    }

    std::string print() const
    {
        std::string res;
        for (int i = 0; i < _capacity; ++i) {
            res += ((i < _size) ? std::to_string(_data[i]) : "_") + " ";
        }
        return res;
    }

    virtual
        ~DynamicArray() {
        release_memory();
    }
};

std::ostream&
operator<<(std::ostream& os, const DynamicArray& obj)
{
    os << "Array params:" << std::endl
        << "size=" << obj.get_size() << ", capacity=" << obj.get_capacity() << std::endl;

    if (obj.get_capacity()) {
        os << "Array content:" << std::endl
            << obj.print() << std::endl;
    }
    os << std::endl;
    return os;
}

int main() {
    DynamicArray da(3);
    da[1] = 3;
    std::cout << da;

    int a[] = { 1,2,3,4,5,6,7,8,9,10 };
    DynamicArray da2(a, 10);
    std::cout << da2;

    DynamicArray da3(a, 10, 8);
    std::cout << da3;

    da3.resize(20);
    std::cout << da3;

    da3.resize(5);
    std::cout << da3;

    da3.push_back(6);
    std::cout << da3;

    da3.push_back(7);
    da3.push_back(8);
    std::cout << da3;

    da3.push_back(9);
    std::cout << da3;

    da3.pop_back();
    std::cout << da3;

    da3.clear();
    da3.push_back(9);
    da3.pop_back();
    std::cout << da3;

    da3.push_back(1);
    da3.push_back(2);
    da3.push_back(3);
    da3.pop_front();
    std::cout << da3;

    da3.push_back(1);
    da3.push_back(2);
    da3.push_back(3);
    std::cout << da3;
}