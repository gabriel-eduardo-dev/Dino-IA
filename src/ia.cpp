#include "headers/ia.hpp"

constexpr double RANDOM_MAX = 1000.0;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> max_dist(-RANDOM_MAX, RANDOM_MAX);

// Activation function
double relu(double x) {
	return (x > 0) ? x : 0;
}

Neuron::Neuron(int32_t num_inputs)
{
	for (int32_t i = 0; i < num_inputs; i++) {
		weights.push_back(max_dist(mt));
	}
	bias = max_dist(mt);
}

double Neuron::feedforward(const std::vector<double>& inputs)
{
	double sum = 0.0;
	for (int32_t i = 0; i < weights.size(); i++) {
		sum += inputs[i] * weights[i];
	}
	sum += bias;
	return relu(sum);
}

Layer::Layer(int32_t num_neurons, int32_t num_inputs_per_neuron)
{
	for (int i = 0; i < num_neurons; i++) {
		neurons.push_back(Neuron(num_inputs_per_neuron));
	}
}

std::vector<double> Layer::feedforward(const std::vector<double> &inputs)
{
	std::vector<double> outputs;
	for (int i = 0; i < neurons.size(); i++) {
		outputs.push_back(neurons[i].feedforward(inputs));
	}
	return outputs;
}

NeuralNetWork::NeuralNetWork(const std::vector<int32_t>& topology)
{
	int num_inputs = topology[0];
	for (int i = 1; i < topology.size(); i++) {
		layers.push_back(Layer(topology[i], num_inputs));
		num_inputs = topology[i];
	}
}

std::vector<double> NeuralNetWork::feedforward(const std::vector<double> &inputs)
{
	std::vector<double> outputs = inputs;
	for (int i = 0; i < layers.size(); i++) {
		outputs = layers[i].feedforward(outputs);
	}
	return outputs;
}

void IA::Init()
{

}

void IA::Update()
{

}

void IA::Draw()
{

}

