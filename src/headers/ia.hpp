#ifndef IA_HPP
#define IA_HPP

#include <cstdint>
#include <vector>

#include <raylib.h>
#include "global.hpp"
#include "dino.hpp"
#include "obstacle.hpp"

class IA
{
	public:

		static void Init();
		static void Update();
		static void Draw();

		struct Weights {
			float dino_y;
			float obstacle_distance;
			float obstacle_width;
			float obstacle_height;
			float obstacle_y;
			float map_vel;
		};
		
	private:

		Weights weights;
		Dino dino;

		inline static std::vector<IA> RNAS;
};

#endif // !IA_HPP
