#pragma once
#include <string>
#include "Graph.h"

// Class Functionality : A class to parse the input file and get the input parameters of the program

class Utils
{
	/****************************************************** Functions *************************************************************/

    // NOTE : Functions explanations are in the cpp file.

public:
	bool CheckIfFloat(std::string str);
	std::pair<std::string, Graph> GetParametersAndGraph(std::ifstream& object);
};