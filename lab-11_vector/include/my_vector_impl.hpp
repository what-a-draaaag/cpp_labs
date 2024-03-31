#pragma once

#include "my_vector.hpp"
#include <ostream>
#include <cstddef>
#include <cassert>
#include <cstring>
#include <sstream>

namespace containers{



int make_capacity(int num){
    if (num <= 1)
      return num;
    num = (num << 1) - 1;
    unsigned int log = 0;
    while (num >>= 1)
      log++;
    return 1 << log;
}

template<typename T>
my_vector<T>::my_vector(){
    _size = 0;
    _capacity = 2;
    _array = (T*)(new char[2*sizeof(T)]);
}

template<typename T>
my_vector<T>::my_vector(std::size_t n){
    _size = n;
    _capacity = make_capacity(n);
    _array = (T*)(new char[_capacity*sizeof(T)]);
    for (size_t i=0; i<_size; i++){
        new (_array+i) T();
    }
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T>& other){
    _size = other._size;
    _capacity = make_capacity(other._size);
    copy_array(other);
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other){
    delete [] (char*)_array;
    _size = other._size; //copy
    _capacity = make_capacity(other._size);
    copy_array(other);
    return *this;
}

template<typename T>
void my_vector<T>::copy_array(const my_vector<T>& other){
    _array = (T*)(new char[_capacity*sizeof(T)]);
    for (size_t i=0; i<other._size; i++){
        new (_array+i) T(other._array[i]);
    }
}

template<typename T>
my_vector<T>::~my_vector(){
    delete [] (char*)_array;
}

template<typename T>
std::size_t my_vector<T>::size() const{
    return _size;
}
template<typename T>
std::size_t my_vector<T>::capacity() const{
    return _capacity;
}
template<typename T>
bool my_vector<T>::empty() const{
    return _size==0;
}

template <typename T>
void my_vector<T>::resize(std::size_t n){
    if (n<_size)
    {
        for (size_t i=n; i<_size;i++){
            _array[i].~T();
        }
        _size = n;
        return;
    }
    int new_capacity = make_capacity(n);
    reserve(new_capacity);
    for (size_t i = _size; i<n; i++)
    {
        new (_array+i) T();//bug??
    }
    _size = n;

}


template <typename T>
void my_vector<T>::reserve(std::size_t n){
    n = make_capacity(n);
    if (_capacity<n)
    {
        T* new_array = (T*)(new char[n*sizeof(T)]);
        for (size_t i = 0; i<_size; i++)
        {
            new (new_array+i) T(_array[i]);
            _array[i].~T();
        }
        delete [] (char*)_array;
        _array = new_array;
        _capacity = n;
    }

}

template <typename T>
T& my_vector<T>::operator[](std::size_t index){
    return _array[index];
}

template <typename T>
void my_vector<T>::push_back(const T& t){
    if (_size==_capacity){
        reserve(make_capacity(_size+1));
    }
    new (_array+_size) T(t);
    _size++;
}

template <typename T>
void my_vector<T>::pop_back(){
    if (_size==0) return;
    _array[_size-1].~T();
    _size--;
}

template <typename T>
void my_vector<T>::clear(){
    for (size_t i=0; i<_size; i++){
        _array[i].~T();
    }
    _size=0;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& v){
    for (size_t i=0; i<v._size; i++){
        out << v._array[i] << " ";
    }
    out << std::endl;
    return out;
}
}