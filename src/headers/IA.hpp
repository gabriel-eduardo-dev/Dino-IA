#ifndef IA_HPP
#define IA_HPP

#include <cstdint>

#include "dino.hpp"
#include "bird.hpp"
#include "cactus.hpp"

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

		static void enemysUpdate();
		static void enemysDraw();
};

#endif // !IA_HPP
