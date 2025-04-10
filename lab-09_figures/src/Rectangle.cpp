#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y){
	width_ = width;
	height_ = height;
}
Rectangle::~Rectangle(){}

void Rectangle::print() const{
	printf("Rectangle ");
	Figure::print();
	printf(" width = %d height = %d\n", width_, height_);
}

bool Rectangle::is_inside(int x, int y) const{
	return abs(x-this->x)<= width_/2 && abs(y-this->y)<=height_/2;
}
void Rectangle::zoom(int factor){
	width_*=factor;
	height_*=factor;
}
