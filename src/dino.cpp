#include "headers/dino.hpp"

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
		"\n\t\tState: " << map_states.at(dino.state) <<
		"\n\t\tPos x: " << dino.pos.x <<
		"\n\t\tPos y: " << dino.pos.y <<
		"\n\t\tOn Ground:" << dino.onGround <<
	"\n\t}\n";
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
	color = GetRandomValue(0, TOTAL_DINO_COLORS);
}

void Dino::setState(State newState)
{
	if (this->state != Dino::State::DEAD) {
		this->state = newState;
	} 
}

Dino::State Dino::getState()
{
	return this->state;
}

void Dino::update()
{
	if (state != Dino::State::DEAD)
	{
		(update_texture && ++texture > 2) ? texture = 1 : texture;	

		auto [a, obstacleDistance] = getNearestObstacle(pos.x);
		this->nearestObstacle = a;

		// GRAVITY 
		if (state == Dino::State::JUMPING) {
			changedState = false;
			onGround = false;
			pos.y -= GRAVITY;
		} 
		else {
			pos.y += GRAVITY + 0.5f;
		}
		if (state == Dino::State::DOWN_RUNNING) {
			changedState = true;
			pos.y += 0.1f;
		}

		// jump limit is 3.3x dino height
		if (pos.y <= ground_pos_y - upDinoHeight * 3.3) {
			state = Dino::State::FALLING;
		}
	
		// change dino height when down or jump
		if (changedState) {
			pos.y += upDinoHeight - downDinoHeight;
		}

		// Fix dino if on ground
		if (state == Dino::State::DOWN_RUNNING && pos.y + downDinoHeight >= ground_pos_y)
		{
			pos.y = ground_pos_y - downDinoHeight;
			onGround = true;
		}
		else if (pos.y + upDinoHeight >= ground_pos_y)
		{
			state = State::UP_RUNNING;
			pos.y = ground_pos_y - upDinoHeight;
			onGround = true;
		}

		// Colision
		if (CheckCollisionRecs(
				Rectangle{pos.x, pos.y, 
					static_cast<float>((state == Dino::State::DOWN_RUNNING) ? downDinoWidth : upDinoWidth), 
					static_cast<float>((state == Dino::State::DOWN_RUNNING) ? downDinoHeight : upDinoHeight)}, 
				Rectangle{nearestObstacle.pos.x, nearestObstacle.pos.y, nearestObstacle.width, nearestObstacle.height}))
		{
			state = Dino::State::DEAD;
			++TOTAL_DEADS;
		} 	
	}
	else if (pos.x + upDinoWidth > 0)
	{
		pos.x -= map_velocity;
		pos.y += GRAVITY + 0.5f;

		// Fix dino if on ground
		if (state == Dino::State::DOWN_RUNNING && pos.y + downDinoHeight >= ground_pos_y)
		{
			pos.y = ground_pos_y - downDinoHeight;
			onGround = true;
		}
		else if (pos.y + upDinoHeight >= ground_pos_y)
		{
			pos.y = ground_pos_y - upDinoHeight;
			onGround = true;
		}
	}
}

void Dino::draw()
{
	switch (state)
	{
		case Dino::State::FALLING:
		case Dino::State::JUMPING:
			DrawTexturePro(upDino[color], 
					{0, 0, upDinoWidth, upDinoHeight - 1}, 
					{pos.x, pos.y, upDinoWidth, upDinoHeight}, {0}, 0, RAYWHITE);
			break;

		case Dino::State::UP_RUNNING:
			DrawTexturePro(upDino[color],
					{static_cast<float>(texture * upDinoWidth), 0, upDinoWidth, upDinoHeight},
					{pos.x, pos.y, upDinoWidth, upDinoHeight}, {0}, 0, RAYWHITE);
			break;

		case Dino::State::DOWN_RUNNING:
			DrawTexturePro(downDino[color],
					{static_cast<float>(texture * downDinoWidth), 0, downDinoWidth, downDinoHeight},
					{pos.x, pos.y, downDinoWidth, downDinoHeight}, {0}, 0, RAYWHITE);
			break;

		case Dino::State::DEAD:
			DrawTexturePro(upDino[color],
					{static_cast<float>(upDino[0].width - upDinoWidth), 0, upDinoWidth, upDinoHeight},
					{pos.x, pos.y, upDinoWidth, upDinoHeight}, {0}, 0, RAYWHITE);
			break;
	}
}

Dino::~Dino()
{

}
