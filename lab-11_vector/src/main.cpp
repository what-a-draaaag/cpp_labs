#include <iostream>

#include "my_vector_impl.hpp"
#include <cassert>
#include <cstring>
#include <sstream>

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price){
        name_ = new char[strlen(name)+1];
        strcpy(name_, name);
        quantity_ = quantity;
        price_ = price;
    }

    Product(const Product& p){
        name_ = new char[strlen(p.name_)+1];
        strcpy(name_, p.name_);
        quantity_ = p.quantity_;
        price_ = p.price_;
    }

    ~Product(){
        delete [] name_;
    }

    friend std::ostream& operator<<(std::ostream& out, Product p){
        out << p.name_ <<" "<<p.quantity_<<" "<<p.price_;
        return out;
    }
private:
    char *name_;
    int quantity_;
    double price_;
};

void print(const containers::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

} 

template <typename T>
void test_my_vector_default_constructible(const T& arg1, const T& arg2)
{
    containers::my_vector<T> v1(5);
    assert(v1.size() == 5);
    assert(v1.capacity() == 8); 
    v1.resize(29);
    assert(v1.size() == 29);
    assert(v1.capacity() == 32);
}

template <typename T>
void test_my_vector(const T& arg1, const T& arg2)
{
    containers::my_vector<T> v1;
    assert(v1.capacity() == 2);
    assert(v1.size() == 0);
    v1.push_back(arg1);
    assert(v1.capacity() == 2);
    assert(v1.size() == 1);
    std::stringstream ss1, ss2;
    ss1 << v1;
    const char* s1 = ss1.str().c_str();
    ss2 << arg1;
    const char* s2 = ss2.str().c_str();
    assert(strcmp(s1, s2) == 0);
    v1.push_back(arg1);
    v1.push_back(arg2);
    v1.push_back(arg1);
    v1.pop_back();
    assert(v1.size() == 3);
    assert(v1.capacity() == 4);
    containers::my_vector<T> v2;
    v2 = v1;    
    assert(v2.size() == 3);
    assert(v2.capacity() == 4);
    v1.clear();
    assert(v1.size() == 0);
    assert(v1.capacity() == 4);
    v2.reserve(17);
    assert(v2.size() == 3);
    assert(v2.capacity() == 32);
    v1.reserve(6);
    assert(v1.capacity() == 8);
    assert(v1.size() == 0);

}

int main() {
    test_my_vector_default_constructible<int>(5,10);
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    return 0;
}
