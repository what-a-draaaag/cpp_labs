#include "matrix.hpp"
#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix* obj){
	if (obj!=nullptr){
		storage_ = new Storage(obj);
		storage_->incr();
	}
	else{
		storage_ = nullptr;
	}
}

shared_ptr::shared_ptr(const shared_ptr& other){
	storage_ = other.storage_;
	if (!isNull())
		storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other){
	if (!isNull()){
		storage_->decr();//check and delete
		if (storage_->getCounter()==0){
			storage_->~Storage(); 
		}
	}
	storage_ = other.storage_;
	storage_->incr();
	return *this;
}

shared_ptr::~shared_ptr(){
	if (isNull()) return;
	storage_->decr();//check and delete
	if (storage_->getCounter()==0){
		storage_->~Storage();
	}
}

Matrix* shared_ptr::ptr() const{
	if (isNull()){
		return 0;
	}
	return storage_->getObject();
}

bool shared_ptr::isNull() const{
	return storage_==nullptr;
}

void shared_ptr::reset(Matrix* obj){
	storage_->decr();//check and delete
	if (storage_->getCounter()==0){
		storage_->~Storage();
	}
	if (obj==nullptr){
		storage_ = nullptr;
		return;
	}
	storage_ = new Storage(obj);
	storage_->incr();

}

Matrix* shared_ptr::operator->() const{
	return storage_->getObject();
}
Matrix& shared_ptr::operator*() const{
	return *(storage_->getObject());
}

shared_ptr::Storage::Storage(Matrix* mtx){
	data_ = mtx;
	ref_count_ = 0;
}
shared_ptr::Storage::~Storage(){
	getObject()->~Matrix();
}

void shared_ptr::Storage::incr(){
	ref_count_++;
}
void shared_ptr::Storage::decr(){
	ref_count_--;
}

int shared_ptr::Storage::getCounter() const{
	return ref_count_;
}
Matrix* shared_ptr::Storage::getObject() const {
	return data_;
}


