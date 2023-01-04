#include "headers/ia.hpp"
#include <vector>

constexpr double RANDOM_MAX = 1.0f;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> max_dist(-RANDOM_MAX, RANDOM_MAX);
std::uniform_real_distribution<double> mutate_dist(-1.f, 1.f);

// Activation function
double relu(double x) {
	return (x > 0) ? x : 0;
}

Neuron::Neuron(size_t num_inputs)
{
	for (size_t i = 0; i < num_inputs; i++) {
		weights.push_back(max_dist(mt));
	}
	bias = max_dist(mt);
}

double Neuron::feedforward(const std::vector<double>& inputs)
{
	double sum = 0.0;
	for (size_t i = 0; i < weights.size(); i++) {
		sum += inputs[i] * weights[i];
	}
	sum += bias;
	return relu(sum);
}

void Neuron::mutate()
{
	for (auto& weight : weights) {

		weight += mutate_dist(mt);
	}
	bias += mutate_dist(mt);
}

void Neuron::rand_weights()
{
	for (auto& weight : weights) {

		weight = max_dist(mt);
	}
	bias = max_dist(mt);
}

Layer::Layer(size_t num_neurons, size_t num_inputs_per_neuron)
{
	for (size_t i = 0; i < num_neurons; i++) {
		neurons.push_back(Neuron(num_inputs_per_neuron));
	}
}

std::vector<double> Layer::feedforward(const std::vector<double> &inputs)
{
	std::vector<double> outputs;
	outputs.reserve(neurons.size());
	for (size_t i = 0; i < neurons.size(); i++) {
		outputs.push_back(neurons[i].feedforward(inputs));
	}
	return outputs;
}

void Layer::mutate()
{
	for (auto& neuron : neurons) {
		neuron.mutate();
	}
}

void Layer::rand_weights()
{
	for (auto& neuron : neurons)
	{
		neuron.rand_weights();
	}
}

NeuralNetWork::NeuralNetWork(int32_t _inputs, int32_t _hiddens, int32_t _outputs)
	: inputs(_inputs, _inputs), hiddens(_inputs, _inputs), outputs(_outputs, _inputs)
{

}

std::vector<double> NeuralNetWork::feedforward(const std::vector<double> &_inputs)
{
	auto in_result = inputs.feedforward(_inputs);
	auto hidden_result = hiddens.feedforward(in_result);
	auto out_result = outputs.feedforward(hidden_result);
	return out_result;
}

void NeuralNetWork::mutate()
{
	inputs.mutate();
	hiddens.mutate();
	outputs.mutate();
}


void NeuralNetWork::rand_weights()
{
	inputs.rand_weights();
	hiddens.rand_weights();
	outputs.rand_weights();
}


Candidate::Candidate(int32_t inputs, int32_t hiddens, int32_t outputs)
	: rna(inputs, hiddens, outputs), dino(), fitness(0.0f)
{

}

Candidate::Candidate()
	: rna (INPUTS_LAYER_SIZE, HIDDENS_LAYER_SIZE, OUTPUTS_LAYER_SIZE)
{

}

void IA::Init()
{
	if (GENERATION == 1)
	{
		population.clear();
		population.reserve(TOTAL_DINOS);
		for (size_t i = 0; i < TOTAL_DINOS; i++) {
			population.push_back(Candidate(INPUTS_LAYER_SIZE, HIDDENS_LAYER_SIZE, OUTPUTS_LAYER_SIZE));
		}
	}
	else 
	{
		std::sort(population.begin(), population.end(),
			[](const Candidate& a, const Candidate& b) {
				return a.fitness > b.fitness;
			});
		const auto best_candidate = population[0];
		if (best_fitness < best_candidate.fitness) {
			best_fitness = best_candidate.fitness;
			best = best_candidate;
		}
		std::cout << best_candidate.fitness << std::endl;
		for (size_t i = 0; i < population.size(); i++)
		{
			if (i % 2 == 0)
			{
				population[i].rna = best_candidate.rna;
				population[i].rna.mutate();
				population[i].dino = Dino();
				population[i].fitness = 0.0f;
			}
			else
			{
				population[i].rna.rand_weights();
				population[i].dino = Dino();
				population[i].fitness = 0.0f;
			}
		}
		for (auto& [rna, dino, fitness] : population)
		{
			rna = best.rna;
			rna.mutate();
			fitness = 0.0f;
			dino = Dino();
		}
	}
}

void IA::Update()
{
	for (auto& [rna, dino, fitness] : population)
	{
		if (dino.pos.x < -downDinoWidth) {
			continue;
		}
		std::vector<double> outputs =
			// inputs
			rna.feedforward({
				dino.pos.y,
				dino.pos.x,
				dino.obstacleDistance,
				dino.nearestObstacle.pos.y,
				dino.nearestObstacle.width,
				map_velocity
			});
		if (outputs[0] > 0 && dino.onGround) {
			dino.setState(Dino::State::JUMPING);
		}
		if (outputs[1] > 0) {
			dino.setState(Dino::State::DOWN_RUNNING);
		}
		dino.update();
		if (dino.state != Dino::State::DEAD) {
			fitness += 0.01f;
		}
	}
	if (TOTAL_DEADS == TOTAL_DINOS)
	{
		map_velocity = DEFAULT_MAP_VEL;
		GENERATION += 1;
		TOTAL_DEADS = 0;

		IA::Init();
		Obstacle::Init();
	}
}

void IA::Draw()
{
	for (auto& [rna, dino, fitness] : population)
	{
		dino.draw();
	}
}

