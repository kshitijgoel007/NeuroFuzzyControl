#ifndef NEURON_H_
#define NEURON_H_

//Custom Includes
#include "parser.h"

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

//// Class for Neuron
class Neuron;

typedef std::vector<Neuron> Layer;

struct Connection
{
  double weight;
  double delta_weight;
};
/******************/
class Neuron
{
public:
  Neuron(unsigned n_outputs, unsigned neural_index);
  void SetOutputVal(double val) {neuron_output_ = val;}
  double GetOutputVal(void) {return neuron_output_;}
  void FeedForward(Layer& prev_layer);
  void CalcOutputGradients(double desired_values);
  void CalcHiddenGradients(Layer& next_layer);
  double SumNext(Layer& next_layer);
  void UpdateInputWeights(Layer& prev_layer);
private:
  static double ActivationFunction(double x);
  static double ActivationFunctionDerivative(double x);
  static double RandomWeight(void) {return rand() / double(RAND_MAX);};
  double neuron_output_;
  std::vector<Connection> neural_output_links_;
  unsigned n_index;
  double neuron_gradient;
  static double eta;
  static double alpha;
};

#endif
