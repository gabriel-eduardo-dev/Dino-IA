#ifndef DINO_HPP
#define DINO_HPP

#include <cstdint>
#include <raylib.h>
#include <iostream>
#include <random>
#include <unordered_map>

#include "global.hpp"

#define upDinoWidth 59
#define upDinoHeight 62

#define downDinoWidth 79
#define downDinoHeight 39

#define maxDinos 4

class Dino
{
	public:

		Dino();
		~Dino();

		enum State {
			JUMPING,
			FALLING,
			UP_RUNNING,
			DOWN_RUNNING,
			DEAD,
		};

	private:

		State state;
		bool changedState;
		bool onGround;
		uint64_t score;
		uint16_t colisionEntity;
		uint8_t texture;
		Vector2 pos;

		friend std::ostream& operator<<(std::ostream& os, const Dino& dino);
		friend class IA;
};

#endif // !DINO_HPP
