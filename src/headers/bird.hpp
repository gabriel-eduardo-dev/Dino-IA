#ifndef BIRD_HPP
#define BIRD_HPP

#include <cstdint>
#include <raylib.h>

#define birdWidth 62
#define birdHeight 50

class Bird
{
	public:

		Bird();
		~Bird();

	private:

		bool isOutsideOfMap;
		Vector2 pos;
};

#endif // !BIRD_HPP
