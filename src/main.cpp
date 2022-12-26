#include <cstdint>
#include <raylib.h>

#include "headers/global.hpp"
#include "headers/ia.hpp"
#include "headers/obstacle.hpp"

bool pause = false;
float ground_x = 0;
float map_velocity = 6.0f;
float score = 0.0f;

Texture2D ground;
Texture2D upDino[TOTAL_DINO_COLORS];
Texture2D downDino[TOTAL_DINO_COLORS];
Texture2D bird;
Texture2D smallCactus;
Texture2D bigCactus;
Texture2D especialCactu;

static void Init();
static void Update();
static void Draw();
static void EndInit();

int32_t main (int argc, char *argv[])
{
	Init();
	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_P)) {
			pause = !pause;
		}
		if (IsKeyPressed(KEY_R)) {
			IA::Init();
			Obstacle::Init();
		}
		if (!pause) {
			Update();
		}
		Draw();
	}
	EndInit();
}

static void Init()
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screen_width, screen_height, "Dino IA");
	SetTargetFPS(60);

	for (size_t i = 0; i < TOTAL_DINO_COLORS; i++) {
		upDino[i] = LoadTexture(("assets/upDino" + std::to_string(i) + ".png").c_str());
		downDino[i] = LoadTexture(("assets/downDino" + std::to_string(i) + ".png").c_str());
	}

	ground = LoadTexture("assets/ground.png");
	bird = LoadTexture("assets/bird.png");
	smallCactus = LoadTexture("assets/smallCactus.png");
	bigCactus = LoadTexture("assets/bigCactus.png");
	especialCactu = LoadTexture("assets/specialCactu.png");
	
	IA::Init();
	Obstacle::Init();
}

static void Update()
{
	if (map_velocity < 10.0f) {
		map_velocity += 0.0002;
	}
	ground_x += map_velocity;
	if (ground_x > ground.width) {
		ground_x = 0.0f;
	}
    IA::Update();
	Obstacle::Update();
}

static void Draw()
{
    BeginDrawing();

	ClearBackground(WHITE);
	DrawFPS(25, 25);
	DrawText(TextFormat("%i %i", GetMouseX(), GetMouseY()), 25, 50, 20, LIME);
	DrawText(TextFormat("Map vel: %f", map_velocity), screen_width - 200, 25, 20, LIME);

    // Ground
	DrawTexturePro(ground, Rectangle{static_cast<float>(ground_x + map_velocity), 0, static_cast<float>(ground.width), static_cast<float>(ground.height)}, Rectangle{0, ground_pos_y - 15, screen_width, static_cast<float>(ground.height)}, Vector2{0}, 0, RAYWHITE);

	Obstacle::Draw();
	IA::Draw();
	
	EndDrawing();
}

static void EndInit()
{
	IA::EndInit();
	for (size_t i = 0; i < TOTAL_DINO_COLORS; i++) {
		UnloadTexture(upDino[i]);
		UnloadTexture(downDino[i]);
	}
	UnloadTexture(ground);
	UnloadTexture(bird);
	UnloadTexture(smallCactus);
	UnloadTexture(bigCactus);
	UnloadTexture(especialCactu);
    CloseWindow(); 
}
