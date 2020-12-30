#include "pch.h"
#include "Utils.h"
#include"Algorithms.h"
#include <iostream>
#include <cmath>

int main()
{
	Utils util = Utils();

	std::pair<std::string, Graph> P = util.GetParametersAndGraph("C:\\Users\\Shadi Helf\\Desktop\\Introduction to AI\\AI Project\\10.txt");

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

	if (algorithm_name._Equal("ASTAR") || algorithm_name._Equal("IDASTAR"))
	{
		//algo.SetHeuristicFunction("Chebyshev Distance");
		algo.SetHeuristicFunction("Octile Distance");
	}

	else if(algorithm_name._Equal("BIASTAR"))
	{
		//algo.SetHeuristicFunction("Chebyshev Distance Bidirectional");
		algo.SetHeuristicFunction("Octile Distance Bidirectional");
	}

	else
	{
		algo.SetHeuristicFunction("None");
	}

	algo.RunActiveAlgorithm();

	std::string path = algo.GetResultPath();

	float cost = algo.GetResultCost();

	int expanded = algo.GetResultExpandedVertices();

	int length = algo.GetResultLength();

	float sum = algo.GetHeristicSum();

	int min_depth = algo.GetMinSearchTreeDepth();

	int max_depth = algo.GetMaxSearchTreeDepth();

	float depths_average = algo.GetAverageSearchTreeDepth();

	std::cout << "Path : " + path << std::endl;
	std::cout << std::endl;
	std::cout << "Cost : " + std::to_string(cost) << std::endl;
	std::cout << std::endl;
	std::cout << "Number Of Expanded Vertices : " + std::to_string(expanded) << std::endl;
	std::cout << std::endl;
	std::cout << "Solution Length : " + std::to_string(length) << std::endl;
	std::cout << std::endl;

	if (algorithm_name._Equal("BIASTAR"))
	{
		std::pair<std::string, std::string> result_path_bidirectional = algo.GetResultPathBidirectional();
		std::string result_path_fowards = result_path_bidirectional.first;
		std::string result_path_backwards = result_path_bidirectional.second;

		std::pair<float, float> result_cost_bidirectional = algo.GetResultCostBidirectional();
		float result_cost_fowards = result_cost_bidirectional.first;
		float result_cost_backwards = result_cost_bidirectional.second;

		std::pair<int, int> expanded_bidirectional = algo.GetResultExpandedVerticesBidirectional();
		int expanded_fowards = expanded_bidirectional.first;
		int expanded_backwards = expanded_bidirectional.second;

		std::pair<int, int> length_bidirectional = algo.GetResultLengthBidirectional();
		int length_fowards = length_bidirectional.first;
		int length_backwards = length_bidirectional.second;

		std::pair<float, float> sum_bidirectional = algo.GetHeristicSumBidirectional();
		float sum_fowards = sum_bidirectional.first;
		float sum_backwards = sum_bidirectional.second;

		std::pair<int, int> min_depth_bidirectional = algo.GetMinSearchTreeDepthBidirectional();
		int min_depth_fowards = min_depth_bidirectional.first;
		int min_depth_backwards = min_depth_bidirectional.second;

		std::pair<int, int> max_depth_bidirectional = algo.GetMaxSearchTreeDepthBidirectional();
		int max_depth_fowards = max_depth_bidirectional.first;
		int max_depth_backwards = max_depth_bidirectional.second;

		std::pair<float, float> depths_average_bidirectional = algo.GetAverageSearchTreeDepthBidirectional();
		float depths_average_fowards = depths_average_bidirectional.first;
		float depths_average_backwards = depths_average_bidirectional.second;

		std::cout << std::endl;
		std::cout << "Fowards Run:" << std::endl << std::endl;

		std::cout << "Path Fowards: " + result_path_fowards << std::endl << std::endl;
		std::cout << "Cost Fowards: " + std::to_string(result_cost_fowards) << std::endl << std::endl;
		std::cout << "Number Of Expanded Vertices Fowards: " + std::to_string(expanded_fowards) << std::endl << std::endl;
		std::cout << "Solution Length Fowards: " + std::to_string(length_fowards) << std::endl << std::endl;
		std::cout << "Penetrance Fowards: " + std::to_string(float(length_fowards) / float(expanded_fowards)) << std::endl << std::endl;
		std::cout << "Heuristic Average Fowards: " + std::to_string(sum_fowards / float(expanded_fowards)) << std::endl << std::endl;
		std::cout << "Effective Branching Factor Fowards Is Approximately : " + std::to_string(std::pow(expanded_fowards, 1.0 / length_fowards)) << std::endl << std::endl;
		std::cout << "Minimum Search Tree Depth Fowards: " + std::to_string(min_depth_fowards) << std::endl << std::endl;
		std::cout << "Maximum Search Tree Depth Fowards: " + std::to_string(max_depth_fowards) << std::endl << std::endl;
		std::cout << "Average Of Search Tree Depths Fowards: " + std::to_string(depths_average_fowards) << std::endl << std::endl;

		std::cout << std::endl;
		std::cout << "Backwards Run:" << std::endl << std::endl;

		std::cout << "Path Backwards: " + result_path_backwards << std::endl << std::endl;
		std::cout << "Cost Backwards: " + std::to_string(result_cost_backwards) << std::endl << std::endl;
		std::cout << "Number Of Expanded Vertices Backwards: " + std::to_string(expanded_backwards) << std::endl << std::endl;
		std::cout << "Solution Length Backwards: " + std::to_string(length_backwards) << std::endl << std::endl;
		std::cout << "Penetrance Backwards: " + std::to_string(float(length_backwards) / float(expanded_backwards)) << std::endl << std::endl;
		std::cout << "Heuristic Average Backwards: " + std::to_string(sum_backwards / float(expanded_backwards)) << std::endl << std::endl;
		std::cout << "Effective Branching Factor Backwards Is Approximately : " + std::to_string(std::pow(expanded_backwards, 1.0 / length_backwards)) << std::endl << std::endl;
		std::cout << "Minimum Search Tree Depth Backwards: " + std::to_string(min_depth_backwards) << std::endl << std::endl;
		std::cout << "Maximum Search Tree Depth Backwards: " + std::to_string(max_depth_backwards) << std::endl << std::endl;
		std::cout << "Average Of Search Tree Depths Backwards: " + std::to_string(depths_average_backwards) << std::endl << std::endl;
	}

	else
	{
		std::cout << "Penetrance : " + std::to_string(float(length) / float(expanded)) << std::endl << std::endl;
		std::cout << "Heursistic Average : " + std::to_string(sum / float(expanded)) << std::endl << std::endl;
		std::cout << "Effective Branching Factor Is Approximately : " + std::to_string(std::pow(expanded, 1.0 / length)) << std::endl << std::endl;
		std::cout << "Minimum Search Tree Depth : " + std::to_string(min_depth) << std::endl << std::endl;
		std::cout << "Maximum Search Tree Depth : " + std::to_string(max_depth) << std::endl << std::endl;
		std::cout << "Average Of Search Tree Depths : " + std::to_string(depths_average) << std::endl << std::endl;
	}
}

