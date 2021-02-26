#include "pch.h"
#include "Utils.h"
#include"Algorithms.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>

int main()
{
	std::string file_path;
	std::ifstream input_object;

	while (1)
	{
		std::cout << "Enter a path for an input file : " << std::endl;

		std::getline(std::cin, file_path);

		input_object.open(file_path.c_str()); // Get the file data from the file_path parameter and store it in an ifstream object 

		if (!input_object)
		{
			std::cout << "ERROR!";
			std::cout << std::endl;
		}

		else break;

	}

	std::cout << std::endl;

	std::chrono::high_resolution_clock::time_point input_start = std::chrono::high_resolution_clock::now(); // staring time for algorithm

	Utils util = Utils();

	// Get parsed input

	std::pair<std::string, Graph> P = util.GetParametersAndGraph(input_object);

	std::string parameters = P.first;

	size_t pos = parameters.find(" ");

	std::string algorithm_name = parameters.substr(0, pos); // Algorithm name

	parameters.erase(0, pos + 1);

	pos = parameters.find(" ");

	int start = std::atoi((parameters.substr(0, pos)).c_str()); // Start point

	parameters.erase(0, pos + 1);

	int end = std::atoi(parameters.c_str()); // Goal point

	Graph G = P.second; // Input graph
	
	Algorithms algo;

	// Set class info

	algo.SetActiveAlgorithm(algorithm_name);

	algo.SetActiveGraph(G);

	algo.SetStart(start);

	algo.SetEnd(end);

	algo.SetHeuristicFunction();
	
	// Get overall input getting time

	std::chrono::high_resolution_clock::time_point input_end = std::chrono::high_resolution_clock::now();

	float input_time = (float)std::chrono::duration_cast<std::chrono::milliseconds>(input_end - input_start).count();

	algo.SetInputTime(input_time);

	std::string grid_dimensions = std::to_string(G.GetRowColLength());

	float time_limit_factor;
	std::string factor;

	while (1)
	{
		std::cout << "Enter a time limit factor for the algorithm (dimension is " + grid_dimensions + ")" + ": ";

		std::cin >> factor; // Get time limit factor for the algorithm form the user

		if (util.CheckIfFloat(factor) )
		{
			time_limit_factor = std::stof(factor);

			if (time_limit_factor > 0)
			{
				std::cout << std::endl;
				break;
			}

			else
			{
				std::cout << "ERROR!";
				std::cout << std::endl;
			}
		}

		else
		{
			std::cout << "ERROR!";
			std::cout << std::endl;
		}
	}

	std::cout << "Time limit = dimension * factor = " + 
		         std::to_string(float(G.GetRowColLength()) * time_limit_factor)  + " seconds" << std::endl << std::endl;

	// NOTE : The duration which takes to get the time limit does not get included in the overall running time of the algorithm 

	algo.SetTimeLimit(float(G.GetRowColLength()) * time_limit_factor); // Set time limit

	if (G.GetNeighbors(end).size() == 0 || G.GetVertexCost(start) == -1 || G.GetVertexCost(end) == -1)
	{
		std::cout << "FAILED" << std::endl; // Algorithm wont find solution within the given time limit because
		                                    // all paths to the goal vertex are blocked or the start or goal vertices are blocked

		std::string key;

		std::cout << "Press 0 To Continue..." << std::endl;

		while (1)
		{
			std::cin >> key;

			if (key._Equal("0")) break;
		}

		return 0;
	}

	algo.RunActiveAlgorithm(); // Execute algorithm

	bool status = algo.GetAlgorithmStatus();

	if(status == true) // Check if we get a solution 
	{
		// Print solution details

		std::string path = algo.GetResultPath();

		float cost = algo.GetResultCost();

		float total_time = algo.GetExecutionTime();

		int expanded = algo.GetResultExpandedVertices();

		int length = algo.GetResultLength();

		float sum = algo.GetHeristicSum();

		int min_depth = algo.GetMinSearchTreeDepth();

		int max_depth = algo.GetMaxSearchTreeDepth();

		float depths_average = algo.GetAverageSearchTreeDepth();

		std::cout << "SOLUTION DETAILS (" + algorithm_name + ") :" << std::endl << std::endl;

		std::cout << "***************************************************************************************"<< std::endl;
		std::cout << std::endl;

		std::cout << "Path : " + path << std::endl;
		std::cout << std::endl;
		std::cout << "Cost : " + std::to_string(cost) << std::endl;
		std::cout << std::endl;
		std::cout << "Number Of Expanded Vertices : " + std::to_string(expanded) << std::endl;
		std::cout << std::endl;

		std::cout << "***************************************************************************************"<< std::endl;
		std::cout << std::endl;

		std::cout << "Solution Length : " + std::to_string(length) << std::endl;
		std::cout << std::endl;
		std::cout << "Execution Time : " + std::to_string(total_time) + " seconds" << std::endl;
		std::cout << std::endl;

		if (algorithm_name._Equal("BIASTAR"))
		{
			std::pair<std::string, std::string> result_path_bidirectional = algo.GetResultPathBidirectional();
			std::string result_path_forwards = result_path_bidirectional.first;
			std::string result_path_backwards = result_path_bidirectional.second;

			std::pair<float, float> result_cost_bidirectional = algo.GetResultCostBidirectional();
			float result_cost_forwards = result_cost_bidirectional.first;
			float result_cost_backwards = result_cost_bidirectional.second;

			std::pair<int, int> expanded_bidirectional = algo.GetResultExpandedVerticesBidirectional();
			int expanded_forwards = expanded_bidirectional.first;
			int expanded_backwards = expanded_bidirectional.second;

			std::pair<int, int> length_bidirectional = algo.GetResultLengthBidirectional();
			int length_forwards = length_bidirectional.first;
			int length_backwards = length_bidirectional.second;

			std::pair<float, float> sum_bidirectional = algo.GetHeristicSumBidirectional();
			float sum_forwards = sum_bidirectional.first;
			float sum_backwards = sum_bidirectional.second;

			std::pair<int, int> min_depth_bidirectional = algo.GetMinSearchTreeDepthBidirectional();
			int min_depth_forwards = min_depth_bidirectional.first;
			int min_depth_backwards = min_depth_bidirectional.second;

			std::pair<int, int> max_depth_bidirectional = algo.GetMaxSearchTreeDepthBidirectional();
			int max_depth_forwards = max_depth_bidirectional.first;
			int max_depth_backwards = max_depth_bidirectional.second;

			std::pair<float, float> depths_average_bidirectional = algo.GetAverageSearchTreeDepthBidirectional();
			float depths_average_forwards = depths_average_bidirectional.first;
			float depths_average_backwards = depths_average_bidirectional.second;

			std::cout << std::endl;
			std::cout << "FORWARDS RUN DETAILS :" << std::endl << std::endl;

			std::cout << "Path Forwards: " + result_path_forwards << std::endl << std::endl;
			std::cout << "Cost Forwards: " + std::to_string(result_cost_forwards) << std::endl << std::endl;
			std::cout << "Number Of Expanded Vertices Forwards: " + std::to_string(expanded_forwards) << std::endl << std::endl;
			std::cout << "Solution Length Forwards: " + std::to_string(length_forwards) << std::endl << std::endl;
			std::cout << "Penetrance Forwards: " + std::to_string(float(length_forwards) / float(expanded_forwards)) << std::endl << std::endl;
			std::cout << "Heuristic Average Forwards: " + std::to_string(sum_forwards / float(expanded_forwards)) << std::endl << std::endl;
			std::cout << "Effective Branching Factor Forwards Is Approximately : " + std::to_string(std::pow(expanded_forwards, 1.0 / length_forwards)) << std::endl << std::endl;
			std::cout << "Minimum Search Tree Depth Forwards: " + std::to_string(min_depth_forwards) << std::endl << std::endl;
			std::cout << "Maximum Search Tree Depth Forwards: " + std::to_string(max_depth_forwards) << std::endl << std::endl;
			std::cout << "Average Of Search Tree Depths Forwards: " + std::to_string(depths_average_forwards) << std::endl << std::endl;

			std::cout << std::endl;
			std::cout << "BACKWARDS RUN DETAILS :" << std::endl << std::endl;

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

			if(algorithm_name._Equal("ASTAR") || algorithm_name._Equal("IDASTAR"))
			{
				std::cout << "Heursistic Average : " + std::to_string(sum / float(expanded)) << std::endl << std::endl;
			}

			std::cout << "Effective Branching Factor Is Approximately : " + std::to_string(std::pow(expanded, 1.0 / length)) << std::endl << std::endl;
			std::cout << "Minimum Search Tree Depth : " + std::to_string(min_depth) << std::endl << std::endl;
			std::cout << "Maximum Search Tree Depth : " + std::to_string(max_depth) << std::endl << std::endl;
			std::cout << "Average Of Search Tree Depths : " + std::to_string(depths_average) << std::endl << std::endl;
		}
	}

	else
	{
	        std::cout << "FAILED" << std::endl; // Algorithm failed to find solution within the given time limit
    }

	std::string key;

	std::cout << "Press 0 To Continue..." << std::endl;

	while (1)
	{
		std::cin >> key;

		if (key._Equal("0")) break;
	}
}

