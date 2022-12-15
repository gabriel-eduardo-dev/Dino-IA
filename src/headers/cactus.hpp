#ifndef CACTUS_HPP
#define CACTUS_HPP

#include <cstdint>
#include <raylib.h>

#define smallCactuWidth 23
#define smallCactuHeight 46

// TODO: static cactus width in image
#define bigCactuWidth null
#define bigCactuHeight null

class Cactu
{
	public:

		Cactu();
		~Cactu();

	private:

		bool isOutsideOfMap;
		Vector2 pos;
};

#endif // !CACTUS_HPP
