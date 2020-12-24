#include "pch.h"
#include "Utils.h"
#include"Algorithms.h"
#include <iostream>

int main()
{
	Utils util = Utils();

	std::pair<std::string, Graph> P = util.GetParametersAndGraph("C:\\Users\\Shadi Helf\\Desktop\\Introduction to AI\\AI Project\\Test.txt");

	std::string parameters = P.first;

	size_t pos = parameters.find(" ");

	std::string algorithm_name = parameters.substr(0, pos);

	parameters.erase(0, pos + 1);

	pos = parameters.find(" ");

	int start = std::atoi((parameters.substr(0, pos)).c_str());

	parameters.erase(0, pos + 1);

	int end = std::atoi(parameters.c_str());

	Graph G = P.second;

	Algorithms algo;

	algo.SetActiveAlgorithm(algorithm_name);

	algo.SetActiveGraph(G);

	algo.SetStart(start);

	algo.SetEnd(end);

	algo.RunActiveAlgorithm();

	std::string path = algo.GetResultPath();

	int cost = algo.GetResultCost();

	int expanded = algo.GetResultExpandedVertices();

	std::cout << "Path : " + path << std::endl;
	std::cout << "Cost : " + std::to_string(cost) << std::endl;
	std::cout << "Expanded Vertices : " + std::to_string(expanded) << std::endl;
}

