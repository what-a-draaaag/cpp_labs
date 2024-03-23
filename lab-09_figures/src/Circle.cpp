#include "Circle.hpp"


Circle::Circle(int id, int x, int y, int radius, const char* label): Figure(id, x, y){
	radius_= radius;
	label_ = label;
}
Circle::~Circle(){}

void Circle::print() const{
	printf("Circle ");
	Figure::print();
	printf(" radius = %d label = %s\n", radius_, label_.c_str());
}
bool Circle::is_inside(int x, int y) const{
	return sqrt(pow(abs(x-this->x),2)+ pow(abs(y-this->y),2))<=radius_;
}
void Circle::zoom(int factor){
	radius_*=factor;
}
