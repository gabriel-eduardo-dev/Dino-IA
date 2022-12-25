#ifndef IA_HPP
#define IA_HPP

#include <cstdint>
#include <vector>

#include <raylib.h>

#include "dino.hpp"
#include "obstacle.hpp"

class IA
{
	public:

		static void Init();
		static void Update();
		static void Draw();
		static void EndInit();
		
	private:

		static void dinoUpdate();
		static void dinoDraw();

		inline static std::vector<Dino> dinos;
		inline static float time;
};

#endif // !IA_HPP
