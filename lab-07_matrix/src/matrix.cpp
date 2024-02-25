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
	this->delete_matrix();
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
	return *this;

}

size_t Matrix::get_rows(){
	return _rows;
}

size_t Matrix::get_cols(){
	return _cols;
}

void Matrix::set(size_t i, size_t j, int val){
	_data[i][j] = val;
}

int Matrix::get(size_t i, size_t j){
	return _data[i][j];
}

void Matrix::print(FILE *f){
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

Matrix Matrix::operator+(Matrix& m){
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



Matrix Matrix::operator-(Matrix& m){
	Matrix result(_rows, _cols);
	for (int i=0; i<_rows; i++)
	{
		for (int j =0; j<_cols; j++)
		{
			result._data[i][j] = _data[i][j] - m._data[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(Matrix& m){
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

bool Matrix::operator==(Matrix& m){
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

bool Matrix::operator!=(Matrix& m){
	return !(this->operator==(m));
}

void Matrix::delete_matrix(){
	for (int i=0; i<_rows; i++)
	{
		delete [] _data[i];
	}
	delete [] _data;
}