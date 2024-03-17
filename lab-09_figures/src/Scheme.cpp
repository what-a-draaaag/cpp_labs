#include "Scheme.hpp"
#include <stdio.h>

Scheme::Scheme(int capacity){
	figures_ = new Figure*[capacity];
	printf("capacity = %d\n", capacity);
	capacity_ = capacity;
	size = 0;
}

Scheme::~Scheme(){
	for (int i=0;i<size; i++){
		delete figures_[i];
	}
	delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg){
	if (size+1<=capacity_){
		figures_[size] = fg;
		size++;
		printf("added figure with id %d at index %d\n", fg->getID(),size-1);
	}
}

void Scheme::remove_figure(int id){
	for (int i=0;i<size; i++){
		if (figures_[i]->getID() == id){
			delete figures_[i];
			printf("added figure by id %d\n", id);
			size--;
			for (int j=i;j<size;j++){
				figures_[j] = figures_[j+1];
			}
		}
	}
}

void Scheme::print_all_figures(){
	for (int i=0;i<size; i++){
		figures_[i]->print();
	}
}

void Scheme::zoom_figure(int id, int factor){
	for (int i=0;i<size; i++){
		if (figures_[i]->getID() == id){
			figures_[i]->zoom(factor);
		}
	}
}

Figure* Scheme::is_inside_figure(int x, int y){
	for (int i=0;i<size; i++){
		if (figures_[i]->is_inside(x, y)){
			return figures_[i];
		}
	}
	return nullptr;
}

void Scheme::move(int id, int new_x, int new_y){
	for (int i=0;i<size; i++){
		if (figures_[i]->getID() == id){
			figures_[i]->move(new_x, new_y);
		}
	}
}
