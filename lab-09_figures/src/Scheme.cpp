#include "Scheme.hpp"
#include <stdio.h>

Scheme::Scheme(int capacity){
	figures_ = new Figure*[capacity];
	//printf("capacity = %d\n", capacity);
	capacity_ = capacity;
	size_ = 0;
}

Scheme::~Scheme(){
	for (int i=0;i<size_; i++){
		delete figures_[i];
	}
	delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg){
	if (size_+1<=capacity_){
		figures_[size_] = fg;
		size_++;
		//printf("added figure with id %d at index %d\n", fg->getID(),size_-1);
	}
}

void Scheme::remove_figure(int id){
	int i = get_index_by_id(id);
	delete figures_[i];
	//printf("removed figure by id %d\n", id);
	for (int j=i;j<size_;j++){
		figures_[j] = figures_[j+1];
	}
	size_--;
}

void Scheme::print_all_figures(){
	for (int i=0;i<size_; i++){
		figures_[i]->print();
	}
}

void Scheme::zoom_figure(int id, int factor){
	int i = get_index_by_id(id);
	figures_[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y){
	for (int i=0;i<size_; i++){
		if (figures_[i]->is_inside(x, y)){
			return figures_[i];
		}
	}
	return nullptr;
}

void Scheme::move(int id, int new_x, int new_y){
	int i = get_index_by_id(id);
	figures_[i]->move(new_x, new_y);
}

int Scheme::get_index_by_id(int id){
	for (int i=0;i<size_; i++){
		if (figures_[i]->getID() == id){
			return i;
		}
	}
	return -1;
}
