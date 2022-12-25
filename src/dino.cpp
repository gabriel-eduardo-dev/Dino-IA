#include "headers/dino.hpp"
#include <cstdint>

std::random_device rd;
std::mt19937 mt(rd());

const std::unordered_map<uint8_t, const std::string> map_states
{
	{0, "Jumping"},
	{1, "Falling"},
	{2, "Up running"},
	{3, "Down running"},
	{4, "Dead"},

};

std::ostream& operator<<(std::ostream& os, const Dino& dino)
{
	os << "Dino {"
		"\n\tState: " << map_states.at(dino.state) <<
		"\n\tPos x: " << dino.pos.x <<
		"\n\tPos y: " << dino.pos.y <<
		"\n\tScore: " << dino.score <<
		"\n\tOn Ground:" << dino.onGround <<
		"\n\tColision entity: " << dino.colisionEntity <<
	"\n}\n";
	return os;
}

Dino::Dino()
{
	pos.x = GetRandomValue(0, 300);
	pos.y = screen_height - 100;
	texture = 1;
	state = State::UP_RUNNING;
	changedState = false;
	onGround = true;
	colisionEntity = 0;
	score = 0;
}

Dino::~Dino()
{

}
