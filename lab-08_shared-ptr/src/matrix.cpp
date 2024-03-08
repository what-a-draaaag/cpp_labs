#include "matrix.hpp"
#include <cstdio>
#include <cstddef>

Matrix::Matrix(size_t r, size_t c)
{
	_rows = r;
	_cols = c;
	_data = new int*[_rows];
	for (size_t i = 0; i<_rows; i++){
		_data[i] = new int[_cols]{0};
	}
}

Matrix::Matrix(const Matrix& m){
	_rows = m._rows;
	_cols = m._cols;
	_data = new int*[_rows];
	for (size_t i = 0; i<_rows; i++){
		_data[i] = new int[_cols];
	}
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<_cols; j++)
		{
			_data[i][j] = m._data[i][j];
		}
	}
}

Matrix::~Matrix(){
	for (size_t i=0; i<_rows; i++)
	{
		delete [] _data[i];
	}
	delete [] _data;
}

Matrix& Matrix::operator=(const Matrix& m){
	if (this == &m){
		return *this;
	}
	Matrix n(m);
	swap(n);
	return *this;

}

void Matrix::swap(Matrix& m){
	Matrix tmp(m);
	for (size_t i=0; i<m._rows; i++)
	{
		delete [] m._data[i];
	}
	delete [] m._data;
	m._rows = _rows;
	m._cols = _cols;
	m._data = _data;
	_rows = tmp._rows;
	_cols = tmp._cols;
	_data = tmp._data;
	tmp._data = new int*[tmp._rows];
	for (size_t i = 0; i<tmp._rows; i++){
		tmp._data[i] = new int[tmp._cols];
	}
}


size_t Matrix::get_rows() const{
	return _rows;
}

size_t Matrix::get_cols() const{
	return _cols;
}

void Matrix::set(size_t i, size_t j, int val){
	_data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const{
	return _data[i][j];
}

bool Matrix::operator==(const Matrix& m) const{
	if (_rows!= m._rows || _cols!= m._cols){
		return false;
	}
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<_cols; j++)
		{
			if (_data[i][j]!= m._data[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& m) const{
	return !(this->operator==(m));
}