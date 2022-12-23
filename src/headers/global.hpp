#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdint>
#include <raylib.h>

#define screen_width 1280
#define screen_height 720

#define TOTAL_DINOS 10
#define GRAVITY 5

extern Texture2D ground;
extern Texture2D upDino;
extern Texture2D downDino;
extern Texture2D bird;
extern Texture2D smallCactus;
extern Texture2D bigCactus;
extern Texture2D especialCactu;
extern float map_velocity;

#define ground_pos_y screen_height - 60

#endif // !GLOBAL_HPP
