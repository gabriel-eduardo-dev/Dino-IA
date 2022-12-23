#include "headers/ia.hpp"
#include "headers/global.hpp"
#include <iostream>

void IA::Init() 
{
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
				dino.texture++;
				if (dino.texture > 2) {
					dino.texture = 1; // fixed btw 1 and 2, where he runs it
				}
			}
			if (IsKeyDown(KEY_S))
			{
				dino.state = Dino::State::DOWN_RUNNING;
				dino.changedState = true;
				dino.pos.y += 0.5f;
			}
			else if (IsKeyPressed(KEY_W) && dino.onGround)
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
			if (dino.pos.y <= ground_pos_y - upDinoHeight * 3) {
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

			// TODO: colisions
			// TODO: ia stuff
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
                DrawTexturePro(upDino, Rectangle{0, 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;

			case Dino::State::UP_RUNNING:
                DrawTexturePro(upDino, Rectangle{static_cast<float>(dino.texture * upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;

			case Dino::State::DOWN_RUNNING:
                DrawTexturePro(downDino, Rectangle{static_cast<float>(dino.texture * downDinoWidth), 0, downDinoWidth, downDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight, RED);
				break;

			case Dino::State::DEAD:
				DrawTexturePro(upDino, Rectangle{static_cast<float>(upDino.width - upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;
		}
	}
}

void IA::EndInit()
{

}
