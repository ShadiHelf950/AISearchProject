#pragma once
#include "vector"
#include "list"
#include <string>
#include "Graph.h"

// Class Functionality : A class to run the graph searching algorithms 

class Algorithms
{
	/****************************************************** Functions *************************************************************/

   // NOTE : Functions explanations are in the cpp file.

public:

	Algorithms();

	void SetActiveAlgorithm(std::string algorithm);

	void SetStart(int index);

	void SetEnd(int index);

	void SetInputTime(float t_input);

	void SetTimeLimit(float limit);

	void SetActiveGraph(const Graph& graph);

	void SetHeuristicFunction();

	void RunActiveAlgorithm();

	float GetExecutionTime() const;

	bool GetAlgorithmStatus() const;

	std::string GetResultPath() const;
	
	std::pair<std::string, std::string> GetResultPathBidirectional() const;

	int GetResultLength() const;

	std::pair<int, int> GetResultLengthBidirectional() const;

	float GetHeristicSum() const;

	std::pair<float, float> GetHeristicSumBidirectional() const;

	float GetResultCost() const;

	std::pair<float, float> GetResultCostBidirectional() const;

	int GetMinSearchTreeDepth() const;

	std::pair<int, int> GetMinSearchTreeDepthBidirectional() const;

	int GetMaxSearchTreeDepth() const;

	std::pair<int, int> GetMaxSearchTreeDepthBidirectional() const;

	float GetAverageSearchTreeDepth() const;

	std::pair<float,float> GetAverageSearchTreeDepthBidirectional() const;

	int GetResultExpandedVertices() const;

	std::pair<int, int> GetResultExpandedVerticesBidirectional() const;

private:

	float ChebyshevDistance(int vertex, int goal);

	std::string GetResultPathString(std::vector<int> result_path_values);

	void ASTAR_Search_Aux(bool threshold_flag);

	void DLS_Search(int depth);

	void IDS_Search();

	void UCS_Search();

	void ASTAR_Search();

	void IDASTAR_Search();

	void BIASTAR_Search();

private:

	Graph G; // Graph which we run our algorithms on

	int start; // Starting point on the grid 

	int end;  // Ending point on the grid 

	float input_time; // Input getting time

	float execution_time; // execution time for algorithm until success of failure

	float time_limit; // time limit for algorithm execution time

	float threshold; // Threshold for f values which is used in the IDASTAR algorithm

	std::vector<float> heuristic_function; // Heuristic function for graph vertices

	float heuristic_sum; // Sum of the heuristic function values for the vertices in the solution of the algorithm

	int min_search_tree_depth; // Minimum depth of the search tree of the algorithm

	int max_search_tree_depth; // Maximum depth of the search tree of the algorithm

	float avg_search_tree_depth; // Average of depths of the search tree of the algorithm

	std::string active_algorithm; // Name of active the algorithm

	bool algorithm_run_status; // Boolean variable which indicates if the algorithm has found a solution or not

	int solution_length; // Number edges in the solution path of the algorithm

	float result_cost; // Cost of the path which is returned by the algorithm

	std::string result_path; // Result path which is returned by the algorithm

	int number_of_expanded_nodes; // Number of expanded vertices which is returned by the algorithm



    // Fields that belong exclusively to the BIASTAR algorithm :

	std::vector<float> heuristic_function_forwards; // Heuristic function for graph vertices in the forwards run

	float heuristic_sum_forwards; // Sum of the heuristic function values for the vertices in the solution of the forwards run

	int solution_length_forwards; // Number edges in the solution path of the forwards run

	float result_cost_forwards; // Cost of the path which is returned by the forwards run

	std::string result_path_forwards; // Result path which is returned by the forwards run

	int number_of_expanded_nodes_forwards; // Number of expanded vertices which is returned by the forwards run

	int min_search_tree_depth_forwards; // Minimum depth of the search tree of the forwards run

	int max_search_tree_depth_forwards; // Maximum depth of the search tree of the forwards run

	float avg_search_tree_depth_forwards; // Average of depths of the search tree of the forwards run

	std::vector<float> heuristic_function_backwards; // Heuristic function for graph vertices in the backwards run

	float heuristic_sum_backwards;  // Sum of the heuristic function values for the vertices in the solution of the backwards run

	int solution_length_backwards; // Number edges in the solution path of the backwards run

	float result_cost_backwards; // Cost of the path which is returned by the backwards run

	std::string result_path_backwards; // Result path which is returned by the backwards run

	int number_of_expanded_nodes_backwards; // Number of expanded vertices which is returned by the backwards run

	int min_search_tree_depth_backwards; // Minimum depth of the search tree of the backwards run

	int max_search_tree_depth_backwards; // Maximum depth of the search tree of the backwards run

	float avg_search_tree_depth_backwards; // Average of depths of the search tree of the backwards run
};