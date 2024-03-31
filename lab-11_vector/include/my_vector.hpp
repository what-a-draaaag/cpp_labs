#pragma once

#include <cstddef>
#include <ostream>
#include <cassert>
#include <cstring>
#include <sstream>

namespace containers {

template<typename T>
class my_vector {
public:
    explicit my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector<T>& other);
    my_vector<T>& operator=(const my_vector<T>& other);
    ~my_vector();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T& operator[](std::size_t index);

    void push_back(const T& t);
    void pop_back();
    void clear();

    void copy_array(const my_vector<T>& other);

    template <typename V>
    friend std::ostream& operator<<(std::ostream& out, const my_vector<V>& v);

private:
    size_t _capacity;
    size_t _size;
    T* _array;
};

}

#include "my_vector_impl.hpp"
