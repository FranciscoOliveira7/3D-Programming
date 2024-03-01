#pragma once

#include <iostream>
#include <algorithm> // std::max  std::min
#include "rectangle.h"

namespace my_game {

	class CollisionBox : public Rectangle {
	 public:
		CollisionBox(float x, float y, float w, float h) : Rectangle(x + w / 2, y + h / 2, w, h), hit_{ false } {};
		bool ComputeCollision(CollisionBox&);

	 private:
		bool hit_ = false;
	};

	bool CollisionBox::ComputeCollision(CollisionBox& other) {
		float min_x = std::min<float>(center_x_ - width_ / 2.0f, other.center_x_ - other.width_ / 2.0f);
		float max_x = std::max<float>(center_x_ + width_ / 2.0f, other.center_x_ + other.width_ / 2.0f);
		float min_y = std::min<float>(center_y_ - height_ / 2.0f, other.center_y_ - other.height_ / 2.0f);
		float max_y = std::max<float>(center_y_ + height_ / 2.0f, other.center_y_ + other.height_ / 2.0f);

		if (((min_x - max_x) < (width_ - other.width_)) || ((min_y - max_y) < (height_ - other.height_))) {
			hit_ = true;
			other.hit_ = true;

			std::cout << "Collision Detected!";
		}
		else {
			hit_ |= false;
		}

		return hit_;
	}
}