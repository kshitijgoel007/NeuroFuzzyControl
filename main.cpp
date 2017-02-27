//Custom Includes
#include "parser.h"
#include "net.h"
#include "neuron.h"
#include "gnuplot_i.hpp"

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


void PrintVector(std::vector<int>& vec)
{
  std::cout << "Topology of the net is : " << std::endl;
    for (unsigned int i = 0; i < vec.size() ; i++)
    {
      std::cout << vec[i] << "  ";
    }
    std::cout << std::endl;
}

void PrintVector(std::vector<double>& vec)
{
    for (unsigned int i = 0; i < vec.size() ; i++)
    {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void TopologyInput(std::vector<int>& net_structure)
{
  int input;
  int hidden_layers;
  std::cout << "*************Constructing Neural Net***************" << std::endl;
  std::cout << "Enter number of inputs : " << std::endl;
  std::cin >> input;
  net_structure.push_back(input);
  std::cout << "Enter number of hidden layers :" << std::endl;
  std::cin >> hidden_layers;

  for (int i = 0; i < hidden_layers; i++) {
    std::cout << "Enter the number of neurons in hidden layer : " << i + 1 << std::endl;
    std::cin >> input;
    net_structure.push_back(input);
  }

  std::cout << "Enter number of outputs : " << std::endl;
  std::cin >> input;
  net_structure.push_back(input);

  PrintVector(net_structure);
}

void ShowVector(std::string label, std::vector<double> &v)
{
	std::cout << label << " ";
	for(unsigned i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}


void StoreScaledData(std::vector<double> input_values, std::vector<double> desired_values, std::ofstream& input, std::ofstream& desired)
{
  for (int j = 0; j < input_values.size(); j++) {
    if (j < (input_values.size() - 1)) {
      input << input_values[j] << " ";
    }
    else{
      input << input_values[j] << std::endl;
    }
  }

  for (int j = 0; j < desired_values.size(); j++) {
    if (j < (desired_values.size() - 1)) {
      desired << desired_values[j] << " ";
    }
    else{
      desired << desired_values[j] << std::endl;
    }
  }
}


////////////////MAIN/////////////////////

int main(int argc, char const *argv[])
{
  int epoch_count;
	//Data import
    Parser p;
    p.file_name = "SN_YEARLY.txt";
    p.data_size = 317;
    p.GetData();
    p.ScalingData();
  // For gnuplot_i
    //Gnuplot gp("lines");

    //Neural Net construction and Learning Params Inputs
    std::vector<int> topology_input;
    TopologyInput(topology_input);
    std::cout << "Enter the number of Epochs: ";
    std::cin >> epoch_count;
    //Topology Complete

    //Windowing Dataset Creation
    std::ofstream MSE;
    std::ofstream input, desired;
    MSE.open("MSE.txt"); input.open("input.txt"); desired.open("desired.txt");
    std::vector<double> input_values;
    std::vector<double> desired_values;
    std::vector<double> result_values;
    Net n(topology_input);
    int total_size = p.data_size - (topology_input.front() + topology_input.back());
    std::cout << total_size << " " << p.data_size - total_size << std::endl;
    double** window_data_set = new double*[total_size];

    double meansqtemp;
    double meansqperepoch[epoch_count];
    for (int epoch = 0; epoch < epoch_count; epoch++)
    {
      meansqtemp = 0;
      for (int i = 0; i < total_size; i++)
      {
        window_data_set[i] = new double[p.data_size - total_size];
        for (int j = 0; j < p.data_size - total_size; j++) {
        window_data_set[i][j] = p.sample_outputs_[i+j];
        if(j < (p.data_size - total_size - topology_input.back()))
          input_values.push_back(window_data_set[i][j]);
        else
          desired_values.push_back(window_data_set[i][j]);
        }

        // store input_values and desired_values in a file
        if(epoch == 0)
        {
          StoreScaledData(input_values, desired_values, input, desired);
        }

        n.ForwardPass(input_values);
        n.GetResults(result_values);
        n.BackPropogate(desired_values);
        meansqtemp += n.GetMeanSquareError();
        input_values.clear();
        desired_values.clear();
      }
      meansqperepoch[epoch] = meansqtemp;
      MSE << epoch+1 << " " << meansqperepoch[epoch] << std::endl;
    }
    MSE.close();
    input.close();
    desired.close();
    //delete p;
//Plotting
    // Get MSE from file
    std::vector<double> MSE_data, iter;
    std::ifstream MSE_in("MSE.txt");
    std::string line;

    while(std::getline(MSE_in, line))
    {
        std::istringstream iss(line);
        double a,b;
        if(!(iss >> a >> b)) { break;}
        MSE_data.push_back(b);
        iter.push_back(a);
    }
    //Plot mean square error

      return 0;
}
