//Custom Includes
#include "parser.h"
#include "neuron.h"

//Standard Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

double Neuron::eta = 0.15; //Learning Rate
double Neuron::alpha = 0.3; //Momentum Factor

Neuron::Neuron(unsigned n_outputs, unsigned neural_index)
{
  for (unsigned c = 0; c < n_outputs; c++) {
    neural_output_links_.push_back(Connection());
    neural_output_links_.back().weight = RandomWeight();
  }
  n_index = neural_index;
}

double Neuron::SumNext(Layer& next_layer)
{
  double net_value = 0.0;
  for (unsigned c = 0; c < next_layer.size(); c++) {
    net_value += neural_output_links_[c].weight*next_layer[c].neuron_gradient;
  }
  return net_value;
}

void Neuron::CalcOutputGradients(double desired_values)
{
  double error = desired_values - neuron_output_;
  neuron_gradient = error*Neuron::ActivationFunctionDerivative(neuron_output_);
}

double Neuron::ActivationFunction(double x)
{
  return tanh(x);
}

double Neuron::ActivationFunctionDerivative(double x)
{
  return 1 - x*x;
}

void Neuron::FeedForward(Layer& prev_layer)
{
  double sum = 0.0;
  for (unsigned n = 0; n < prev_layer.size(); n++) {
    sum += prev_layer[n].GetOutputVal()*
            prev_layer[n].neural_output_links_[n_index].weight;
  }
  neuron_output_ = Neuron::ActivationFunction(sum);
}

void Neuron::UpdateInputWeights(Layer& prev_layer)
{
    for (unsigned n = 0; n < prev_layer.size(); n++) {
      Neuron& neuron = prev_layer[n]; //Neuron is being updated in the previous layer
      double delta_weight_old = neuron.neural_output_links_[n_index].delta_weight;
      double delta_weight_new = eta*neuron.GetOutputVal()*neuron_gradient + alpha*delta_weight_old; //Learning Rate + Momentum

      neuron.neural_output_links_[n_index].delta_weight = delta_weight_new;
      neuron.neural_output_links_[n_index].weight += delta_weight_new;
    }
}

void Neuron::CalcHiddenGradients(Layer& next_layer)
{
    double temp = SumNext(next_layer);
    neuron_gradient = temp * Neuron::ActivationFunctionDerivative(neuron_output_);
}
