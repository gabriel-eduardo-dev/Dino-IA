#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdint>
#include <raylib.h>

#define screen_width 1280
#define screen_height 720

#define TOTAL_DINOS 1500
#define TOTAL_DINO_COLORS 7
#define GRAVITY 5
#define DEFAULT_MAP_VEL 5.0f;

#define INPUTS_LAYER_SIZE 6
#define HIDDENS_LAYER_SIZE 6
#define OUTPUTS_LAYER_SIZE 2

extern Texture2D ground;
extern Texture2D upDino[TOTAL_DINO_COLORS];
extern Texture2D downDino[TOTAL_DINO_COLORS];
extern Texture2D bird;
extern Texture2D smallCactus;
extern Texture2D bigCactus;
extern Texture2D especialCactu;
extern float map_velocity;
extern float MAX_RANGE;
extern float GENERATION;
extern int32_t TOTAL_DEADS;
extern float best_fitness;

#define ground_pos_y screen_height - 50

#endif // !GLOBAL_HPP
