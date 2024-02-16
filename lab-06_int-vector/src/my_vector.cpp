#include<algorithm>
#include "my_vector.hpp"

MyVector::MyVector(){
	_size = 0;
	_capacity = 2;
	_data = new int[2];
}

MyVector::MyVector(std::size_t init_capacity){
	_size = 0;
	_capacity = init_capacity;
	_data = new int[init_capacity];
}

MyVector::MyVector(const MyVector& another){
	_size = another._size;
	_capacity = another._capacity;
	_data = new int[_capacity];
	for (int i=0; i<_size; i++)
	{
		_data[i] = another._data[i];
	}
}

MyVector::~MyVector(){
	delete [] _data;
}

MyVector& MyVector::operator=(const MyVector& another){
	_size = another._size;
	_capacity = another._capacity;
	_data = new int[_capacity];
	for (int i=0; i<_size; i++)
	{
		_data[i] = another._data[i];
	}
	return *this;
}

void MyVector::set(std::size_t index, int value){
	if (index<_capacity)
	{
		_data[index] = value;
	}
}

int MyVector::get(std::size_t index){
	if (index<_size)
	{
		return _data[index];
	}
}

std::size_t MyVector::size(){
	return _size;
}

std::size_t MyVector::capacity(){
	return _capacity;
}

void MyVector::reserve(std::size_t new_capacity){
	if (_capacity<new_capacity)
	{
		_capacity = new_capacity;
		int* new_data = new int[new_capacity];
		for (int i = 0; i<_size; i++)
		{
			new_data[i] = _data[i];
		}
		delete [] _data;
		_data = new_data;
	}
}

void MyVector::resize(std::size_t new_size){
	if (new_size<_capacity)
	{
		_size = new_size;
		return;
	}
	_capacity = std::max(new_size, 2*_capacity);
	this->reserve(_capacity);
	_size = new_size;
}

void MyVector::push_back(int value){
	if (_capacity==_size)
	{
		this->reserve(_capacity*2);
		_data[_capacity/2] = value;
	}
	else
	{
		_data[_size] = value;
	}
	_size++;
}

void MyVector::insert(std::size_t index, int value){
	if (index==_capacity)
	{
		this->reserve(_capacity+1);
	}
	for (int i=_size+1; i > index; i--)
	{
		_data[i] = _data[i-1];
	}
	_data[index] = value;
	_size++;
}

void MyVector::erase(std::size_t index){
	for (int i = index + 1; i<_size; i++)
	{
		_data[i-1] = _data[i];
	}
}