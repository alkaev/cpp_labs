#pragma once

#include <new>
#include <cassert>
#include <iostream>

namespace containers {

    template<typename T>
    my_vector<T>::my_vector() : size_(0), capacity_(1), array_((T*)::operator new(sizeof(T) * capacity_)) {}

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) : size_(n), capacity_(min_power_of_2(n)), array_((T*)::operator new(sizeof(T) * capacity_)) {
        for (size_t i = 0; i < size_; ++i) {
            new (array_ + i) T(); 
        }
    }

    template<typename T>
    my_vector<T>& my_vector<T>::operator=(my_vector other) {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(array_, other.array_);
        return *this;
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T>& other) : size_(other.size_), capacity_(other.capacity_), array_((T*)::operator new(sizeof(T) * capacity_)) {
        for (size_t i = 0; i < size_; ++i) {
            new (array_ + i) T(other[i]); 
        }
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        clear();
        ::operator delete(array_);
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        if constexpr (std::is_default_constructible<T>::value) {  
            if (n > capacity_) {
                reserve(n);
            }
            for (size_t i = size_; i < n; ++i) {
                new (array_ + i) T();
            }
            for (size_t i = n; i < size_; ++i) {
                array_[i].~T();
            }
            size_ = n;
        } else {
            throw std::runtime_error("Type is not DefaultConstructible");
        }
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n > capacity_) {
            size_t new_capacity = min_power_of_2(n);
            T* new_array = (T*)::operator new(sizeof(T) * new_capacity);
            for (size_t i = 0; i < size_; ++i) {
                new (new_array + i) T(std::move(array_[i]));
                array_[i].~T();
            }
            ::operator delete(array_);
            array_ = new_array;
            capacity_ = new_capacity;
        }
    }

    template<typename T>
    void my_vector<T>::push_back(const T& t) {
        if (size_ == capacity_) {
            reserve(2 * capacity_);
        }
        new (array_ + size_) T(t);
        ++size_;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        array_[size_ - 1].~T();
        --size_;
    }

    template<typename T>
    void my_vector<T>::clear() {
        while (size_ > 0) {
            pop_back();
        }
    }

    template<typename T>
    T& my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T& my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    size_t my_vector<T>::min_power_of_2(size_t n) const {
        size_t power = 1;
        while (power < n) {
            power *= 2;
        }
        return power;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const my_vector<T>& v) {
        for (std::size_t i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i < v.size() - 1) {
                os << " ";
            }
        }
        return os;
    }

}
