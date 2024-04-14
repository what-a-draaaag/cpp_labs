#pragma once

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:

    my_array() = default;
    my_array(const my_array& other){
        for (int i=0; i<N; i++){
            data[i] = other.data[i];
        }
    }

    T& at(std::size_t index){
        if (index>=N){
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    T& operator[](std::size_t index){
        return data[index];
    }

    const T& at(std::size_t index) const{
        if (index>=N){
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    const T& operator[](std::size_t index) const{
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
    proxy_bool(int index, char& byte): index(index), byte(byte) {}

    operator bool() const{
        if (byte>>index){
            return 1;
        }
        return 0;
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
    int index;
    char& byte;
};



/*
template <std::size_t N>
class my_array<bool, N>{
public:
    my_array() = default;

    my_array(const my_array& other){
        for (int i=0; i<N; i++){
            data[i] = other.data[i];
        }
    }

    proxy_bool operator[](std::size_t index){
        return proxy_bool(index%8, data[index/8]);
    }

    proxy_bool at(std::size_t index){
        if (index>=N){
            throw std::out_of_range("Index out of range.");
        }
        return (*this)[index];
    }

    bool operator[](std::size_t index) const{
        return (data[index/8]>>index)?1:0;
    }

    bool at(std::size_t index) const{
        if (index>=N){
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
        for (size_t i = 0; i< N/8; i++){
            data[i] = val? -1 : 0;
        }
    }

    friend proxy_bool;

private:
    char data[N/8 + (N%8)/8]{};
};


*/


}  // namespace lab_13

