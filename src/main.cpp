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
    p.file_name = "./Data/SN_YEARLY.txt";
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
    std::ofstream MSE, MSE_test;
    std::ofstream input, desired, results;
    //Open the files
    MSE.open("output_data/MSE.txt"); input.open("output_data/input.txt"); desired.open("output_data/desired.txt");
    MSE_test.open("output_data/MSE_test.txt");results.open("output_data/results.txt");

    //Define vectors for neural net. Size will be defined automatically using the
    //topology input from the user
    std::vector<double> input_values;
    std::vector<double> desired_values;
    std::vector<double> result_values;
    Net n(topology_input);
    int total_size = p.data_size - (topology_input.front() + topology_input.back());
    std::cout << total_size << " " << p.data_size - total_size << std::endl;

    //Allocate memory for Windowing Dataset
    double** window_data_set = new double*[total_size];

    //Aux variables for MSE
    double meansqtemp;
    double meansqperepoch[epoch_count];

    for (int epoch = 0; epoch < epoch_count; epoch++)
    {
      meansqtemp = 0.0;
      //////////////////////ONLINE TRAINING////////////////////////
      for (int i = 0; i < round(total_size*0.6); i++) // 60% is training set
      {
        window_data_set[i] = new double[p.data_size - total_size];
        for (int j = 0; j < p.data_size - total_size; j++)
        {
          window_data_set[i][j] = p.sample_outputs_[i+j];
          if(j < (p.data_size - total_size - topology_input.back()))
            input_values.push_back(window_data_set[i][j]);
          else
            desired_values.push_back(window_data_set[i][j]);
        }

        if(epoch == epoch_count - 1)
        {
          StoreScaledData(input_values, desired_values, input, desired);
          results << i + 1 << " " << result_values[0] << std::endl;
        }

        // NN run
        n.ForwardPass(input_values, desired_values);
        n.GetResults(result_values);
        n.BackPropogate(desired_values);
        meansqtemp += n.GetMeanSquareError();
        input_values.clear();
        desired_values.clear();
      }
      meansqperepoch[epoch] = meansqtemp/round(total_size*0.6);
      MSE << epoch+1 << " " << meansqperepoch[epoch] << std::endl;

      meansqtemp = 0.0;
      // Forward pass run on Test data, 40%
      for (int i = round(total_size*0.6); i < total_size; i++)
      {
        window_data_set[i] = new double[p.data_size - total_size];
        for (int j = 0; j < p.data_size - total_size; j++)
        {
          window_data_set[i][j] = p.sample_outputs_[i+j];
          if(j < (p.data_size - total_size - topology_input.back()))
            input_values.push_back(window_data_set[i][j]);
          else
            desired_values.push_back(window_data_set[i][j]);
        }

        // NN run
        n.ForwardPass(input_values, desired_values);
        n.GetResults(result_values);
        meansqtemp += n.GetMeanSquareError();

        if(epoch == epoch_count - 1)
        {
          StoreScaledData(input_values, desired_values, input, desired);
          results << i - round(total_size*0.6) + 1 << " " << result_values[0] << std::endl;
        }
        input_values.clear();
        desired_values.clear();
      }
      MSE_test << epoch+1 << " " << meansqtemp/(total_size - round(total_size*0.6)) << std::endl;
    }
    MSE.close();
    MSE_test.close();
    input.close();
    desired.close();
    results.close();
    return 0;
}
