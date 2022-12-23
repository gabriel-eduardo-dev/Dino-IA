#include <cstdint>
#include <raylib.h>

#include "headers/global.hpp"
#include "headers/ia.hpp"

bool pause = false;
float ground_x = 0;
float map_velocity = 1.0f;

Texture2D ground;
Texture2D upDino;
Texture2D downDino;
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

	ground = LoadTexture("assets/ground.png");
	upDino = LoadTexture("assets/upDino.png");
	downDino = LoadTexture("assets/downDino.png");
	bird = LoadTexture("assets/bird.png");
	smallCactus = LoadTexture("assets/smallCactu.png");
	bigCactus = LoadTexture("assets/bigCactus.png");
	especialCactu = LoadTexture("assets/especialCactu.png");
	
	IA::Init();
}

static void Update()
{
	ground_x += 4.0f;
	if (ground_x > ground.width) {
		ground_x = 0.0f;
	}
    IA::Update();
}

static void Draw()
{
    BeginDrawing();

	ClearBackground(Color{29,29,29});
	DrawFPS(25, 25);
	DrawText(TextFormat("%i %i", GetMouseX(), GetMouseY()), 25, 50, 20, LIME);

    // Ground
	DrawTexturePro(ground, Rectangle{static_cast<float>(ground_x * map_velocity), 0, static_cast<float>(ground.width), static_cast<float>(ground.height)}, Rectangle{0, ground_pos_y - 15, screen_width, static_cast<float>(ground.height)}, Vector2{0}, 0, RAYWHITE);

	IA::Draw();

	
	EndDrawing();
}

static void EndInit()
{
	IA::EndInit();
	UnloadTexture(ground);
	UnloadTexture(upDino);
	UnloadTexture(downDino);
	UnloadTexture(bird);
	UnloadTexture(smallCactus);
	UnloadTexture(bigCactus);
	UnloadTexture(especialCactu);
    CloseWindow(); 
}
