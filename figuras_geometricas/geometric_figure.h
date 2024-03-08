#pragma once

#include <iostream>

namespace geometric_figure {

	constexpr float kPi = 3.141592f;

	class GeometricFigure {
	public:
		GeometricFigure() {}
		virtual ~GeometricFigure() {}
		virtual float Perimeter() = 0;
		virtual float Area() = 0;
		virtual void Print() = 0;
	};

	class Rectangle : public GeometricFigure {
	public:
		Rectangle(int w = 0, int h = 0) : width_{ w }, height_{ h } {
			std::cout << "Rectangle Created\n";
		}
		~Rectangle();
		void Print();
		float Perimeter();
		float Area();
		Rectangle operator+(Rectangle);
	private:
		int width_;
		int height_;
	};

	class Circle : public GeometricFigure {
	public:
		Circle(int r = 0) : radius_{ r } {
			std::cout << "Circle Created\n";
		}
		~Circle();
		void Print();
		float Perimeter();
		float Area();
	private:
		int radius_;
	};
}
