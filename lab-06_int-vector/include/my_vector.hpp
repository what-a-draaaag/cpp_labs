#pragma once

#include <cstddef>

class MyVector {
public:
    MyVector();
    MyVector(std::size_t init_capacity);
    MyVector(const MyVector& another);
    ~MyVector();

    MyVector& operator=(const MyVector& another);

    void set(std::size_t index, int value);
    int get(std::size_t index);

    std::size_t size();
    std::size_t capacity();

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);

private:
    std::size_t _size, _capacity;
    int * _data;
};
