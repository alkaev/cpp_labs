#include <iostream>
#include "my_vector.hpp"
#include <cassert> 
#include <cstring>

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price)
        : name_(new char[strlen(name) + 1]), quantity_(quantity), price_(price) {
        strcpy(name_, name);
    }

    Product(const Product& other)
        : name_(new char[strlen(other.name_) + 1]), quantity_(other.quantity_), price_(other.price_) {
        strcpy(name_, other.name_);
    }

    bool operator==(const Product& other) const {
        return (quantity_ == other.quantity_ && price_ == other.price_ &&
                strcmp(name_, other.name_) == 0);
    }

    ~Product() {
        delete[] name_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << p.name_ << " " << p.quantity_ << " " << p.price_;
        return os;
    }

private:
    char* name_;
    int quantity_;
    double price_;
};

}  

template<typename T>
void test_my_vector(const T& first_value, const T& second_value) {
    using namespace containers;

    my_vector<T> vec;
    assert(vec.empty());
    assert(vec.size() == 0);
    assert(vec.capacity() == 1);

    vec.push_back(first_value);
    assert(!vec.empty());
    assert(vec.size() == 1);
    assert(vec[0] == first_value);

    vec.push_back(second_value);
    assert(vec.size() == 2);
    assert(vec[1] == second_value);

    my_vector<T> vec_copy = vec;
    assert(vec_copy.size() == vec.size());
    assert(vec_copy[0] == vec[0]);
    assert(vec_copy[1] == vec[1]);

    my_vector<T> vec_assigned;
    vec_assigned = vec;
    assert(vec_assigned.size() == vec.size());
    assert(vec_assigned[0] == vec[0]);
    assert(vec_assigned[1] == vec[1]);

    vec.pop_back();
    assert(vec.size() == 1);
    assert(vec[0] == first_value);

    vec.clear();
    assert(vec.empty());
    assert(vec.size() == 0);
}

template<typename T>
void test_my_vector_default_constructible() {
    using namespace containers;
    my_vector<T> vec(5);  
    assert(vec.size() == 5);

    vec.resize(10);
    assert(vec.size() == 10);

    vec.resize(3);
    assert(vec.size() == 3);

    vec.reserve(20);
    assert(vec.capacity() >= 20);
}

int main() {
    using namespace containers;
    using namespace product;

    test_my_vector<int>(5, 10);
    test_my_vector_default_constructible<int>();

    Product p1("Product1", 5, 10.0);
    Product p2("Product2", 3, 15.5);
    test_my_vector<Product>(p1, p2);

    return 0;
}
