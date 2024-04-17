#pragma once

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

const int bits_in_byte = 8;

template<typename T, size_t N>
class my_array {
public:

    my_array() = default;
    my_array(const my_array& other){
        for (size_t i=0; i<N; i++){
            data[i] = other.data[i];
        }
    }

    T& at(size_t index){
        if (index>=N || index<0){
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    T& operator[](size_t index){
        return data[index];
    }

    const T& at(size_t index) const{
        if (index>=N || index<0){
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    const T& operator[](size_t index) const{
        return data[index];
    }

    bool empty() const{
        return N == 0;
    }
    size_t size() const{
        return N;
    }

    void fill(T val){
        for (size_t i = 0; i< N; i++){
            data[i] = val;
        }
    }

private:
    T data[N]{};
};


class proxy_bool{
public:
    proxy_bool(size_t index, unsigned char& byte): index(index), byte(byte) {}

    operator bool() const{
        return get_bit();
    }
    proxy_bool& operator=(const proxy_bool& other){
        *this = bool(other);
        return *this;
    }

    proxy_bool& operator=(bool value){
        if (value){
            byte |= 1<<index;
        }
        else{
            byte &= ~(1<<index);
        }
        return *this;
    }

private:
    size_t index;
    unsigned char& byte;
    bool get_bit() const{
        return (byte >> index)& 1;
    }
};




template <std::size_t N>
class my_array<bool, N>{
public:
    my_array() = default;

    proxy_bool operator[](std::size_t index){
        return proxy_bool(index%bits_in_byte, data[index/bits_in_byte]);
    }

    proxy_bool at(std::size_t index){
        if (index>=N || index<0){
            throw std::out_of_range("Index out of range.");
        }
        return (*this)[index];
    }

    bool operator[](std::size_t index) const{
        return (data[index/bits_in_byte]>>(index%bits_in_byte))&1;
    }

    bool at(std::size_t index) const{
        if (index>=N || index<0){
            throw std::out_of_range("Index out of range.");
        }
        return (*this)[index];
    }

    bool empty() const{
        return N == 0;
    }
    size_t size() const{
        return N;
    }

    void fill(bool val){
        unsigned char byte_value = !!val;
        for (size_t i = 0; i< (N/bits_in_byte + !!(N%bits_in_byte)); i++){
            data[i] = byte_value;
        }
    }

    friend proxy_bool;

private:
    unsigned char data[N/bits_in_byte + !!(N%bits_in_byte)]{};
};





}  // namespace lab_13

