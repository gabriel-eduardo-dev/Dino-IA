#ifndef DINO_HPP
#define DINO_HPP

#include <cstdint>
#include <raylib.h>
#include <random>

#include "global.hpp"

#define upDinoWidth 59
#define upDinoHeight 62

#define downDinoWidth 79
#define downDinoHeight 39

#define maxDinos 4

enum State {
	JUMPING,
	UP_RUNNING,
	DOWN_RUNNING,
	DEAD,
};


class Dino
{
	public:

		Dino();
		~Dino();

	private:

		State state;
		bool changedState;
		uint64_t score;
		uint16_t colisionEntity;
		uint8_t texture;
		Vector2 pos;

		friend class IA;
};

#endif // !DINO_HPP
