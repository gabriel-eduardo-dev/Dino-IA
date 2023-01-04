#ifndef IA_HPP
#define IA_HPP

#include <cstdint>
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <fstream>

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
		void rand_weights();
		friend class IA;
		friend class NeuralNetWork;
};

class Layer 
{
	private:

		std::vector<Neuron> neurons;

	public:

        Layer(size_t num_neurons, size_t num_inputs_per_neuron);
        std::vector<double> feedforward(const std::vector<double>& _inputs);
		void mutate();
		void rand_weights();
		friend class IA;
		friend class NeuralNetWork;
};

class NeuralNetWork
{
	private:

		Layer inputs;
		Layer hiddens;
		Layer outputs;

	public:

		NeuralNetWork(int32_t _inputs, int32_t _hiddens, int32_t _outputs);

		std::vector<double> feedforward(const std::vector<double>& inputs);
		void mutate();
		void rand_weights();

		friend class IA;
};

struct Candidate
{
	Candidate(int32_t inputs, int32_t hiddens, int32_t outputs);
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
