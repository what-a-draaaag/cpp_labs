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

}  // namespace lab_13

