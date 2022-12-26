#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <cstdint>
#include <iostream>
#include <raylib.h>
#include <random>
#include <vector>
#include <unordered_map>
#include "global.hpp"
#include "dino.hpp"

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
		static Obstacle getFirstObstacle(const Dino& dino);

		enum Type {BIRD, SMALL_CACTU, BIG_CACTU, ESPECIAL_CACTU};
		
	private:

		Obstacle();

		Type type;
		Vector2 pos;
		int32_t texture;
		float width;
		float height;

		inline static std::vector<Obstacle> obstacles;
		inline static float time;

		friend std::ostream& operator<<(std::ostream& os, const Obstacle& obs);
		friend class IA;

};

#endif // !OBSTACLE_HPP
	   //
