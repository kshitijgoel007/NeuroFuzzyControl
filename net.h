#ifndef NET_H_
#define NET_H_
//Custom Includes
#include "parser.h"
#include "neuron.h"

//Standard Includes
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>


/// Class for whole Network
class Net
{
public:
    Net(const std::vector<int> &topology);
    void ForwardPass(std::vector<double>& input_values, std::vector<double>& desired_values);
    void BackPropogate(std::vector<double>& desired_values);
    void GetResults(std::vector<double>& result_values);
    double GetMeanSquareError(void){return mean_square_error;}
private:
  double mean_square_error;
    std::vector<Layer> layer_net_; //layer_net_[layer_num][neuron_num]
};
#endif
