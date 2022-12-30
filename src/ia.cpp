#include "headers/ia.hpp"

constexpr double RANDOM_MAX = 1.0f;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> max_dist(-RANDOM_MAX, RANDOM_MAX);
std::uniform_real_distribution<double> mutate_dist(-0.1f, 0.1f);

// Activation function
double relu(double x) {
	return std::max(x, 0.0);
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

void Neuron::set_random_weights()
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

NeuralNetWork::NeuralNetWork(const std::vector<int32_t>& topology)
{
	size_t num_inputs = topology[0];
	for (size_t i = 1; i < topology.size(); i++) {
		layers.push_back(Layer(topology[i], num_inputs));
		num_inputs = topology[i];
	}
}

std::vector<double> NeuralNetWork::feedforward(const std::vector<double> &inputs)
{
	std::vector<double> outputs = inputs;
	for (size_t i = 0; i < layers.size(); i++) {
		outputs = layers[i].feedforward(outputs);
		outputs[i] = relu(outputs[i]);
	}
	return outputs;
}

void NeuralNetWork::mutate()
{
	for (auto& layer : layers) {
		layer.mutate();
	}
}

Candidate::Candidate(std::vector<int32_t> topology)
	: rna(topology), dino(), fitness(0.0f)
{

}

Candidate::Candidate()
	: rna ({6, 6, 2})
{

}

void IA::Init()
{
	if (GENERATION == 1)
	{
		population.clear();
		population.reserve(TOTAL_DINOS);
		for (size_t i = 0; i < TOTAL_DINOS; i++) {
			population.push_back(Candidate({6, 6, 2}));
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

