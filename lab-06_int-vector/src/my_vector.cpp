#include "my_vector.hpp"
#include <utility>


MyVector::MyVector() : MyVector(2) {} 

MyVector::MyVector(std::size_t init_capacity) {
    _capacity = init_capacity;
    _size = 0;
    _data = new int[_capacity];
}

MyVector::~MyVector() {
    delete [] _data;
}

void MyVector::set(std::size_t index, int value) {
    while (index + 1 > _capacity) {
        reserve(_capacity * 2);
    }

    _data[index] = value;
};

int MyVector::get(size_t i){   
    return _data[i];
}

size_t MyVector::size(){
    return _size;
}

size_t MyVector::capacity(){
    return _capacity;
}

void MyVector::push_back(int value) {
    set(_size, value);
    _size += 1;
};

void MyVector::insert(std::size_t index, int value) {
    push_back(value);
    if (!_size) 
        return;
    

    for (std::size_t i=_size-1; i > index; i--) {
        _data[i] = _data[i-1];
    }

    _data[index] = value;

};

void MyVector::erase(size_t index){
    for (int i = index; i < (int)_size-1; i++){
        _data[i] = _data[i+1];
    }
    _size--;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }

    MyVector new_vector = MyVector(new_capacity);
    std::swap(_data, new_vector._data);
    std::swap(_capacity, new_vector._capacity);

    for (std::size_t i = 0; i<_size; i++) 
        _data[i] = new_vector._data[i];
    
};

void MyVector::resize(std::size_t new_size) {
    if (new_size > _capacity) 
        reserve(new_size > (2 * _capacity) ? new_size : (2 * _capacity));
    
    for (std::size_t i = _size; i < new_size; i++) 
        _data[i] = 0;
    

    _size = new_size;
};

MyVector::MyVector(const MyVector& another_vector) {

    _capacity = another_vector._capacity;
    _size = another_vector._size;
    _data = new int[_capacity];
    memcpy(_data, another_vector._data, sizeof(int) * _size);
}

MyVector& MyVector::operator=(MyVector other) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_data, other._data);

    return *this;
};






















