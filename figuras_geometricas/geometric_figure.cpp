#include "geometric_figure.h"

namespace geometric_figure {

	// Rectangle

	Rectangle::~Rectangle() {
		std::cout << "Rectangle Destroyed\n";
	}
	void Rectangle::Print() {
		std::cout << "Rectangle: area = " << Area() << " | perimeter = " << Perimeter() << std::endl;
	}
	float Rectangle::Perimeter() {
		return width_ * 2 + height_ * 2;
	}
	float Rectangle::Area() {
		return width_ * height_;
	}
	Rectangle Rectangle::operator+(Rectangle rhs) {
		Rectangle rectangle;

		rectangle.width_ = width_ + rhs.width_;
		rectangle.height_ = height_ + rhs.height_;

		return rectangle;
	}

	// Circle

	Circle::~Circle() {
		std::cout << "Circle Destroyed\n";
	}
	void Circle::Print() {
		std::cout << "Circle: area = " << Area() << " | perimeter = " << Perimeter() << std::endl;
	}
	float Circle::Perimeter() {
		return 2 * 3.14 * radius_;
	}
	float Circle::Area() {
		return 3.14 * radius_ * radius_;
	}
}