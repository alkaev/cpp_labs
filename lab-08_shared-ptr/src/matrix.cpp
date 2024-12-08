#include "matrix.hpp"
#include <utility>
#include <cstring>
#include <functional>
#include <iostream>
#include <algorithm> 

Matrix::Matrix(std::size_t rows, std::size_t cols){
    _rows = rows;
    _cols = cols;
    if (_rows * _cols == 0)
        return;
    _data = new int*[_rows];
    for (size_t i = 0; i < _rows; i++) {
        _data[i] = new int[_cols]();
    }
}


Matrix::Matrix(const Matrix& m) {
    _rows = m._rows;
    _cols = m._cols;

    if(_rows * _cols == 0) 
        return;  
    
    _data = new int*[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
        
    for (size_t i = 0; i < _rows; i++){
        for(size_t j = 0; j < _cols; j++){
            _data[i][j] = m._data[i][j];
        }
    }
}


Matrix::~Matrix() {
    for (size_t i = 0; i < _rows; i++) {
        delete [] _data[i];
    }
    delete [] _data;
}

std::size_t Matrix::get_rows() const { 
    return _rows; 
}

std::size_t Matrix::get_cols() const { 
    return _cols; 
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& m) const {
    if(_rows != m._rows ||  _cols != m._cols)
        return false;
    for (size_t i = 0; i < m._rows; i++){
        for(size_t j = 0; j < m._cols; j++){
            if (_data[i][j] != m._data[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}


