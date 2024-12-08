#include "Circle.hpp"
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <iostream> 

Circle::Circle(int id, int x, int y, int radius, const char* label): Figure{id, x, y}, radius{radius} {
    assert(label != nullptr);
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
};

Circle::~Circle() {
    delete [] label;
};

void Circle::print() const {
    std::cout << "Circle " << id << ": x = " << x << " y = " << y
              << " radius = " << radius << " label = " << label << std::endl;
}

bool Circle::is_inside(int x, int y) const {
    return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2)) <= radius;
};

void Circle::zoom(int factor) {
    radius *= factor;
}
