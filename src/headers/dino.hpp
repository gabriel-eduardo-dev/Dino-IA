#ifndef DINO_HPP
#define DINO_HPP

#include <cstdint>
#include <raylib.h>

#define upDinoWidth 59
#define upDinoHeight 62

#define downDinoWidth 114
#define downDinoHeight 40

class Dino
{
	public:

		Dino();
		~Dino();

	private:

        bool isDead;
		bool isJumping;
		uint64_t score;
		uint16_t colisionEntity;
		Vector2 pos;
};

#endif // !DINO_HPP
