#include "headers/obstacle.hpp"

const std::unordered_map<uint8_t, const std::string> map_types {
	{1, "Bird"},
	{2, "Small Cactu"},
	{3, "Big Cactu"},
	{4, "Special Cactu"},
};

std::ostream& operator<<(std::ostream& os, const Obstacle& obs)
{
	os << "Obstacle {"
		"\n\tType: " << map_types.at(obs.type) <<
		"\n\tPos x: " << obs.pos.x <<
		"\n\tPos y: " << obs.pos.y <<
		"\n\tIs outside of bounds: " << obs.is_outside_of_bounds <<
	"\n}\n";
	return os;
}

Obstacle::Obstacle()
	: type {Obstacle::Type(GetRandomValue(1, 4))},
	is_outside_of_bounds {false}
{	switch (type)
	{
		case BIRD:
			texture = 1;
			pos.y = ground_pos_y - birdHeight * GetRandomValue(1, 3);
			break;

		case SMALL_CACTU:
			texture = GetRandomValue(1, 6);
			pos.y = ground_pos_y - smallCactuHeight;
			break;

		case BIG_CACTU:
			texture = GetRandomValue(1, 4);
			pos.y = ground_pos_y - bigCactuHeight;
			break;

		case ESPECIAL_CACTU:
			texture = 0;
			pos.y = ground_pos_y - specialCactuHeight;
			break;
	}
	pos.x = screen_width + GetRandomValue(0, 2500);
}

void Obstacle::Init()
{
    for (size_t j = 0; j < MAX_OBSTACLES; j++) {
    	obstacles.push_back(Obstacle());
    }
}

void Obstacle::Update()
{
	bool update_texture = false;
    time += GetFrameTime();
	if (time > 0.4f) {
		time = 0.0f;
		update_texture = true;
	}

	for (Obstacle& obs : obstacles)
	{
		if (!obs.is_outside_of_bounds)
		{
            if (obs.type == BIRD && update_texture) {
				(++obs.texture > 2) ? obs.texture = 1 : obs.texture;
			}
		    obs.pos.x -= 5;
			if (obs.pos.x + specialCactuHeight < 0) {
				obs.is_outside_of_bounds = true;
			}
		}
	}
}

void Obstacle::Draw()
{
    for (const Obstacle& obs : obstacles)
	{
		if (!obs.is_outside_of_bounds)
		{
			switch (obs.type)
			{
				case BIRD:
					DrawTexturePro(bird, Rectangle{static_cast<float>(obs.texture * birdWidth), 0, birdWidth, birdHeight}, Rectangle{obs.pos.x, obs.pos.y, birdWidth, birdHeight}, Vector2{0}, 0, RAYWHITE);
					break;

				case SMALL_CACTU:
					DrawTexturePro(smallCactus, Rectangle{static_cast<float>(obs.texture * smallCactuWidth), 0, smallCactuWidth, smallCactuHeight}, Rectangle{obs.pos.x, obs.pos.y, smallCactuWidth, smallCactuHeight}, Vector2{0}, 0, RAYWHITE);
					break;

				case BIG_CACTU:
					DrawTexturePro(bigCactus, Rectangle{static_cast<float>(obs.texture * bigCactuWidth), 0, bigCactuWidth, bigCactuHeight}, Rectangle{obs.pos.x, obs.pos.y, bigCactuWidth, bigCactuHeight}, Vector2{0}, 0, RAYWHITE);
					break;

				case ESPECIAL_CACTU:
					DrawTexturePro(especialCactu, Rectangle{0, 0, specialCactuWidth, specialCactuHeight}, Rectangle{obs.pos.x, obs.pos.y, specialCactuWidth, specialCactuHeight}, Vector2{0}, 0, RAYWHITE);
					break;
			}	
		}
	}
}
