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
		"\n\tState: " << map_states.at(dino.state) <<
		"\n\tPos x: " << dino.pos.x <<
		"\n\tPos y: " << dino.pos.y <<
		"\n\tScore: " << dino.score <<
		"\n\tOn Ground:" << dino.onGround <<
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
	score = 0;
	color = GetRandomValue(0, TOTAL_DINO_COLORS);
}

void Dino::update()
{
	if (state != Dino::State::DEAD)
	{
		(update_texture && ++texture > 2) ? texture = 1 : texture;	

		const auto [obstacle, distance] = getNearestObstacle(pos.x);

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
			pos.y = ground_pos_y - upDinoHeight;
			onGround = true;
		}

		// Colision
		if (CheckCollisionRecs(
				Rectangle{pos.x, pos.y, 
					static_cast<float>((state == Dino::State::DOWN_RUNNING) ? downDinoWidth : upDinoWidth), 
					static_cast<float>((state == Dino::State::DOWN_RUNNING) ? downDinoHeight : upDinoHeight)}, 
				Rectangle{obstacle.pos.x + 5, obstacle.pos.y + 5, obstacle.width - 5, obstacle.height - 5}))
		{
			state = Dino::State::DEAD;
			++TOTAL_DEADS;
		} 	
		++score;
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
					{0, 0, upDinoWidth, upDinoHeight}, 
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
