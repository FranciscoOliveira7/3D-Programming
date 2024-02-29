#pragma once

#include <iostream>
#include <algorithm> // std::max  std::min
#include "rectangle.h"

namespace my_game {

	class CollisionBox : public Rectangle {
		bool hit_ = false;

	public:
		CollisionBox(float x, float y, float w, float h) : Rectangle(x + w / 2, y + h / 2, w, h) {
			std::cout << "Collision box created";
		}

		void ComputeCollision(CollisionBox other) {
			float x_min = std::min<float>(center_x_ - width_ / 2.0f, other.center_x_ - other.width_ / 2.0f);
			float x_max = std::max<float>(center_x_ + width_ / 2.0f, other.center_x_ + other.width_ / 2.0f);
			float y_min = std::min<float>(center_y_ - height_ / 2.0f, other.center_y_ - other.height_ / 2.0f);
			float y_max = std::max<float>(center_y_ + height_ / 2.0f, other.center_y_ + other.height_ / 2.0f);

			//if (((x_min - x_max) < (width_ - other.width_)) || ((x_min - x_max) < (width_ - other.width_)))
		}
	};
}