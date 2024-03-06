#pragma once

#include <iostream>

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
	 ~Rectangle() {}
	 void Print();
	 float Perimeter();
	 float Area();
 private:
	 int width_;
	 int height_;
};

class Circle : public GeometricFigure {
 public:
	~Circle() {}
	void Print();
	float Perimeter();
	float Area();
 private:
	int radius_;
};