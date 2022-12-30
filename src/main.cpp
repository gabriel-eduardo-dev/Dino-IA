#include <cstdint>
#include <cstdlib>
#include <string>
#include <raylib.h>

#include "headers/global.hpp"
#include "headers/dino.hpp"
#include "headers/obstacle.hpp"
#include "headers/ia.hpp"

bool pause = false;
float ground_x = 0;
float background_x = 0;
float map_velocity = 6.0f;
float score = 0.0f;
float MAX_RANGE = 1000.0f;
float GENERATION = 1.0f;
bool update_texture = false; // dino
int32_t TOTAL_DEADS = 0;
float best_fitness = 0.0f;

float frame_rate = 60.0f;

Texture2D ground;
Texture2D upDino[TOTAL_DINO_COLORS];
Texture2D downDino[TOTAL_DINO_COLORS];
Texture2D bird;
Texture2D smallCactus;
Texture2D bigCactus;
Texture2D especialCactu;
Texture2D background;

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
			GENERATION = 1;
			map_velocity = DEFAULT_MAP_VEL;
			TOTAL_DEADS = 0;
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
	background = LoadTexture("assets/background_sky.png");
	
	IA::Init();
	Obstacle::Init();
}

static void Update()
{
	if (IsKeyDown(KEY_RIGHT) && frame_rate < 500) {
		frame_rate += 10;
		SetTargetFPS(frame_rate);
	}
	if (IsKeyDown(KEY_LEFT) && frame_rate > 60) {
		frame_rate -= 10;
		SetTargetFPS(frame_rate);
	}

	if (map_velocity < 20.0f) {
		map_velocity += 0.001;
	}
	ground_x += map_velocity;
	background_x += map_velocity / 2.0f;
	if (ground_x > ground.width) {
		ground_x = 0.0f;
	}
	if (background_x > background.width) {
		background_x = 0.0f;
	}

	update_texture = false;
	static float time; time += GetFrameTime();
	if (time >= 0.2f) {
		time = 0;
		update_texture = true;
	}
    IA::Update();
	Obstacle::Update();
}

static void Draw()
{
    BeginDrawing();

	ClearBackground(Color{32,32,32});
	DrawFPS(25, 25);
	DrawTexturePro(background, Rectangle{background_x, 0, (float)background.width, (float)background.height}, Rectangle{0, -250, (float)background.width, (float)background.height}, Vector2{0}, 0, RAYWHITE);
	DrawText(TextFormat("Map vel: %0.2f", map_velocity), screen_width - 200, 25, 20, LIME);
	DrawText(TextFormat("Generation: %0.0f", GENERATION), screen_width - 200, 50, 20, LIME);
	DrawText(TextFormat("Dead dinos: %i", TOTAL_DEADS), screen_width - 200, 75, 20, LIME);
	DrawText(TextFormat("Best Fitness: %0.2f", best_fitness), screen_width - 200, 100, 20, LIME);
	DrawText(TextFormat("MOUSE %i , %i", GetMouseX(), GetMouseY()), 50, 50, 20, RED);


    // Ground
	DrawTexturePro(ground, Rectangle{ground_x, 0, static_cast<float>(ground.width), static_cast<float>(ground.height)}, Rectangle{0, ground_pos_y - 15, screen_width, static_cast<float>(ground.height)}, Vector2{0}, 0, RAYWHITE);

	IA::Draw();
	Obstacle::Draw();
	
	EndDrawing();
}

static void EndInit()
{
	for (size_t i = 0; i < TOTAL_DINO_COLORS; i++) {
		UnloadTexture(upDino[i]);
		UnloadTexture(downDino[i]);
	}
	UnloadTexture(ground);
	UnloadTexture(bird);
	UnloadTexture(smallCactus);
	UnloadTexture(bigCactus);
	UnloadTexture(especialCactu);
	UnloadTexture(background);
    CloseWindow(); 
}
