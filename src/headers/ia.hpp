#ifndef IA_HPP
#define IA_HPP

#include <cstdint>
#include <vector>
#include <algorithm>
#include <raylib.h>

#include "global.hpp"
#include "dino.hpp"
#include "obstacle.hpp"

class Neuron
{
	private:

		std::vector<double> weights;
		double bias;

	public:

		Neuron(int32_t num_inputs);
		double feedforward(const std::vector<double>& inputs);
};

class Layer 
{
	private:

		std::vector<Neuron> neurons;

	public:

        Layer(int32_t num_neurons, int32_t num_inputs_per_neuron);
        std::vector<double> feedforward(const std::vector<double>& inputs);
};

class NeuralNetWork
{
	private:

		std::vector<Layer> layers;
		Dino dino;

	public:

		NeuralNetWork(const std::vector<int32_t>& topology);
		std::vector<double> feedforward(const std::vector<double>& inputs);
};

class IA 
{
	public:

		static void Init();
		static void Update();
		static void Draw();

	private:

		std::vector<NeuralNetWork> neuralNetwtoks;
};

#endif // !IA_HPP
