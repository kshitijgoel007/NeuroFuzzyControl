//Custom Includes
#include "parser.h"
#include "net.h"
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


void Net::BackPropogate(std::vector<double>& desired_values)
{
  Layer& output_layer = layer_net_.back();
  mean_square_error = 0.0;
  for (unsigned n = 0; n < output_layer.size(); n++) {
    double error = desired_values[n] - output_layer[n].GetOutputVal();
    mean_square_error += 0.5*(error)*(error);
  }

  //Output Layer Gradients
  for (unsigned n = 0; n < output_layer.size(); n++) {
    output_layer[n].CalcOutputGradients(desired_values[n]);
  }

  //Hidden Layer Gradients
  for (unsigned layer_num = layer_net_.size() - 2; layer_num > 0; --layer_num) {
    Layer& hidden_layer = layer_net_[layer_num];
    Layer& next_layer = layer_net_[layer_num + 1];

    for (unsigned n = 0; n < hidden_layer.size(); n++) {
      hidden_layer[n].CalcHiddenGradients(next_layer);
    }
  }

  for (unsigned layer_num = layer_net_.size() - 1; layer_num > 0; --layer_num){
    Layer& current_layer = layer_net_[layer_num];
    Layer& prev_layer = layer_net_[layer_num - 1];

    for (unsigned n = 0; n < current_layer.size(); n++) {
      current_layer[n].UpdateInputWeights(prev_layer);
    }
  }
  // Update all the weights
}

void Net::ForwardPass(std::vector<double>& input_values)
{
  assert(input_values.size() == layer_net_[0].size());
  for (unsigned i = 0; i < input_values.size(); i++) {
    layer_net_[0][i].SetOutputVal(input_values[i]);
  }

  //Forward Pass
  for (unsigned layerNum = 1; layerNum < layer_net_.size(); layerNum++) {
    for (unsigned n = 0; n < layer_net_[layerNum].size(); n++) {
      Layer& prev_layer = layer_net_[layerNum - 1];
      layer_net_[layerNum][n].FeedForward(prev_layer); // Maths inside Neuron happens here.
    }
  }
}

Net::Net(const std::vector<int>& topology)
{
  unsigned num_layers = topology.size();
  for (int layerNum = 0; layerNum < num_layers; layerNum++) {
    unsigned n_outputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
    layer_net_.push_back(Layer()); // create a new empty layer

    for (int neuron_num = 0; neuron_num < topology[layerNum]; neuron_num++) {
      layer_net_.back().push_back(Neuron(n_outputs, neuron_num));
    }
  }
}

void Net::GetResults(std::vector<double>& result_values)
{
  result_values.clear();
  for (unsigned n = 0; n < layer_net_.back().size(); n++) {
    result_values.push_back(layer_net_.back()[n].GetOutputVal());
  }
}
