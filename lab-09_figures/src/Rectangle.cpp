#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

Rectangle::~Rectangle() = default;

bool Rectangle::is_inside(int p_x, int p_y) const {
  return (p_x >= x - width / 2 && p_x <= x + width / 2 && p_y >= y - height / 2 && p_y <= y + height / 2);
}

void Rectangle::print() const {
    std::cout << "Rectangle " << id << ": x = " << x << " y = " << y
              << " width = " << width << " height = " << height << std::endl;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}
