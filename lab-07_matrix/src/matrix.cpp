#include "matrix.h"
#include <cstdio>
#include <cstddef>

Matrix::Matrix(size_t r, size_t c)
{
	_rows = r;
	_cols = c;
	_data = new int*[_rows];
	for (int i = 0; i<_rows; i++){
		_data[i] = new int[_cols]{0};
	}
}

Matrix::Matrix(const Matrix& m){
	_rows = m._rows;
	_cols = m._cols;
	_data = new int*[_rows];
	for (int i = 0; i<_rows; i++){
		_data[i] = new int[_cols];
	}
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<_cols; j++)
		{
			_data[i][j] = m._data[i][j];
		}
	}
}

Matrix::~Matrix(){
	this->delete_matrix();
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
	m.delete_matrix();
	m._rows = _rows;
	m._cols = _cols;
	m._data = _data;
	_rows = tmp._rows;
	_cols = tmp._cols;
	_data = tmp._data;
	tmp._data = new int*[tmp._rows];
	for (int i = 0; i<tmp._rows; i++){
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

void Matrix::print(FILE *f) const{
	for (int i = 0; i<_rows; i++){
		for (int j = 0; j<_cols; j++){
			if (j==_cols - 1){
				fprintf(f, "%d", _data[i][j]);
			}
			else{
			    fprintf(f, "%d ", _data[i][j]);
			}
		}
		fprintf(f, "\n");
	}
}

Matrix Matrix::operator+(Matrix& m) const{
	Matrix result(_rows, _cols);
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<_cols; j++)
		{
			result._data[i][j] = _data[i][j] + m._data[i][j];
		}
	}
	return result;
}



Matrix Matrix::operator-(Matrix& m) const{
	Matrix tmp(_rows, _cols);
	tmp = -m;
	tmp = (*this) + tmp;
	return tmp;
}

Matrix Matrix::operator*(Matrix& m) const{
	Matrix result(_rows, m._cols);
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<m._cols; j++)
		{
			int val = 0;
			for (int k = 0; k<_cols; k++)
			{
				val += _data[i][k]*m._data[k][j];
			}
			result.set(i, j, val);
		}
	}
	return result;
}

Matrix Matrix::operator-(){
	Matrix result(_rows, _cols);
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<_cols; j++)
		{
			result._data[i][j] = - _data[i][j];
		}
	}
	return result;
}

Matrix& Matrix::operator+=(Matrix& m){
	*this = (*this) + m;
	return *this;
}

Matrix& Matrix::operator-=(Matrix& m){
	*this = (*this) - m;
	return *this;
}

Matrix& Matrix::operator*=(Matrix& m){
	*this = (*this) * m;
	return *this;
}

bool Matrix::operator==(Matrix& m) const{
	if (_rows!= m._rows || _cols!= m._cols){
		return false;
	}
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<_cols; j++)
		{
			if (_data[i][j]!= m._data[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix& m) const{
	return !(this->operator==(m));
}

void Matrix::delete_matrix(){
	for (int i=0; i<_rows; i++)
	{
		delete [] _data[i];
	}
	delete [] _data;
}