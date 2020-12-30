#pragma once
#include "vector"
#include "list"
#include <string>
#include "Graph.h"
 
class Algorithms
{
public:

	Algorithms();

	void SetActiveAlgorithm(std::string algorithm);

	void SetStart(int index);

	void SetEnd(int index);

	void SetActiveGraph(const Graph& graph);

	void SetHeuristicFunction(std::string heuristic_type);

	void RunActiveAlgorithm();

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

	float OctileDistance(int vertex, int goal);

	std::string GetResultPathString(std::vector<int> result_path_values);

	void ASTAR_Search_Aux(bool threshold_flag);

	void DLS_Search(int depth);

	void IDS_Search();

	void UCS_Search();

	void ASTAR_Search();

	void IDASTAR_Search();

	void BIASTAR_Search();

private:

	Graph G;
	int start;
	int end;
	float threshold;
	std::vector<float> heuristic_function;
	float heuristic_sum;
	int min_search_tree_depth;
	int max_search_tree_depth;
	float avg_search_tree_depth;
	std::string active_algorithm;
	bool algorithm_run_status;
	int solution_length;
	float result_cost;
	std::string result_path;
	int number_of_expanded_nodes;

	std::vector<float> heuristic_function_fowards;
	float heuristic_sum_fowards;
	int solution_length_fowards;
	float result_cost_fowards;
	std::string result_path_fowards;
	int number_of_expanded_nodes_fowards;
	int min_search_tree_depth_fowards;
	int max_search_tree_depth_fowards;
	float avg_search_tree_depth_fowards;

	std::vector<float> heuristic_function_backwards;
	float heuristic_sum_backwards;
	int solution_length_backwards;
	float result_cost_backwards;
	std::string result_path_backwards;
	int number_of_expanded_nodes_backwards;
	int min_search_tree_depth_backwards;
	int max_search_tree_depth_backwards;
	float avg_search_tree_depth_backwards;
};