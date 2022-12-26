#include "headers/ia.hpp"

void IA::Init() 
{
	dinos.clear();
	for (size_t i = 0; i < TOTAL_DINOS; i++) {
		dinos.push_back(Dino());
	}
}

void IA::Update()
{
	bool update_texture = false;
    time += GetFrameTime();
	if (time > 0.2f) {
		time = 0.0f;
		update_texture = true;
	}
	for (Dino& dino : dinos)
	{
		if (dino.state != Dino::State::DEAD)
		{
			if (update_texture) {
				(++dino.texture > 2) ? dino.texture = 1 : dino.texture;	
			}
			if (IsKeyDown(KEY_S))
			{
				dino.state = Dino::State::DOWN_RUNNING;
				dino.changedState = true;
				dino.pos.y += 0.5f;
			}
			else if (IsKeyDown(KEY_W) && dino.onGround)
			{
				dino.state = Dino::State::JUMPING;
				dino.changedState = false;
				dino.onGround = false;
			} 
			else if (dino.onGround)
			{
				dino.state = Dino::State::UP_RUNNING;
			}

			// GRAVITY 
			if (dino.state == Dino::State::JUMPING) {
				dino.pos.y -= GRAVITY;
			} 
			else {
				dino.pos.y += GRAVITY + 0.5f;
			}

			// jump limit is 3x dino height
			if (dino.pos.y <= ground_pos_y - upDinoHeight * 3.3) {
				dino.state = Dino::State::FALLING;
			}
		
			// change dino height when down or jump
			if (dino.changedState) {
				dino.pos.y += upDinoHeight - downDinoHeight;
			}

			// Fix dino if on ground
			if (dino.state == Dino::State::DOWN_RUNNING && dino.pos.y + downDinoHeight >= ground_pos_y)
			{
                dino.pos.y = ground_pos_y - downDinoHeight;
				dino.onGround = true;
			}
			else if (dino.pos.y + upDinoHeight >= ground_pos_y)
			{
                dino.pos.y = ground_pos_y - upDinoHeight;
				dino.onGround = true;
			}
			dino.score++;

			Obstacle obs = Obstacle::getFirstObstacle(dino);

			if (dino.state == Dino::State::DOWN_RUNNING) {
				if (CheckCollisionRecs(Rectangle{dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight}, Rectangle{obs.pos.x + 5, obs.pos.y + 5, obs.width - 5, obs.height - 5})) {
					dino.state = Dino::State::DEAD;
					++total_deads;
				}
			} else {
				if (CheckCollisionRecs(Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Rectangle{obs.pos.x + 5, obs.pos.y + 5, obs.width - 5, obs.height - 5})) {
					dino.state = Dino::State::DEAD;
					++total_deads;
				}
			}
			// TODO: ia stuff
        }
		else if (dino.pos.x + upDinoWidth > 0) {
			// GRAVITY 
			if (dino.state == Dino::State::JUMPING) {
				dino.pos.y -= GRAVITY;
			} 
			else {
				dino.pos.y += GRAVITY + 0.5f;
			}
			// Fix dino if on ground
			if (dino.state == Dino::State::DOWN_RUNNING && dino.pos.y + downDinoHeight >= ground_pos_y)
			{
                dino.pos.y = ground_pos_y - downDinoHeight;
				dino.onGround = true;
			}
			else if (dino.pos.y + upDinoHeight >= ground_pos_y)
			{
                dino.pos.y = ground_pos_y - upDinoHeight;
				dino.onGround = true;
			}
			dino.pos.x -= map_velocity;
		}
		if (total_deads == TOTAL_DINOS) {
			total_deads = 0;
			Obstacle::Init();
			IA::Init();
			map_velocity = 6.0f;
		}
	}
}

void IA::Draw()
{
	for (const Dino& dino : dinos)
	{
        switch (dino.state)
		{
			case Dino::State::FALLING:
			case Dino::State::JUMPING:
                DrawTexturePro(upDino[dino.color], Rectangle{0, 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
				break;

			case Dino::State::UP_RUNNING:
                DrawTexturePro(upDino[dino.color], Rectangle{static_cast<float>(dino.texture * upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
				break;

			case Dino::State::DOWN_RUNNING:
                DrawTexturePro(downDino[dino.color], Rectangle{static_cast<float>(dino.texture * downDinoWidth), 0, downDinoWidth, downDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight}, Vector2{0}, 0, RAYWHITE);
				break;

			case Dino::State::DEAD:
				DrawTexturePro(upDino[dino.color], Rectangle{static_cast<float>(upDino[0].width - upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
				break;
		}
	}
}

void IA::EndInit()
{

}
