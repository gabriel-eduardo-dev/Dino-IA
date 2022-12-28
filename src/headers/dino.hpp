#ifndef DINO_HPP
#define DINO_HPP

#include <cstdint>
#include <raylib.h>
#include <iostream>
#include <unordered_map>

#include "global.hpp"
#include "obstacle.hpp"

#define upDinoWidth 59
#define upDinoHeight 62

#define downDinoWidth 79
#define downDinoHeight 39

extern bool update_texture;

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
	
		void update();
		void draw();

		void setState(State newState);
		Dino::State getState();

	private:

		State state;
		bool changedState;
		bool onGround;
		uint8_t texture;
		int32_t color;
		Vector2 pos;

		int32_t obstacles_passed;
		Obstacle nearestObstacle;
		float obstacleDistance;

		friend class IA;
		friend std::ostream& operator<<(std::ostream& os, const Dino& dino);
};

#endif // !DINO_HPP
