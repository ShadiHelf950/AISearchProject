#include "pch.h"
#include "Algorithms.h"
#include <iostream>
#include <sstream>
#include <iostream>

//Chebyshev Distance

float Algorithms::ChebyshevDistance(int vertex, int goal)
{
	float dx = std::abs((float((vertex / G.GetRowColLength())) - float((goal / G.GetRowColLength()))));
	float dy = std::abs((float((vertex % G.GetRowColLength())) - float((goal % G.GetRowColLength()))));

	if (dx >= dy) return dx;
	else return dy;
}

//Octile Distance

float Algorithms::OctileDistance(int vertex, int goal)
{
	float dx = std::abs((float((vertex / G.GetRowColLength())) - float((goal / G.GetRowColLength()))));
	float dy = std::abs((float((vertex % G.GetRowColLength())) - float((goal % G.GetRowColLength()))));

	float min;

	if (dx >= dy) return min = dy;
	else min = dx;

	return (dx + dy) + (sqrt(2) - 2) * min;
}

Algorithms::Algorithms() : G()
{
	solution_length = 0;
	result_cost = 0;
	number_of_expanded_nodes = 0;
	heuristic_sum = 0;
	result_path = "";

	result_path_fowards = "";
	result_path_backwards = "";
	result_cost_fowards = 0;
	result_cost_backwards = 0;
	solution_length_fowards = 0;
	solution_length_backwards = 0;
	number_of_expanded_nodes_fowards = 0;
	number_of_expanded_nodes_backwards = 0;
	heuristic_sum_fowards = 0;
	heuristic_sum_backwards = 0;
}

void Algorithms::SetStart(int index)
{
	start = index;
}

void Algorithms::SetEnd(int index)
{
	end = index;
}

void Algorithms::SetActiveGraph(const Graph& graph)
{
	G  = graph;
}

void Algorithms::SetHeuristicFunction(std::string heuristic_type)
{
	int i;

	if (heuristic_type._Equal("None"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function.push_back(0);
		}
	}

	else if (heuristic_type._Equal("Chebyshev Distance"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function.push_back(ChebyshevDistance(i,end));
		}
	}

	else if (heuristic_type._Equal("Chebyshev Distance Bidirectional"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function_fowards.push_back(ChebyshevDistance(i, end));
			heuristic_function_backwards.push_back(ChebyshevDistance(i, start));
		}
	}

	else if (heuristic_type._Equal("Octile Distance"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function.push_back(OctileDistance(i, end));
		}
	}

	else if (heuristic_type._Equal("Octile Distance Bidirectional"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function_fowards.push_back(OctileDistance(i, end));
			heuristic_function_backwards.push_back(OctileDistance(i, start));
		}
	}
}

void Algorithms::SetActiveAlgorithm(std::string algorithm)
{
	active_algorithm = algorithm;
}

std::string Algorithms::GetResultPathString(std::vector<int> result_path_values)
{
	int neighbor_type, previous_vertex, current_vertex;

	std::string output;

	for (unsigned i = 0; i < result_path_values.size() - 1; i++)
	{
		previous_vertex = result_path_values[i];
		current_vertex  = result_path_values[i + 1];

		neighbor_type = G.GetNeighborType(previous_vertex, current_vertex);

		if (neighbor_type == UP)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "U";
			}

			else
			{
				output += "U-";
			}
		}

		else if (neighbor_type == DOWN)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "D";
			}

			else
			{
				output += "D-";
			}
		}

		else if (neighbor_type == RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "R";
			}

			else
			{
				output += "R-";
			}
		}

		else if (neighbor_type == LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "L";
			}

			else
			{
				output += "L-";
			}
		}

		else if (neighbor_type == UPPER_RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "RU";
			}

			else
			{
				output += "RU-";
			}
		}

		else if (neighbor_type == UPPER_LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "LU";
				solution_length++;
			}

			else
			{
				output += "LU-";
			}
		}

		else if (neighbor_type == BOTTOM_RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "RD";
			}

			else
			{
				output += "RD-";
			}
		}

		else if (neighbor_type == BOTTOM_LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				output += "LD";
			}

			else
			{
				output += "LD-";
			}
		}
	}

	return output;
}

std::string Algorithms::GetResultPath() const
{
	return result_path;
}

std::pair<std::string, std::string> Algorithms::GetResultPathBidirectional() const
{
	return std::make_pair(result_path_fowards, result_path_backwards);
}

int Algorithms::GetResultLength() const
{
	return solution_length;
}

std::pair<int, int> Algorithms::GetResultLengthBidirectional() const
{
	return std::make_pair(solution_length_fowards, solution_length_backwards);
}

float Algorithms::GetHeristicSum() const
{
	return heuristic_sum;
}

std::pair<float, float> Algorithms::GetHeristicSumBidirectional() const
{
	return std::make_pair(heuristic_sum_fowards, heuristic_sum_backwards);
}

float Algorithms::GetResultCost() const
{
	return result_cost;
}

std::pair<float, float> Algorithms::GetResultCostBidirectional() const
{
	return std::make_pair(result_cost_fowards, result_cost_backwards);
}

int Algorithms::GetMinSearchTreeDepth() const
{
	return min_search_tree_depth;
}

std::pair<int, int> Algorithms::GetMinSearchTreeDepthBidirectional() const
{
	return std::make_pair(min_search_tree_depth_fowards, min_search_tree_depth_backwards);
}

int Algorithms::GetMaxSearchTreeDepth() const
{
	return max_search_tree_depth;
}

std::pair<int, int> Algorithms::GetMaxSearchTreeDepthBidirectional() const
{
	return std::make_pair(max_search_tree_depth_fowards, max_search_tree_depth_backwards);
}

float Algorithms::GetAverageSearchTreeDepth() const
{
	return avg_search_tree_depth;
}

std::pair<float, float> Algorithms::GetAverageSearchTreeDepthBidirectional() const
{
	return std::make_pair(avg_search_tree_depth_fowards, avg_search_tree_depth_backwards);
}

int Algorithms::GetResultExpandedVertices() const
{
	return number_of_expanded_nodes;
}

std::pair<int, int> Algorithms::GetResultExpandedVerticesBidirectional() const
{
	return std::make_pair(number_of_expanded_nodes_fowards,number_of_expanded_nodes_backwards);
}

void Algorithms::RunActiveAlgorithm()
{
	if(active_algorithm._Equal("IDS")) IDS_Search();

	else if(active_algorithm._Equal("UCS")) UCS_Search();

	else if(active_algorithm._Equal("ASTAR")) ASTAR_Search();

	else if(active_algorithm._Equal("IDASTAR")) IDASTAR_Search();

	else if(active_algorithm._Equal("BIASTAR")) BIASTAR_Search();
}

void Algorithms::ASTAR_Search_Aux(bool threshold_flag)
{
	min_search_tree_depth = INT_MAX;
	max_search_tree_depth = INT_MIN;

	unsigned int i, j;
	int k;
	int min_vertex_index;
	float min_vertex_cost;
	int deletion_index;
	int vertex;
	int search_tree_vertices_depth_sum = 0;
	int search_tree_vertices_count = 1;
	float current_heuristic_value;
	std::vector<int> result_path_values; // Minimum cost path values stored in a vector
	std::vector<int> visited_vertices; // Keep track on what vertices were visited
	std::vector<int> parent_vertices; // Keep track of parent
	std::vector<int> depth_vertices; // Depth of vertices in search tree
	std::vector<float> min_cost_to_vertices; // Least cost path from starting point to all vertices
	std::vector<int> min_index_queue; // Index in priority queue with minimum cost path from starting point
	std::vector<int> in_queue; // Keep track on what vertices are in the indexes queue
	std::vector<int> neighbors; // Store the neighbors  of the current vertex in this vector

	// Initialization
	for (k = 0; k < G.GetVertexCount(); k++)
	{
		visited_vertices.push_back(0);
		depth_vertices.push_back(0);
		parent_vertices.push_back(-1);
		min_cost_to_vertices.push_back(FLT_MAX);
		in_queue.push_back(0);
	}

	// Initilize the start of the queue and paths costs vector 
	min_index_queue.push_back(start);
	min_cost_to_vertices[start] = G.GetVertexCost(start);

	while (min_index_queue.empty() == false)
	{	
		// Get the vertex index in the queue which has the least cost path from the start added with heuristic value

		min_vertex_index = min_index_queue[0];
		current_heuristic_value = heuristic_function[min_index_queue[0]];
		min_vertex_cost = min_cost_to_vertices[min_index_queue[0]] + heuristic_function[min_index_queue[0]];
		deletion_index = 0;

		int end_index;

		for (j = 0; j < min_index_queue.size(); j++)
		{
			if (min_index_queue[j] == end) end_index = j; // Check if goal is in the queue
			 
			if ((min_cost_to_vertices[min_index_queue[j]] + heuristic_function[min_index_queue[j]]) < min_vertex_cost)
			{
				min_vertex_cost = (min_cost_to_vertices[min_index_queue[j]] + heuristic_function[min_index_queue[j]]);
				min_vertex_index = min_index_queue[j];
				current_heuristic_value = heuristic_function[min_index_queue[j]];
				deletion_index = j;
			}
		}

		// Check if goal index should be popped from the queue

		if ((min_cost_to_vertices[end] + heuristic_function[end]) == min_vertex_cost)
		{
			min_vertex_index = end;
			current_heuristic_value = heuristic_function[end];
			deletion_index = end_index;
		}

		heuristic_sum += current_heuristic_value;

		min_index_queue.erase(min_index_queue.begin() + deletion_index); // pop minimum index from the queue

		visited_vertices[min_vertex_index] = 1; // mark as visited

		if (threshold_flag == true) // This flag is true if we are using IDASTAR and it is false otherwise
		{
			if (min_vertex_cost > threshold)
			{
				threshold = min_vertex_cost;
				return;
			}
		}

		number_of_expanded_nodes++; // number of expanded nodes increases

		if (visited_vertices[end] == 1) // Check if goal is visited and if yes then retrieve the optimal path
		{
			vertex = end;

			while (parent_vertices[vertex] != -1) // Use parents of vertices to retrieve the optimal path
			{
				solution_length++;
				result_path_values.push_back(vertex);
				vertex = parent_vertices[vertex];
			}

			result_cost = min_cost_to_vertices[end];

			result_path_values.push_back(start);
			solution_length++;

			std::reverse(result_path_values.begin(), result_path_values.end());

			avg_search_tree_depth = float(search_tree_vertices_depth_sum) / float(search_tree_vertices_count);

			result_path = GetResultPathString(result_path_values); // Get the string which represents the optimal path

			algorithm_run_status = true; // Mark that we found a solution and exit the algorithm

			return;
		}

		neighbors = G.GetNeighbors(min_vertex_index); // Get neighbors of current vertex

		for (i = 0; i < neighbors.size(); i++)
		{
			if (visited_vertices[neighbors[i]] == 0) // Check if visited
			{
				if (in_queue[neighbors[i]] == 0) // Check if in queue
				{
					// Add to queue, update parent and set path cost to current neighbor

					in_queue[neighbors[i]] = 1;
					parent_vertices[neighbors[i]] = min_vertex_index;
					depth_vertices[neighbors[i]] = depth_vertices[min_vertex_index] + 1;
					min_cost_to_vertices[neighbors[i]] = (min_cost_to_vertices[min_vertex_index] + G.GetVertexCost(neighbors[i]));
					min_index_queue.push_back(neighbors[i]); 

					if (depth_vertices[neighbors[i]] > max_search_tree_depth) max_search_tree_depth = depth_vertices[neighbors[i]];
					if (depth_vertices[neighbors[i]] < min_search_tree_depth) min_search_tree_depth = depth_vertices[neighbors[i]];

					search_tree_vertices_depth_sum += depth_vertices[neighbors[i]];
					search_tree_vertices_count++;
				}

				else
				{
					if ((depth_vertices[min_vertex_index] + 1) > max_search_tree_depth) max_search_tree_depth = (depth_vertices[min_vertex_index] + 1);
					if ((depth_vertices[min_vertex_index] + 1) < min_search_tree_depth) min_search_tree_depth = (depth_vertices[min_vertex_index] + 1);

					search_tree_vertices_depth_sum += (depth_vertices[min_vertex_index] + 1);
					search_tree_vertices_count++;

					// Update parent and update path cost to current neighbor if needed

					if (min_cost_to_vertices[neighbors[i]] > (min_cost_to_vertices[min_vertex_index] + G.GetVertexCost(neighbors[i])))
					{
						parent_vertices[neighbors[i]] = min_vertex_index;
						min_cost_to_vertices[neighbors[i]] = (min_cost_to_vertices[min_vertex_index] + G.GetVertexCost(neighbors[i]));
					}
				}
			}
		}
	}

	algorithm_run_status = false; // Failed to find a solution
}

void Algorithms::DLS_Search(int depth)
{
	min_search_tree_depth = INT_MAX;
	max_search_tree_depth = INT_MIN;

	unsigned int i;
	int current_vertex;
	int vertex;
	int search_tree_vertices_depth_sum = 0;
	int search_tree_vertices_count = 1;
	std::vector<int> result_path_values;
	std::vector<int> visited_vertices;
	std::vector<int> depth_vertices;
	std::vector<int> parent_vertices;
	std::list<int> queue;
	std::vector<int> neighbors;

	for (int i = 0; i < G.GetVertexCount(); i++)
	{
		visited_vertices.push_back(0);
        depth_vertices.push_back(0);
		parent_vertices.push_back(-1);
	}

	queue.push_back(start);

	while (queue.empty() == false)
	{
		current_vertex = queue.front();

		queue.pop_front();

		visited_vertices[current_vertex] = 1;

		if (depth_vertices[current_vertex] > depth) continue;

		if (current_vertex == end) // Goal point reached
		{
			vertex = end;

			while (parent_vertices[vertex] != -1)
			{
				solution_length++;
				result_path_values.push_back(vertex);
				result_cost += G.GetVertexCost(vertex);

				vertex = parent_vertices[vertex];
			}

			result_cost += G.GetVertexCost(start);
			solution_length++;

			result_path_values.push_back(start);

			std::reverse(result_path_values.begin(), result_path_values.end());

			avg_search_tree_depth = float(search_tree_vertices_depth_sum) / float(search_tree_vertices_count);

			result_path = GetResultPathString(result_path_values);

			algorithm_run_status = true;  // Mark that we found a solution and exit the algorithm

			return;
		}

		neighbors = G.GetNeighbors(current_vertex);

		number_of_expanded_nodes++;

		for (i = 0; i < neighbors.size() ; i++)
		{
			if (visited_vertices[neighbors[i]] == 0)
			{
				visited_vertices[neighbors[i]] = 1;
				queue.push_back(neighbors[i]);
				depth_vertices[neighbors[i]] = depth_vertices[current_vertex] + 1;
				parent_vertices[neighbors[i]] = current_vertex;

				if (depth_vertices[neighbors[i]] > max_search_tree_depth) max_search_tree_depth = depth_vertices[neighbors[i]];
				if (depth_vertices[neighbors[i]] < min_search_tree_depth) min_search_tree_depth = depth_vertices[neighbors[i]];

				search_tree_vertices_depth_sum += depth_vertices[neighbors[i]];
				search_tree_vertices_count++;
			}
		}
	}
    
	algorithm_run_status = false; // Failed to find a solution
}

//****************************************  Main Functions  ********************************************//

void Algorithms::IDS_Search()
{
	int depth = 0;
	algorithm_run_status = false;

	while (1)
	{
		DLS_Search(depth);

		if (algorithm_run_status == true) break;

		depth++;
		number_of_expanded_nodes = 0;
	}
}

void Algorithms::UCS_Search()
{
	for (int i = 0; i < G.GetVertexCount(); i++)
	{
		heuristic_function.push_back(0);
	}

	ASTAR_Search();
}

void Algorithms::ASTAR_Search()
{
	ASTAR_Search_Aux(false);
}

void Algorithms::IDASTAR_Search()
{
	threshold = FLT_MIN;
	algorithm_run_status = false;

	while (1)
	{
		ASTAR_Search_Aux(true);

		if (algorithm_run_status == true) break;

		number_of_expanded_nodes = 0;
		heuristic_sum = 0;
	}
}

void Algorithms::BIASTAR_Search()
{
	min_search_tree_depth_fowards = INT_MAX;
	max_search_tree_depth_fowards = INT_MIN;

	min_search_tree_depth_backwards = INT_MAX;
	max_search_tree_depth_backwards = INT_MIN;

	unsigned int i, j, q;
	int k;
	int mutual_vertex;
	int vertex;
	int search_tree_vertices_depth_sum_fowards = 0;
	int search_tree_vertices_count_fowards = 1;
	int search_tree_vertices_depth_sum_backwards = 0;
	int search_tree_vertices_count_backwards = 1;
	bool identical;
	std::vector<int> result_path_values;

	// Foward A* variables

	std::vector<int> result_path_values_fowards;
	int min_vertex_index_fowards;
	float min_vertex_cost_fowards;
	float current_heuristic_value_fowards;
	int deletion_index_fowards;
	int expanded_nodes_fowards_count = 0;

	std::vector<int> visited_vertices_fowards;
	std::vector<int> parent_vertices_fowards;
	std::vector<float> min_cost_to_vertices_fowards;
	std::vector<int> min_index_queue_fowards;
	std::vector<int> in_queue_fowards;
	std::vector<int> depth_vertices_fowards;
	std::vector<int> neighbors_fowards;
	std::vector<int> candidates_fowards;

	// Backwards A* variables

	std::vector<int> result_path_values_backwards;
	int min_vertex_index_backwards;
	float min_vertex_cost_backwards;
	float current_heuristic_value_backwards;
	int deletion_index_backwards;
	int expanded_nodes_backwords_count = 0;

	std::vector<int> visited_vertices_backwards;
	std::vector<int> parent_vertices_backwards;
	std::vector<float> min_cost_to_vertices_backwards;
	std::vector<int> min_index_queue_backwards;
	std::vector<int> in_queue_backwards;
	std::vector<int> depth_vertices_backwards;
	std::vector<int> neighbors_backwards;
	std::vector<int> candidates_backwards;

	for (k = 0; k < G.GetVertexCount(); k++)
	{
		visited_vertices_fowards.push_back(0);
		in_queue_fowards.push_back(0);
		depth_vertices_fowards.push_back(0);
		parent_vertices_fowards.push_back(-1);
		min_cost_to_vertices_fowards.push_back(FLT_MAX);
		candidates_fowards.push_back(0);

		visited_vertices_backwards.push_back(0);
		in_queue_backwards.push_back(0);
		depth_vertices_backwards.push_back(0);
		parent_vertices_backwards.push_back(-1);
		min_cost_to_vertices_backwards.push_back(FLT_MAX);
		candidates_backwards.push_back(0);
	}

	min_index_queue_fowards.push_back(start);
	min_cost_to_vertices_fowards[start] = G.GetVertexCost(start);

	min_index_queue_backwards.push_back(end);
	min_cost_to_vertices_backwards[end] = G.GetVertexCost(end);

	while (min_index_queue_fowards.empty() == false && min_index_queue_backwards.empty() == false)
	{
		min_vertex_index_fowards = min_index_queue_fowards[0];
		min_vertex_cost_fowards = min_cost_to_vertices_fowards[min_index_queue_fowards[0]] + heuristic_function_fowards[min_index_queue_fowards[0]];
		current_heuristic_value_fowards = heuristic_function_fowards[min_index_queue_fowards[0]];
		deletion_index_fowards = 0;

		for (j = 0; j < min_index_queue_fowards.size(); j++)
		{
			if ((min_cost_to_vertices_fowards[min_index_queue_fowards[j]] + heuristic_function_fowards[min_index_queue_fowards[j]]) < min_vertex_cost_fowards)
			{
				min_vertex_cost_fowards = (min_cost_to_vertices_fowards[min_index_queue_fowards[j]] + heuristic_function_fowards[min_index_queue_fowards[j]]);
				min_vertex_index_fowards = min_index_queue_fowards[j];
				current_heuristic_value_fowards = heuristic_function_fowards[min_index_queue_fowards[j]];
				deletion_index_fowards = j;
			}
		}

		std::fill(candidates_fowards.begin(), candidates_fowards.end(), 0);

		for (i = 0; i < min_index_queue_fowards.size(); i++)
		{
			if (min_cost_to_vertices_fowards[min_index_queue_fowards[i]] + heuristic_function_fowards[min_index_queue_fowards[i]] == min_vertex_cost_fowards)
			{
				candidates_fowards[min_index_queue_fowards[i]] = 1;
			}
		}

		min_vertex_index_backwards = min_index_queue_backwards[0];
		min_vertex_cost_backwards = min_cost_to_vertices_backwards[min_index_queue_backwards[0]] + heuristic_function_backwards[min_index_queue_backwards[0]];
		current_heuristic_value_backwards = heuristic_function_backwards[min_index_queue_backwards[0]];
		deletion_index_backwards = 0;

		for (j = 0; j < min_index_queue_backwards.size(); j++)
		{
			if ((min_cost_to_vertices_backwards[min_index_queue_backwards[j]] + heuristic_function_backwards[min_index_queue_backwards[j]]) < min_vertex_cost_backwards)
			{
				min_vertex_cost_backwards = (min_cost_to_vertices_backwards[min_index_queue_backwards[j]] + heuristic_function_backwards[min_index_queue_backwards[j]]);
				min_vertex_index_backwards = min_index_queue_backwards[j];
				current_heuristic_value_backwards = heuristic_function_backwards[min_index_queue_backwards[j]];
				deletion_index_backwards = j;
			}
		}

		std::fill(candidates_backwards.begin(), candidates_backwards.end(), 0);

		for (i = 0; i < min_index_queue_backwards.size(); i++)
		{
			if (min_cost_to_vertices_backwards[min_index_queue_backwards[i]] + heuristic_function_backwards[min_index_queue_backwards[i]] == min_vertex_cost_backwards)
			{
				candidates_backwards[min_index_queue_backwards[i]] = 1;
			}
		}

		identical = false;

		for (k = 0; k < G.GetVertexCount(); k++)
		{
			if (candidates_fowards[k] == 1 && candidates_backwards[k] == 1)
			{
				min_vertex_index_fowards = k;
				min_vertex_index_backwards = k;
				current_heuristic_value_fowards = heuristic_function_fowards[k];
				current_heuristic_value_backwards = heuristic_function_backwards[k];
				identical = true;
				break;
			}
		}

		if (identical == true)
		{
			for (j = 0; j < min_index_queue_fowards.size(); j++)
			{
				if (min_vertex_index_fowards == min_index_queue_fowards[j])
				{
					deletion_index_fowards = j;
					break;
				}
			}

			for (j = 0; j < min_index_queue_backwards.size(); j++)
			{
				if (min_vertex_index_backwards == min_index_queue_backwards[j])
				{
					deletion_index_backwards = j;
					break;
				}
			}
		}

		heuristic_sum_fowards += current_heuristic_value_fowards;

		heuristic_sum_backwards += current_heuristic_value_backwards;

		min_index_queue_fowards.erase(min_index_queue_fowards.begin() + deletion_index_fowards);

		min_index_queue_backwards.erase(min_index_queue_backwards.begin() + deletion_index_backwards);

		visited_vertices_fowards[min_vertex_index_fowards] = 1;

		visited_vertices_backwards[min_vertex_index_backwards] = 1;

		in_queue_fowards[min_vertex_index_fowards] = 0;

		in_queue_backwards[min_vertex_index_backwards] = 0;

		expanded_nodes_fowards_count++;

		expanded_nodes_backwords_count++;

		if (min_vertex_index_fowards == min_vertex_index_backwards)
		{
			mutual_vertex = min_vertex_index_fowards;

			vertex = parent_vertices_fowards[mutual_vertex];

			while (parent_vertices_fowards[vertex] != -1)
			{
				solution_length_fowards++;
				solution_length++;
				result_path_values_fowards.push_back(vertex);
				vertex = parent_vertices_fowards[vertex];
			}

			result_path_values_fowards.push_back(start);
			solution_length_fowards++;
			solution_length++;

			std::reverse(result_path_values_fowards.begin(), result_path_values_fowards.end());

			result_path_values_fowards.push_back(mutual_vertex);

			result_path_fowards = GetResultPathString(result_path_values_fowards);

			result_path_fowards.append(" (Path begins at " + 
			std::to_string(start / G.GetRowColLength()) + "," + std::to_string(start % G.GetRowColLength()) + 
			" and ends at " + std::to_string(mutual_vertex / G.GetRowColLength()) + "," + std::to_string(mutual_vertex % G.GetRowColLength()) + ")");

			result_path_values_fowards.pop_back();

			vertex = mutual_vertex;

			while (parent_vertices_backwards[vertex] != -1)
			{
				solution_length_backwards++;
				solution_length++;
				result_path_values_backwards.push_back(vertex);
				vertex = parent_vertices_backwards[vertex];
			}

			result_path_values_backwards.push_back(end);
			solution_length_backwards++;
			solution_length++;

			result_path_backwards = GetResultPathString(result_path_values_backwards);

			result_path_backwards.append(" (Path begins at " +
			std::to_string(mutual_vertex / G.GetRowColLength()) + "," + std::to_string(mutual_vertex % G.GetRowColLength()) +
			" and ends at " + std::to_string(end / G.GetRowColLength()) + "," + std::to_string(end % G.GetRowColLength()) + ")");

			for (q = 0; q < result_path_values_fowards.size(); q++)
			{
				result_path_values.push_back(result_path_values_fowards[q]);
			}

			for (q = 0; q < result_path_values_backwards.size(); q++)
			{
				result_path_values.push_back(result_path_values_backwards[q]);
			}

			solution_length--;

			avg_search_tree_depth_fowards = float(search_tree_vertices_depth_sum_fowards) / float(search_tree_vertices_count_fowards);

			avg_search_tree_depth_backwards = float(search_tree_vertices_depth_sum_backwards) / float(search_tree_vertices_count_backwards);

			result_path = GetResultPathString(result_path_values);

			result_cost = min_cost_to_vertices_fowards[mutual_vertex] + min_cost_to_vertices_backwards[mutual_vertex] - G.GetVertexCost(mutual_vertex);

			result_cost_fowards = min_cost_to_vertices_fowards[mutual_vertex];

			result_cost_backwards = min_cost_to_vertices_backwards[mutual_vertex];

			number_of_expanded_nodes_fowards = expanded_nodes_fowards_count;

			number_of_expanded_nodes_backwards = expanded_nodes_backwords_count;

			number_of_expanded_nodes = expanded_nodes_fowards_count + expanded_nodes_backwords_count;

			algorithm_run_status = true;
			return;
		}

		neighbors_fowards = G.GetNeighbors(min_vertex_index_fowards);

		for (i = 0; i < neighbors_fowards.size(); i++)
		{
			if (visited_vertices_fowards[neighbors_fowards[i]] == 0)
			{
				if (in_queue_fowards[neighbors_fowards[i]] == 1)
				{
					if (min_cost_to_vertices_fowards[neighbors_fowards[i]] > (min_cost_to_vertices_fowards[min_vertex_index_fowards] + G.GetVertexCost(neighbors_fowards[i])))
					{
						parent_vertices_fowards[neighbors_fowards[i]] = min_vertex_index_fowards;
						min_cost_to_vertices_fowards[neighbors_fowards[i]] = (min_cost_to_vertices_fowards[min_vertex_index_fowards] + G.GetVertexCost(neighbors_fowards[i]));
					}

					if ((depth_vertices_fowards[min_vertex_index_fowards] + 1) > max_search_tree_depth_fowards) max_search_tree_depth_fowards = (depth_vertices_fowards[min_vertex_index_fowards] + 1);
					if ((depth_vertices_fowards[min_vertex_index_fowards] + 1) < min_search_tree_depth_fowards) min_search_tree_depth_fowards = (depth_vertices_fowards[min_vertex_index_fowards] + 1);

					search_tree_vertices_depth_sum_fowards += (depth_vertices_fowards[min_vertex_index_fowards] + 1);
					search_tree_vertices_count_fowards++;
				}

				else
				{
					in_queue_fowards[neighbors_fowards[i]] = 1;
					min_index_queue_fowards.push_back(neighbors_fowards[i]);
					parent_vertices_fowards[neighbors_fowards[i]] = min_vertex_index_fowards;
					depth_vertices_fowards[neighbors_fowards[i]] = depth_vertices_fowards[min_vertex_index_fowards] + 1;
					min_cost_to_vertices_fowards[neighbors_fowards[i]] = (min_cost_to_vertices_fowards[min_vertex_index_fowards] + G.GetVertexCost(neighbors_fowards[i]));

					if (depth_vertices_fowards[neighbors_fowards[i]] > max_search_tree_depth_fowards) max_search_tree_depth_fowards = depth_vertices_fowards[neighbors_fowards[i]];
					if (depth_vertices_fowards[neighbors_fowards[i]] < min_search_tree_depth_fowards) min_search_tree_depth_fowards = depth_vertices_fowards[neighbors_fowards[i]];

					search_tree_vertices_depth_sum_fowards += depth_vertices_fowards[neighbors_fowards[i]];
					search_tree_vertices_count_fowards++;
				}
			}
		}

		neighbors_backwards = G.GetNeighbors(min_vertex_index_backwards);

		for (i = 0; i < neighbors_backwards.size(); i++)
		{
			if (visited_vertices_backwards[neighbors_backwards[i]] == 0)
			{
				if (in_queue_backwards[neighbors_backwards[i]] == 1)
				{
					if (min_cost_to_vertices_backwards[neighbors_backwards[i]] > (min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i])))
					{
						parent_vertices_backwards[neighbors_backwards[i]] = min_vertex_index_backwards;
						min_cost_to_vertices_backwards[neighbors_backwards[i]] = min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i]);
					}

					if ((depth_vertices_backwards[min_vertex_index_backwards] + 1) > max_search_tree_depth_backwards) max_search_tree_depth_backwards = (depth_vertices_backwards[min_vertex_index_backwards] + 1);
					if ((depth_vertices_backwards[min_vertex_index_backwards] + 1) < min_search_tree_depth_backwards) min_search_tree_depth_backwards = (depth_vertices_backwards[min_vertex_index_backwards] + 1);

					search_tree_vertices_depth_sum_backwards += (depth_vertices_backwards[min_vertex_index_backwards] + 1);
					search_tree_vertices_count_backwards++;
				}

				else
				{
					in_queue_backwards[neighbors_backwards[i]] = 1;
					min_index_queue_backwards.push_back(neighbors_backwards[i]);
					parent_vertices_backwards[neighbors_backwards[i]] = min_vertex_index_backwards;
					depth_vertices_backwards[neighbors_backwards[i]] = depth_vertices_backwards[min_vertex_index_backwards] + 1;
					min_cost_to_vertices_backwards[neighbors_backwards[i]] = min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i]);

					if (depth_vertices_backwards[neighbors_backwards[i]] > max_search_tree_depth_backwards) max_search_tree_depth_backwards = depth_vertices_backwards[neighbors_backwards[i]];
					if (depth_vertices_backwards[neighbors_backwards[i]] < min_search_tree_depth_backwards) min_search_tree_depth_backwards = depth_vertices_backwards[neighbors_backwards[i]];

					search_tree_vertices_depth_sum_backwards += depth_vertices_backwards[neighbors_backwards[i]];
					search_tree_vertices_count_backwards++;

				}
			}
		}
	}

	algorithm_run_status = false;
}


