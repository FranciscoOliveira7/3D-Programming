#pragma once

#include <iostream>

namespace my_game {

	class Rectangle {
	protected:
		float center_x_;
		float center_y_;
		float width_;
		float height_;

	public:
		Rectangle(float cx, float cy, float w, float h) : center_x_{ cx }, center_y_{ cy }, width_{ w }, height_{ h } {
			std::cout << "Rectangle created";
		}
	};
}