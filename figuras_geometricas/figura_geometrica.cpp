#include "figura_geometrica.h"

// Rectangle

Rectangle::Rectangle(float width, float height) : width_{ width }, height_{ height } {}
Rectangle::~Rectangle() {
	std::cout << "Rectangle Destroyed";
}
void Rectangle::Print() {
	std::cout << "Rectangle: area = " << Area() << ", perimeter = " << Perimeter() << std::endl;
}
float Rectangle::Perimeter() {
	return width_ * 2 + height_ * 2;
}
float Rectangle::Area() {
	return width_ * height_;
}

// Circle

Circle::~Circle() {
	std::cout << "Circle Destroyed";
}
void Circle::Print() {
	std::cout << "Circle: area = " << Area() << ", perimeter = " << Perimeter() << std::endl;
}
float Circle::Perimeter() {
	return 2 * 3.14 * radius_;
}
float Circle::Area() {
	return 3.14 * radius_ * radius_;
}