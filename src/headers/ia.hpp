#ifndef IA_HPP
#define IA_HPP

#include <array>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <raylib.h>

#include "global.hpp"
#include "dino.hpp"
#include "obstacle.hpp"

#define BIAS 4

class IA
{
	public:

		static void Init();
		static void Update();
		static void Draw();

		template <size_t W, size_t R>
		struct Layer {
			std::array<double, W> weights;
			std::array<double, R> results;
		};
		struct Layers {
			Layer<6,6> input;
			Layer<6,2> hidden;
			Layer<0,2> output;
		};

		void rna_init();
		void rna_update();
	
	private:

		Layers layers;
		Dino dino;
	
		inline static std::vector<IA> RNAS;

		friend std::ostream& operator<<(std::ostream& os, const IA& ia);
};

#endif // !IA_HPP
