#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <cstdint>
#include <raylib.h>
#include <random>
#include <vector>
#include "global.hpp"

#define birdWidth 62
#define birdHeight 50

#define smallCactuWidth 23
#define smallCactuHeight 46

#define bigCactuWidth 33 
#define bigCactuHeight 67 

#define specialCactuWidth 67
#define specialCactuHeight 67

#define MAX_OBSTACLES 100

class Obstacle
{
	public:

		Obstacle();

		static void Init();
		static void Update();
		static void Draw();

		enum Type {BIRD, SMALL_CACTU, BIG_CACTU, ESPECIAL_CACTU};
		
	private:

		Type type;
		Vector2 pos;
		uint8_t texture;
		bool is_outside_of_bounds;

		inline static std::vector<Obstacle> obstacles;
		inline static float time;

		friend class IA;

};

#endif // !OBSTACLE_HPP
