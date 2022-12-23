#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <cstdint>
#include <raylib.h>
#include <random>
#include "global.hpp"

class Obstacle
{
	public:

		Obstacle();

		enum Type {BIRD, SMALL_CACTU, BIG_CACTU, ESPECIAL_CACTU};
		
	private:

		Type type;
		Vector2 pos;
		uint8_t texture;
		bool is_outside_of_bounds;
};

#endif // !OBSTACLE_HPP
