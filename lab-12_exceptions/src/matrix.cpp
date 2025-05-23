#include "matrix.h"
#include <cstdio>
#include <cstddef>

Matrix::Matrix(size_t r, size_t c)
{
	_rows = r;
	_cols = c;
	_data = new int[_rows * _cols];
	check_alloc(_data);
}

Matrix::Matrix(const Matrix& m){
	_rows = m._rows;
	_cols = m._cols;
	_data = new int[_rows * _cols];
	check_alloc(_data);
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<_cols; j++)
		{
			_data[i * _cols + j] = m._data[i * _cols + j];
		}
	}
}

void Matrix::check_alloc(void* ptr){
	if (ptr == nullptr){
		throw MatrixException("Unable to allocate memory.");
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
	tmp._data = new int[tmp._rows * tmp._cols];
	check_alloc(tmp._data);
}


void Matrix::set(size_t i, size_t j, int val){
	_data[i * _cols + j] = val;
}

int Matrix::get(size_t i, size_t j) const{
	if (i>=_rows || j >= _cols || i<0 || j<0){
		throw MatrixException("ACCESS: bad index.");
	}
	return _data[i * _cols + j];
}

void Matrix::print() const{
	for (size_t i = 0; i<_rows; i++){
		for (size_t j = 0; j<_cols; j++){
			if (j==_cols - 1){
				std::cout << _data[i * _cols + j];
			}
			else{
			    std::cout << _data[i * _cols + j] << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Matrix::load(std::string filename){
	std::ifstream f(filename);
	if (!f.good()){
		throw MatrixException("LOAD: unable to open file.");
	}
	size_t rows, cols;
	int elem;
	if (!(f >> rows >> cols)){
    	throw MatrixException("LOAD: invalid file format.");
	}
	Matrix tmp(rows, cols);
    for (size_t i = 0; i < tmp._rows; i++){
     	for (size_t j = 0; j < tmp._cols; j++){
	  		if (!(f >> elem)){
	    		throw MatrixException("LOAD: invalid file format.");
	  		}
    		tmp.set(i, j, elem);
    	}
	}
  	*this = tmp;
}

Matrix Matrix::operator+(Matrix& m) const{
	if (_rows!=m._rows || _cols!= m._cols){
		throw MatrixException("ADD: dimensions do not match.");
	}
	Matrix result(_rows, _cols);
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<_cols; j++)
		{
			result._data[i * _cols + j] = _data[i * _cols + j] + m._data[i * _cols + j];
		}
	}
	return result;
}

Matrix Matrix::operator*(Matrix& m) const{
	if (_cols!=m._rows){
		throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
	}
	Matrix result(_rows, m._cols);
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<m._cols; j++)
		{
			int val = 0;
			for (size_t k = 0; k<_cols; k++)
			{
				val += _data[i * _cols + k]*m._data[k * m._cols + j];
			}
			result.set(i, j, val);
		}
	}
	return result;

}

Matrix& Matrix::operator+=(Matrix& m){
	*this = (*this) + m;
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
	for (size_t i=0; i<_rows; i++)
	{
		for (size_t j =0; j<_cols; j++)
		{
			if (_data[i * _cols + j] !=  m._data[i * _cols + j])
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
	delete [] _data;
}



MatrixException::MatrixException(const std::string& message): message{message} {}


const char* MatrixException::what() const noexcept{
    return message.c_str();
}