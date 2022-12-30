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

		Neuron(size_t num_inputs);
		double feedforward(const std::vector<double>& inputs);
		void mutate();
		void set_random_weights();
		friend class IA;
};

class Layer 
{
	private:

		std::vector<Neuron> neurons;

	public:

        Layer(size_t num_neurons, size_t num_inputs_per_neuron);
        std::vector<double> feedforward(const std::vector<double>& inputs);
		void mutate();
		friend class IA;
};

class NeuralNetWork
{
	private:

		std::vector<Layer> layers;

	public:

		NeuralNetWork(const std::vector<int32_t>& topology);
		std::vector<double> feedforward(const std::vector<double>& inputs);
		void mutate();
		friend class IA;
};

struct Candidate
{
	Candidate(std::vector<int32_t> topology);
	Candidate();
	NeuralNetWork rna;
	Dino dino;
	double fitness;
};

class IA 
{
	public:

		static void Init();
		static void Update();
		static void Draw();

	private:

		inline static std::vector<Candidate> population;
		inline static Candidate best;
};

#endif // !IA_HPP
