#ifndef PARSER_H_
#define PARSER_H_
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Parser
{
	//Members
public:
    std::string file_name;
    int data_size;
    double* sample_inputs_;
    double* sample_outputs_;

	//Methods
	public:
		Parser(){}
    ~Parser();
    void Initialize();
    void GetData();
    void PrintDataset();
    void ScalingData();
};


#endif
