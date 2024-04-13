#pragma once

#include <cstdio>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>


class Matrix {
public:
  Matrix(size_t r, size_t c);
  Matrix(const Matrix& m);
  ~Matrix();

  Matrix& operator=(const Matrix& m);

  void set(size_t i, size_t j, int val);
  int get(size_t i, size_t j) const;
  void print() const;
  void load(std::string filename);

  Matrix operator+(Matrix& m) const;
  Matrix operator*(Matrix& m) const;

  Matrix& operator+=(Matrix& m);
  Matrix& operator*=(Matrix& m);

  bool operator==(Matrix& m) const;
  bool operator!=(Matrix& m) const; 
private:
  size_t _rows;
  size_t _cols;
  int **_data;
  void delete_matrix();
  void swap(Matrix& m);
  void check_alloc(void* ptr);
};


class MatrixException: public std::exception
{
public:
    MatrixException(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};
