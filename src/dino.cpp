#include "headers/dino.hpp"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int32_t> dist_pos_x(5, 350);

Dino::Dino()
{
	pos.x = dist_pos_x(mt);
	pos.y = screen_height - 100;
	texture = 1;
	state = State::UP_RUNNING;
	changedState = false;
	onGround = true;
}

Dino::~Dino()
{

}
