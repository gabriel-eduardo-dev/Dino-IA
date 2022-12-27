#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <cstdint>
#include <iostream>
#include <raylib.h>
#include <random>
#include <vector>
#include <unordered_map>
#include "global.hpp"
#include <tuple>

#define birdWidth 62
#define birdHeight 50

#define smallCactuWidth 23
#define smallCactuHeight 46

#define bigCactuWidth 33 
#define bigCactuHeight 67 

#define specialCactuWidth 67
#define specialCactuHeight 67

#define MAX_OBSTACLES 10

class Obstacle
{
	public:

		static void Init();
		static void Update();
		static void Draw();

		inline static std::vector<Obstacle> obstacles;

		enum Type {BIRD, SMALL_CACTU, BIG_CACTU, ESPECIAL_CACTU};
		
	private:

		Obstacle();

		Type type;
		Vector2 pos;
		int32_t texture;
		float width;
		float height;

		inline static float time;

		friend std::ostream& operator<<(std::ostream& os, const Obstacle& obs);
		friend std::tuple<Obstacle, float> getNearestObstacle(int32_t dino_pos_x);
		friend class Dino;
};

std::tuple<Obstacle, float> getNearestObstacle(int32_t dino_pos_x);

#endif // !OBSTACLE_HPP
