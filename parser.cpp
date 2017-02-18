#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "parser.h"
#include <algorithm>

Parser::~Parser()
{
    delete[] sample_inputs_;
    delete[] sample_outputs_;

    sample_inputs_ = NULL;
    sample_outputs_ = NULL;
}

void Parser::Initialize()
{
    for (int i = 0; i < data_size; i++)
	{
		sample_inputs_[i] = 0;
		sample_outputs_[i] = 0;
	}
}

void Parser::PrintDataset()
{
    for (int i=0; i < data_size; i++)
    {
            std::cout << sample_inputs_[i] << ",";
            std::cout << sample_outputs_[i] << std::endl;
    }
}

void Parser::GetData()
{
    std::ifstream infile(file_name.c_str());
    std::cout << "Given file is : " << file_name.c_str() << std::endl;
    std::string line;

    sample_inputs_ = new double[data_size];
    sample_outputs_ = new double[data_size];
    Initialize();

    std::cout << "Loading Dataset...." << std::endl;
    int i = 0;

    while(std::getline(infile, line))
    {
        std::istringstream iss(line);
        double a,b;
        if(!(iss >> a >> b)) { break;}
        sample_inputs_[i] = a;
        sample_outputs_[i] = b;
        i = i + 1;
    }
    std::cout << "Dataset captured is : " << std::endl;
    //PrintDataset();
}

void Parser::ScalingData()
{
  for (int i = 0; i < data_size; i++) {
  sample_outputs_[i] = -0.9 + (sample_outputs_[i] - *std::min_element(sample_outputs_, sample_outputs_+ data_size))*1.8/
                          (*std::max_element(sample_outputs_, sample_outputs_ + data_size) - *std::min_element(sample_outputs_, sample_outputs_+ data_size));
  }
  //PrintDataset();
  return;
}
