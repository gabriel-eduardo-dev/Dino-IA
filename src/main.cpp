#include <cstdint>
#include <raylib.h>

#include "headers/IA.hpp"

constexpr uint32_t screen_width = 1280;
constexpr uint32_t screen_height = 720;
bool pause = false;

static void Init();
static void Update();
static void Draw();
static void EndInit();

int32_t main (int argc, char *argv[])
{
	Init();
	while (!WindowShouldClose())
	{
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

	IA::Init();
}

static void Update()
{
    IA::Update();
}

static void Draw()
{
    BeginDrawing();

	ClearBackground(RAYWHITE);
	DrawFPS(25, 25);
    
	IA::Draw();

	EndDrawing();
}

static void EndInit()
{
	IA::EndInit();
    CloseWindow(); 
}
