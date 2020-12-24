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

	void RunActiveAlgorithm();

	std::string GetResultPath() const;

	int GetResultCost() const;

	int GetResultExpandedVertices() const;

private:

	void GetResultPathString(std::vector<int> result_path_values);

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
	std::string active_algorithm;
	bool algorithm_run_status;
	int search_depth;
	int result_cost;
	std::string result_path;
	int number_of_expanded_nodes;
};