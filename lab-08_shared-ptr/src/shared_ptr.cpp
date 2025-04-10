#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix* obj){
	if (obj!=nullptr){
		storage_ = new Storage(obj);
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
	decrAndCheck();
	storage_ = other.storage_;
	storage_->incr();
	return *this;
}

void shared_ptr::decrAndCheck(){
	if (!isNull()){
		storage_->decr();
		if (storage_->getCounter()==0){
			delete storage_;
		}
	}
}

shared_ptr::~shared_ptr(){
	decrAndCheck();
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
	decrAndCheck();
	if (obj==nullptr){
		storage_ = nullptr;
		return;
	}
	storage_ = new Storage(obj);

}

Matrix* shared_ptr::operator->() const{
	return storage_->getObject();
}
Matrix& shared_ptr::operator*() const{
	return *(storage_->getObject());
}

shared_ptr::Storage::Storage(Matrix* mtx){
	data_ = mtx;
	ref_count_ = 1;
}
shared_ptr::Storage::~Storage(){
	delete data_;
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


