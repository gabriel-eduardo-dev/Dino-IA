#include "headers/ia.hpp"

void IA::Init() 
{
	RNAS.clear();
	for (size_t i = 0; i < TOTAL_DINOS; i++) {
		RNAS.push_back(IA());
	}
}

void IA::Update()
{
	for (auto& ia : RNAS) {
		ia.dino.update();
	}
	if (TOTAL_DEADS == TOTAL_DINOS) {
		IA::Init();
		Obstacle::Init();
		TOTAL_DEADS = 0;
		GENERATION++;
		map_velocity = DEFAULT_MAP_VEL;
	}
}

void IA::Draw()
{
	for (auto& ia: RNAS) {
		ia.dino.draw();
	}
}
