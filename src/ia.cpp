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
	const static float a = dinos[0].pos.y;
	if (time > 0.2f) {
		time = 0.0f;
		update_texture = true;
	}
	for (Dino& dino : dinos)
	{
		if (dino.state != State::DEAD)
		{
			if (update_texture) {
				dino.texture++;
				if (dino.texture > 2) {
					dino.texture = 1; // fixed btw 1 and 2, where he runs it
				}
			}
			dino.pos.y += GRAVITY;

			 if (IsKeyDown(KEY_S)) {
				dino.state = State::DOWN_RUNNING;
				dino.changedState = true;
				dino.pos.y += 3;
			} else if (IsKeyDown(KEY_W)) {
				dino.state = State::JUMPING;
				dino.pos.y -= 5;
			} 
			if (dino.state == State::JUMPING && dino.pos.y + upDinoHeight >= ground_pos_y) {
				dino.state = State::UP_RUNNING;
				dino.changedState = false;
			}
			if (dino.changedState) {
				dino.pos.y += (upDinoHeight - downDinoHeight);
			}
			if (dino.state == State::UP_RUNNING && dino.pos.y + upDinoHeight > ground_pos_y)
			{
                dino.pos.y = ground_pos_y - upDinoHeight;
			}
			else if (dino.state == State::DOWN_RUNNING && dino.pos.y + downDinoHeight > ground_pos_y)
			{
                dino.pos.y = ground_pos_y - downDinoHeight;
			}
        }
	}
}

void IA::Draw()
{
	for (const Dino& dino : dinos)
	{
        switch (dino.state)
		{
			case JUMPING:
                DrawTexturePro(upDino, Rectangle{0, 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;

			case UP_RUNNING:
                DrawTexturePro(upDino, Rectangle{static_cast<float>(dino.texture * upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;

			case DOWN_RUNNING:
                DrawTexturePro(downDino, Rectangle{static_cast<float>(dino.texture * downDinoWidth), 0, downDinoWidth, downDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, downDinoWidth, downDinoHeight, RED);
				break;

			case DEAD:
				DrawTexturePro(upDino, Rectangle{static_cast<float>(upDino.width - upDinoWidth), 0, upDinoWidth, upDinoHeight}, Rectangle{dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight}, Vector2{0}, 0, RAYWHITE);
		        DrawRectangleLines(dino.pos.x, dino.pos.y, upDinoWidth, upDinoHeight, RED);
				break;
		}
	}
}

void IA::EndInit()
{

}
