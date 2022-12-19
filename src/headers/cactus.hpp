#ifndef CACTUS_HPP
#define CACTUS_HPP

#include <cstdint>
#include <raylib.h>

#define smallCactuWidth 23
#define smallCactuHeight 46

#define bigCactuWidth 33 
#define bigCactuHeight 67 

#define specialCactuWidth 67
#define specialCactuHeight 67

class Cactu
{
	public:

		Cactu();
		~Cactu();

	private:

		bool isOutsideOfMap;
		uint8_t texture;
		Vector2 pos;
};

#endif // !CACTUS_HPP
