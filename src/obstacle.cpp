#include "headers/obstacle.hpp"

const std::unordered_map<uint8_t, const std::string> map_types {
	{0, "Bird"},
	{1, "Small Cactu"},
	{2, "Big Cactu"},
	{3, "Special Cactu"},
};

std::ostream& operator<<(std::ostream& os, const Obstacle& obs)
{
	os << "Obstacle {"
		"\n\tType: " << map_types.at(obs.type) <<
		"\n\tPos x: " << obs.pos.x <<
		"\n\tPos y: " << obs.pos.y <<
		"\n\tTexture: " << obs.texture <<
	"\n}\n";
	return os;
}

std::tuple<Obstacle, float> getNearestObstacle(int32_t dino_pos_x) 
{
	Obstacle nearest_obstacle;
	nearest_obstacle.pos.x = 99999;
	float distance = 0.0f;
	for (const auto& obs : Obstacle::obstacles)
	{
		float distance_obs = (obs.pos.x + obs.width) - dino_pos_x ;
		if (distance_obs > 0 && distance_obs < nearest_obstacle.pos.x) {
			nearest_obstacle = obs;
			distance = distance_obs;
		}
	}
	return std::make_tuple(nearest_obstacle, distance);
}

Obstacle::Obstacle()
{	
	type = Obstacle::Type(GetRandomValue(0, 3));
	switch (type)
	{
		case BIRD:
			texture = 1;
			pos.y = ground_pos_y - birdHeight * GetRandomValue(1, 3);
			width = birdWidth;
			height = birdHeight;
			break;

		case SMALL_CACTU:
			texture = GetRandomValue(1, 5);
			pos.y = ground_pos_y - smallCactuHeight;
			width = smallCactuWidth * texture;
			height = smallCactuHeight;
			break;

		case BIG_CACTU:
			texture = GetRandomValue(1, 3);
			pos.y = ground_pos_y - bigCactuHeight;
			width = bigCactuWidth * texture;
			height = bigCactuHeight;
			break;

		case ESPECIAL_CACTU:
			texture = 1;
			pos.y = ground_pos_y - specialCactuHeight;
			width = specialCactuWidth;
			height = specialCactuHeight;
			break;
	}
}

void Obstacle::Init()
{
	obstacles.clear();
    for (size_t i = 0; i < MAX_OBSTACLES; i++)
	{
    	obstacles.push_back(Obstacle());
		(i == 0) ? obstacles[i].pos.x = screen_width 
				 : obstacles[i].pos.x = obstacles[i-1].pos.x + 300 + GetRandomValue(50, 250);
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
	
	size_t index = 0;
	for (Obstacle& obs : obstacles)
	{
		if (obs.type == BIRD && update_texture) {
			(++obs.texture > 2) ? obs.texture = 1 : obs.texture;
		}
		obs.pos.x -= map_velocity;
		if (obs.pos.x + specialCactuWidth < 0)
		{
			obs = Obstacle();
			(index == 0) // change pos.x to last obstacle pos.x + gap
				? obs.pos.x = obstacles[obstacles.size() - 1].pos.x + 300 + GetRandomValue(100, 250)
	            : obs.pos.x = obstacles[index-1].pos.x + 300 + GetRandomValue(100, 250);
		}
		(++index == MAX_OBSTACLES) ? index = 0 : index;
	} 
}

void Obstacle::Draw()
{
    for (const Obstacle& obs : obstacles)
	{
		switch (obs.type)
		{
			case BIRD:
				DrawTexturePro(bird, 
					{static_cast<float>(obs.texture * birdWidth), 0, birdWidth, birdHeight},
					{obs.pos.x, obs.pos.y, birdWidth, birdHeight}, {0}, 0, RAYWHITE);
				break;

			case SMALL_CACTU:
				DrawTexturePro(smallCactus, 
					{0, 0, static_cast<float>(obs.texture * smallCactuWidth), smallCactuHeight},
					{obs.pos.x, obs.pos.y, static_cast<float>(obs.texture * smallCactuWidth), smallCactuHeight}, {0}, 0, RAYWHITE);
				break;

			case BIG_CACTU:
				DrawTexturePro(bigCactus, 
					{0, 0, static_cast<float>(obs.texture * bigCactuWidth), bigCactuHeight},
					{obs.pos.x, obs.pos.y, static_cast<float>(obs.texture * bigCactuWidth), bigCactuHeight}, Vector2{0}, 0, RAYWHITE);
				break;

			case ESPECIAL_CACTU:
				DrawTexturePro(especialCactu, 
					{0, 0, specialCactuWidth, specialCactuHeight},
					{obs.pos.x, obs.pos.y, specialCactuWidth, specialCactuHeight}, {0}, 0, RAYWHITE);
				break;
		}	
	}
}
