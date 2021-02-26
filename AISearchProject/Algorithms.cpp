#include "pch.h"
#include "Algorithms.h"
#include <iostream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <algorithm>

// My Best Heuristic :

//ChebyshevDistance(int vertex, int goal) :

// Purpose:
// Calculate the Chebyshev distance between the current graph vertex and the goal vertex

// Parameters:
// 1.  vertex : A graph vertex
// 2.  goal : The goal vertex of the graph

// Return Value:
// Maximum between the absolute value of the difference between x coordinate and y coordinate of the current graph vertex and the
// goal vertex

float Algorithms::ChebyshevDistance(int vertex, int goal)
{
	float dx = std::abs((float((vertex / G.GetRowColLength())) - float((goal / G.GetRowColLength()))));
	float dy = std::abs((float((vertex % G.GetRowColLength())) - float((goal % G.GetRowColLength()))));

	if (dx >= dy) return dx;
	else return dy;
}



/*************************************************** Class Functions *******************************************************/


// Algorithms() : 

// Purpose :
// Default constructor for the Algorithms class

// Parameters : None

// Return Value : None

Algorithms::Algorithms() : G()
{
	// Initilaize results of IDS, UCS, ASTAR, IDASTAR

	solution_length = 0;
	result_cost = 0;
	number_of_expanded_nodes = 0;
	heuristic_sum = 0;
	result_path = "";

	// Initilaize results BIASTAR

	result_path_forwards = "";
	result_path_backwards = "";
	result_cost_forwards = 0;
	result_cost_backwards = 0;
	solution_length_forwards = 0;
	solution_length_backwards = 0;
	number_of_expanded_nodes_forwards = 0;
	number_of_expanded_nodes_backwards = 0;
	heuristic_sum_forwards = 0;
	heuristic_sum_backwards = 0;
}



// SetStart(int index) :

// Purpose :
// Set function for the grid start field

// Parameters :
// 1. index : Initial vertex for grid searching

// Return Value: None

void Algorithms::SetStart(int index)
{
	start = index;
}



// SetEnd(int index) :

// Purpose :
// Set function for the grid end field

// Parameters :
// 1. index : Goal vertex for grid searching

// Return Value : None

void Algorithms::SetEnd(int index)
{
	end = index;
}



// SetInputTime(float t_input) :

// Purpose :
// Set function for the input getting time field

// Parameters :
// 1. t_input : Input getting time

// Return Value : None

void Algorithms::SetInputTime(float t_input)
{
	input_time = t_input;
}



// SetTimeLimit(float limit) :

// Purpose :
// Set function for the time_limit field

// Parameters :
// 1. limit : time limit for searching algorithms execution time

// Return Value : None

void Algorithms::SetTimeLimit(float limit)
{
	time_limit = limit;
}



// SetActiveGraph(const Graph& graph) :

// Purpose :
// Set function for the G field

// Parameters :
// 1. graph : Graph object for searching algorithms

// Return Value : None

void Algorithms::SetActiveGraph(const Graph& graph)
{
	G  = graph;
}



// SetHeuristicFunction(std::string heuristic_type) : 

// Purpose :
// Set function for the heuristic_function field if we use ASTAR or IDASTAR 
// or for heuristic_function_forwards and heuristic_function_backwards fields if we use BIASTAR
// ( Calculates heuristic value for every graph vertex ).

// Parameters : None

// Return Value : None

void Algorithms::SetHeuristicFunction()
{
	int i;

	if (active_algorithm._Equal("UCS")) // If we use UCS then we use the 0 heuristic 
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function.push_back(0);
		}
	}

	// If we use ASTAR or IDASTAR then we use the Chebyshev distance heuristic
	
	else if (active_algorithm._Equal("ASTAR") || active_algorithm._Equal("IDASTAR"))
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function.push_back(ChebyshevDistance(i,end));
		}
	}

	// If we use BIASTAR then we use the Chebyshev distance heuristic for both forwards and backwards runs

	else if (active_algorithm._Equal("BIASTAR")) 
	{
		for (i = 0; i < G.GetVertexCount(); i++)
		{
			heuristic_function_forwards.push_back(ChebyshevDistance(i, end)); // Chebyshev distance for forwards run 
			heuristic_function_backwards.push_back(ChebyshevDistance(i, start)); // Chebyshev distance for backwards run 
		}
	}
}



// SetActiveAlgorithm(std::string algorithm) : 

// Purpose :
// Set function for the active_algorithm field ( Set which search algorithm to run )

// Parameters :
// 1. algorithm : Algorithm name (IDS, UCS, ASTAR, IDASTAR, BIASTAR)

// Return Value : None

void Algorithms::SetActiveAlgorithm(std::string algorithm)
{
	active_algorithm = algorithm;
}



// GetResultPathString(std::vector<int> result_path_values) : 

// Purpose :
// Creates result string which represents the solution path from start to goal given path vertices vector as input

// Parameters :
// 1. result_path_values : Vector of the indexes which represent the vertices of the solution path

// Return Value : A result string which represents the solution path from start to goal

std::string Algorithms::GetResultPathString(std::vector<int> result_path_values)
{
	int neighbor_type, previous_vertex, current_vertex; // Local variables

	std::string output; // Return value

	for (unsigned i = 0; i < result_path_values.size() - 1; i++)
	{
		previous_vertex = result_path_values[i]; // Previous vertex in solution path
		current_vertex  = result_path_values[i + 1]; // Current vertex in solution path ( neighbor of the previous vertex )

		// Get the type of the neighbor that current_vertex is to previous_vertex and based on which
		// type of neighbor it is we append the corresponding grid step to the output string. 

		neighbor_type = G.GetNeighborType(previous_vertex, current_vertex);

		if (neighbor_type == UP)
		{
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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
			if (i == result_path_values.size() - 2) // Last vertex in path
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



// GetResultPath() : 

// Purpose :
// Get function for the result_path field ( get the solution path string for the grid )

// Parameters : None

// Return Value : Solution path string

std::string Algorithms::GetResultPath() const
{
	return result_path;
}



// GetResultPathBidirectional() : 

// Purpose :
// Get function for the result_path_backwards and result_path_forwards fields ( get the solution path string for the grid
// for both the forwards and backwards runs of the the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of solution path strings for the forwards and backwards runs of the BIASTAR algorithm 

std::pair<std::string, std::string> Algorithms::GetResultPathBidirectional() const
{
	return std::make_pair(result_path_forwards, result_path_backwards);
}



// GetResultLength() : 

// Purpose :
// Get function for the solution_length field ( get the solution path length for the grid )

// Parameters : None

// Return Value : Length of solution path

int Algorithms::GetResultLength() const
{
	return solution_length;
}



// GetResultLengthBidirectional() : 

// Purpose :
// Get function for the solution_length_backwards and solution_length_forwards fields ( get the solution path length for the grid
// for both the forwards and backwards runs of the the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of solution path lengths for the forwards and backwards runs of the BIASTAR algorithm 

std::pair<int, int> Algorithms::GetResultLengthBidirectional() const
{
	return std::make_pair(solution_length_forwards, solution_length_backwards);
}



// GetHeristicSum()() : 

// Purpose :
// Get function for the heuristic_sum field ( get the solution path heuristic function sum for the path's vertices )

// Parameters : None

// Return Value : Heuristic function sum for the solution path's vertices

float Algorithms::GetHeristicSum() const
{
	return heuristic_sum;
}



// GetHeristicSumBidirectional() : 

// Purpose :
// Get function for the heuristic_sum_backwards and heuristic_sum_forwards fields ( get the solution path heuristic function
// sum for the path's vertices for both the forwards and backwards runs of the the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of heuristic function sum for the path's vertices for both the forwards and backwards runs
// of the the BIASTAR algorithm

std::pair<float, float> Algorithms::GetHeristicSumBidirectional() const
{
	return std::make_pair(heuristic_sum_forwards, heuristic_sum_backwards);
}



// GetResultCost() : 

// Purpose :
// Get function for the result_cost field ( get the solution path cost for the grid )

// Parameters : None

// Return Value : Cost of solution path 

float Algorithms::GetResultCost() const
{
	return result_cost;
}



// GetResultCostBidirectional() : 

// Purpose :
// Get function for the result_cost_backwards and result_cost_forwards fields ( get the solution path cost for the grid
// for both the forwards and backwards runs of the the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of solution path costs for the forwards and backwards runs of the BIASTAR algorithm 

std::pair<float, float> Algorithms::GetResultCostBidirectional() const
{
	return std::make_pair(result_cost_forwards, result_cost_backwards);
}



// GetMinSearchTreeDepth() : 

// Purpose :
// Get function for the min_search_tree_depth field ( get the minimum depth for the search tree of the current searching algorithm )

// Parameters : None

// Return Value : Minimum depth for the search tree of the current searching algorithm

int Algorithms::GetMinSearchTreeDepth() const
{
	return min_search_tree_depth;
}



// GetMinSearchTreeDepthBidirectional() : 

// Purpose :
// Get function for the min_search_tree_depth_backwards and min_search_tree_depth_forwards fields
// ( get the minimum depth for the search trees of the forwards and backwards runs of the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of minimum depth for the search trees of the forwards and backwards runs of the BIASTAR algorithm

std::pair<int, int> Algorithms::GetMinSearchTreeDepthBidirectional() const
{
	return std::make_pair(min_search_tree_depth_forwards, min_search_tree_depth_backwards);
}



// GetMaxSearchTreeDepth() : 

// Purpose :
// Get function for the max_search_tree_depth field ( get the maximum depth for the search tree of the current searching algorithm )

// Parameters : None

// Return Value : Maximum depth for the search tree of the current searching algorithm

int Algorithms::GetMaxSearchTreeDepth() const
{
	return max_search_tree_depth;
}



// GetMaxSearchTreeDepthBidirectional() : 

// Purpose :
// Get function for the max_search_tree_depth_backwards and max_search_tree_depth_forwards fields
// ( get the maximum depth for the search trees of the forwards and backwards runs of the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of maximum depth for the search trees of the forwards and backwards runs of the BIASTAR algorithm

std::pair<int, int> Algorithms::GetMaxSearchTreeDepthBidirectional() const
{
	return std::make_pair(max_search_tree_depth_forwards, max_search_tree_depth_backwards);
}



// GetAverageSearchTreeDepth() : 

// Purpose :
// Get function for the avg_search_tree_depth field ( get the average of depths for the search tree of the 
// current searching algorithm )

// Parameters : None

// Return Value : Average of depths for the search tree of the current searching algorithm

float Algorithms::GetAverageSearchTreeDepth() const
{
	return avg_search_tree_depth;
}



// GetAverageSearchTreeDepthBidirectional() : 

// Purpose :
// Get function for the avg_search_tree_depth_backwards and avg_search_tree_depth_forwards fields
// ( get the average of depths for the search trees of the forwards and backwards runs of the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of average of depths for the search trees of the forwards and backwards runs of the BIASTAR algorithm

std::pair<float, float> Algorithms::GetAverageSearchTreeDepthBidirectional() const
{
	return std::make_pair(avg_search_tree_depth_forwards, avg_search_tree_depth_backwards);
}



// GetResultExpandedVertices() : 

// Purpose :
// Get function for the number_of_expanded_nodes ( get the number of expanded nodes of the solution )

// Parameters : None

// Return Value : The number of expanded nodes of the solution

int Algorithms::GetResultExpandedVertices() const
{
	return number_of_expanded_nodes;
}



// GetResultExpandedVerticesBidirectional() : 

// Purpose :
// Get function for the number_of_expanded_nodes_backwards and number_of_expanded_nodes_forwards fields
// ( get the number of expanded nodes for the forwards and backwards runs of the BIASTAR algorithm)

// Parameters : None

// Return Value : A pair of the number of expanded nodes for the forwards and backwards runs of the BIASTAR algorithm

std::pair<int, int> Algorithms::GetResultExpandedVerticesBidirectional() const
{
	return std::make_pair(number_of_expanded_nodes_forwards,number_of_expanded_nodes_backwards);
}



// RunActiveAlgorithm() : 

// Purpose :
// Run the current active search algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::RunActiveAlgorithm()
{
	if (active_algorithm._Equal("IDS"))
	{
		IDS_Search();
	}

	else if (active_algorithm._Equal("UCS"))
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

		UCS_Search();

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

		execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + input_time;

		execution_time /= 1000; // convert into seconds

		if (execution_time > time_limit) algorithm_run_status = false;
	}

	else if (active_algorithm._Equal("ASTAR"))
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

		ASTAR_Search();

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

		execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + +input_time;

		execution_time /= 1000; // convert into seconds

		if (execution_time > time_limit) algorithm_run_status = false;
	}

	else if (active_algorithm._Equal("IDASTAR"))
	{
		IDASTAR_Search();
	}

	else if (active_algorithm._Equal("BIASTAR"))
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

		BIASTAR_Search();

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

		execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + +input_time;

		execution_time /= 1000; // convert into seconds

		if (execution_time > time_limit) algorithm_run_status = false;
	}
}



// GetExecutionTime() : 

// Purpose :
// Get function for the execution_time field ( get execution time of the current searching algorithm )

// Parameters : None

// Return Value : Execution time of the current searching algorithm 


float Algorithms::GetExecutionTime() const
{
	return execution_time;
}



// GetAlgorithmStatus() : 

// Purpose :
// Get function for the algorithm_run_status field ( get success/failure status the current searching algorithm )

// Parameters : None

// Return Value : Success/Failure status the current searching algorithm

bool Algorithms::GetAlgorithmStatus() const
{
	return algorithm_run_status;
}



// ASTAR_Search_Aux(bool threshold_flag) : 

// Purpose :
// Run the ASTAR algorithm with an option to run until a certain threshold on the current active graph 

// Parameters :
// 1. threshold_flag : A flag which determines if we run normal ASTAR or we run ASTAR until a certain threshold ( part of IDASTAR )

// Return Value : None

void Algorithms::ASTAR_Search_Aux(bool threshold_flag)
{
	min_search_tree_depth = INT_MAX;
	max_search_tree_depth = INT_MIN;

	// Loop variables

	unsigned int i, j;
	int k;

	// Other variables

	int min_vertex_index; // Index of vertex with minimum f function value
	float min_vertex_cost; // Value of the current minimum f function value
	int deletion_index; // Actual index of min_vertex_index in the priority queue
	int vertex;
	int search_tree_vertices_depth_sum = 0;
	int search_tree_vertices_count = 1;
	float current_heuristic_value;
	std::vector<int> result_path_values; // Minimum cost path values stored in a vector
	std::vector<int> visited_vertices; // Keep track on what vertices were visited
	std::vector<int> parent_vertices; // Keep track of parent
	std::vector<int> depth_vertices; // Depth of vertices in search tree
	std::vector<float> min_cost_to_vertices; // Least cost path from starting point to all vertices
	std::vector<int> min_index_queue; // Priority queue for vertices with minimum f values
	std::vector<int> in_queue; // Keep track on what vertices are in the indexes queue
	std::vector<int> neighbors; // Store the neighbors of the current vertex in this vector

	// Initialization of vectors
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
		// Get the vertex index in the queue which has the least cost path from the start added with heuristic value ( f value )

		min_vertex_index = min_index_queue[0];
		current_heuristic_value = heuristic_function[min_index_queue[0]];
		min_vertex_cost = min_cost_to_vertices[min_index_queue[0]] + heuristic_function[min_index_queue[0]];
		deletion_index = 0;

		int end_index;

		for (j = 0; j < min_index_queue.size(); j++)
		{
			if (min_index_queue[j] == end) end_index = j; // Check if goal vertex is in the queue
			 
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

		heuristic_sum += current_heuristic_value; // Update heuristic sum of expanded nodes

		min_index_queue.erase(min_index_queue.begin() + deletion_index); // Pop minimum index from the queue

		visited_vertices[min_vertex_index] = 1; // Mark current vertex as visited

		if (threshold_flag == true) // This flag is true if we are using IDASTAR and it is false otherwise
		{
			if (min_vertex_cost > threshold)
			{
				threshold = min_vertex_cost; // Set new threshold for IDASTAR and exit the current IDASTAR iteration
				return;
			}
		}

		number_of_expanded_nodes++;

		if (visited_vertices[end] == 1) // Check if goal is visited and if yes then retrieve the optimal path
		{
			vertex = end;

			while (parent_vertices[vertex] != -1) // Use parents of vertices to retrieve the optimal path vertices in a vector
			{
				solution_length++;
				result_path_values.push_back(vertex);
				vertex = parent_vertices[vertex];
			}

			result_cost = min_cost_to_vertices[end] - G.GetVertexCost(start);

			result_path_values.push_back(start); // Add the starting point of the grid to the vertices vector
			solution_length++;

			std::reverse(result_path_values.begin(), result_path_values.end()); // Reverse the vertices vector

			// Calculate the average of search tree depths

			avg_search_tree_depth = float(search_tree_vertices_depth_sum) / float(search_tree_vertices_count);

			result_path = GetResultPathString(result_path_values); // Get the string which represents the optimal path

			algorithm_run_status = true; // Mark that we found a solution and exit the algorithm

			return;
		}

		neighbors = G.GetNeighbors(min_vertex_index); // Get neighbors of current vertex

		for (i = 0; i < neighbors.size(); i++)
		{
			if (visited_vertices[neighbors[i]] == 0) // Check if current neighbor visited
			{
				if (in_queue[neighbors[i]] == 0) // Check if current neighbor in queue
				{
					// Add to queue, update parent, depth and set path cost to current neighbor

					in_queue[neighbors[i]] = 1;
					parent_vertices[neighbors[i]] = min_vertex_index;
					depth_vertices[neighbors[i]] = depth_vertices[min_vertex_index] + 1;
					min_cost_to_vertices[neighbors[i]] = (min_cost_to_vertices[min_vertex_index] + G.GetVertexCost(neighbors[i]));
					min_index_queue.push_back(neighbors[i]); 

					// Update the max and min of search tree depths

					if (depth_vertices[neighbors[i]] > max_search_tree_depth) max_search_tree_depth = depth_vertices[neighbors[i]];
					if (depth_vertices[neighbors[i]] < min_search_tree_depth) min_search_tree_depth = depth_vertices[neighbors[i]];

					// Update the sum and of search tree depths and the number of vertices in the search tree

					search_tree_vertices_depth_sum += depth_vertices[neighbors[i]];
					search_tree_vertices_count++;
				}

				else
				{
					// Update the max and min of search tree depths

					if ((depth_vertices[min_vertex_index] + 1) > max_search_tree_depth) max_search_tree_depth = (depth_vertices[min_vertex_index] + 1);
					if ((depth_vertices[min_vertex_index] + 1) < min_search_tree_depth) min_search_tree_depth = (depth_vertices[min_vertex_index] + 1);

					// Update the sum and of search tree depths and the number of vertices in the search tree

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



// DLS_Search(int depth) : 

// Purpose :
// Run Depth Limited Search (DLS) algorithm until we reach a maximum given depth 

// Parameters :
// 1. depth : A depth limit for the DLS algorithm. We do not expand vertices with a bigger depth than this parameter

// Return Value : None

void Algorithms::DLS_Search(int depth)
{
	min_search_tree_depth = INT_MAX;
	max_search_tree_depth = INT_MIN;

	unsigned int i;
	int current_vertex;
	int vertex;
	int search_tree_vertices_depth_sum = 0;
	int search_tree_vertices_count = 1;
	std::vector<int> result_path_values; //  Solution path costs stored in a vector
	std::vector<int> visited_vertices; // Keep track on what vertices were visited
	std::vector<int> depth_vertices; // Depth of vertices in search tree
	std::vector<int> parent_vertices; // Keep track of parent
	std::list<int> queue; // Queue for graph vertices
	std::vector<int> neighbors; // Store the neighbors of the current vertex in this vector

    // Initialization of vectors
	for (int i = 0; i < G.GetVertexCount(); i++)
	{
		visited_vertices.push_back(0);
        depth_vertices.push_back(0);
		parent_vertices.push_back(-1);
	}

	// Initilize the start of the queue
	queue.push_back(start);

	while (queue.empty() == false)
	{
		current_vertex = queue.front(); // Get first queue element

		queue.pop_front(); // Delete it from the queue

		visited_vertices[current_vertex] = 1; // Mark current element as visited

		if (depth_vertices[current_vertex] > depth) continue; // Check if we go over the depth limit

		if (current_vertex == end) // Goal point reached
		{
			vertex = end;

			while (parent_vertices[vertex] != -1) // Use parents of vertices to retrieve the solution path vertices in a vector
			{
				solution_length++;
				result_path_values.push_back(vertex);
				result_cost += G.GetVertexCost(vertex);

				vertex = parent_vertices[vertex];
			}

			solution_length++;

			result_path_values.push_back(start); // Add the starting point of the grid to the vertices vector

			std::reverse(result_path_values.begin(), result_path_values.end()); // Reverse the vertices vector

			// Calculate the average of search tree depths

			avg_search_tree_depth = float(search_tree_vertices_depth_sum) / float(search_tree_vertices_count);

			result_path = GetResultPathString(result_path_values); // Get the string which represents the solution path

			algorithm_run_status = true;  // Mark that we found a solution and exit the algorithm

			return;
		}

		neighbors = G.GetNeighbors(current_vertex); // Get neighbors of current vertex

		number_of_expanded_nodes++;

		for (i = 0; i < neighbors.size() ; i++)
		{
			if (visited_vertices[neighbors[i]] == 0) // Check if current neighbor visited
			{
				// Add to queue, update parent, depth and mark current neighbor as visited

				visited_vertices[neighbors[i]] = 1;
				queue.push_back(neighbors[i]);
				depth_vertices[neighbors[i]] = depth_vertices[current_vertex] + 1;
				parent_vertices[neighbors[i]] = current_vertex;

				// Update the max and min of search tree depths

				if (depth_vertices[neighbors[i]] > max_search_tree_depth) max_search_tree_depth = depth_vertices[neighbors[i]];
				if (depth_vertices[neighbors[i]] < min_search_tree_depth) min_search_tree_depth = depth_vertices[neighbors[i]];

				// Update the sum and of search tree depths and the number of vertices in the search tree

				search_tree_vertices_depth_sum += depth_vertices[neighbors[i]];
				search_tree_vertices_count++;
			}
		}
	}

	algorithm_run_status = false;  // Failed to find a solution
}



// IDS_Search() : 

// Purpose :
// Run the IDS algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::IDS_Search()
{
	int depth = 0;
	algorithm_run_status = false;

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	std::chrono::high_resolution_clock::time_point end;

	while (1)
	{
		DLS_Search(depth);

		if (algorithm_run_status == true) break; // Break out of the infinite loop if we find a solution

		end = std::chrono::high_resolution_clock::now();

		execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + input_time;

		execution_time /= 1000; // convert into seconds

		if (execution_time > time_limit) return;

		depth++; // Update iteration depth
		number_of_expanded_nodes = 0; // Reset expanded vertices count
	}

	end = std::chrono::high_resolution_clock::now();

	execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + input_time;

	execution_time /= 1000; // convert into seconds

	if (execution_time > time_limit) algorithm_run_status = false;
}



// UCS_Search() : 

// Purpose :
// Run the UCS algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::UCS_Search()
{
	for (int i = 0; i < G.GetVertexCount(); i++)
	{
		heuristic_function.push_back(0); // Set the heuristic function to be 0 for every vertex in the graph
	}

	ASTAR_Search(); // Running the ASTAR algorithm with heuristic = 0 equals to running the UCS algorithm
}



// ASTAR_Search() : 

// Purpose :
// Run the ASTAR algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::ASTAR_Search()
{
	ASTAR_Search_Aux(false); // Threshold flag is false here because we are running ASTAR and not IDASTAR
}



// IDASTAR_Search() : 

// Purpose :
// Run the IDASTAR algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::IDASTAR_Search()
{
	threshold = FLT_MIN;
	algorithm_run_status = false;

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	std::chrono::high_resolution_clock::time_point end;

	while (1)
	{
		ASTAR_Search_Aux(true); // Running the ASTAR algorithm while the threshold flag is true updates the threshold

		if (algorithm_run_status == true) break; // Break out of the infinite loop if we find a solution

		end = std::chrono::high_resolution_clock::now();

		execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + input_time;

		execution_time /= 1000; // convert into seconds

		if (execution_time > time_limit) return;

		number_of_expanded_nodes = 0; // Reset expanded vertices count
		heuristic_sum = 0; // Reset heuristic function sum
	}

	end = std::chrono::high_resolution_clock::now();

	execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() + input_time;

	execution_time /= 1000; // convert into seconds

	if (execution_time > time_limit) algorithm_run_status = false;
}



// BIASTAR_Search() : 

// Purpose :
// Run the BIASTAR algorithm on the current active graph

// Parameters : None

// Return Value : None

void Algorithms::BIASTAR_Search()
{
	min_search_tree_depth_forwards = INT_MAX;
	max_search_tree_depth_forwards = INT_MIN;

	min_search_tree_depth_backwards = INT_MAX;
	max_search_tree_depth_backwards = INT_MIN;

	// Loop variables

	unsigned int i, j, q;
	int k;

	// Other variables

	int mutual_vertex; // Collision point between the forwards run and the backwards run
	int vertex;
	int search_tree_vertices_depth_sum_forwards = 0; 
	int search_tree_vertices_count_forwards = 1;
	int search_tree_vertices_depth_sum_backwards = 0;
	int search_tree_vertices_count_backwards = 1;
	bool identical; // A flag which checks if the current exapnded vertex in the forwards run is identical to the
	                // current exapnded vertex in the backwards run 
	std::vector<int> result_path_values; // Minimum cost path values stored in a vector

	// forwards A* variables

	std::vector<int> result_path_values_forwards; // Minimum cost path values of forwards stored in a vector 
	int min_vertex_index_forwards; // Index of vertex with minimum f function value for forwards run
	float min_vertex_cost_forwards; // Least cost path from starting point to all vertices in forwards run
	float current_heuristic_value_forwards; // Current heuristic function value for a vertex in the forwards run
	int deletion_index_forwards; // Actual index of min_vertex_index_forwards in the priority queue for the forwards run
	int expanded_nodes_forwards_count = 0; // Number of expanded vertices in the forwards run  

	std::vector<int> visited_vertices_forwards; // Keep track on what vertices were visited in the forwards run
	std::vector<int> parent_vertices_forwards; // Keep track of parent in the forwards run
	std::vector<float> min_cost_to_vertices_forwards; // Least cost path from starting point to all vertices in the forwards run
	std::vector<int> min_index_queue_forwards; // Priority queue for vertices with minimum f values in the forwards run
	std::vector<int> in_queue_forwards; // Keep track on what vertices are in the indexes queue in the forwards run
	std::vector<int> depth_vertices_forwards; // Depth of vertices in search tree in the forwards run
	std::vector<int> neighbors_forwards; // Store the neighbors of the current vertex in this vector in the forwards run
	std::vector<int> candidates_forwards; // Current graph vertices in the priority queue with minimum f value in the forwards run
	std::vector<int> closed_forwards; // Closed vertices list for forwards run 

	// Backwards A* variables

	std::vector<int> result_path_values_backwards; // Minimum cost path values of backwards stored in a vector 
	int min_vertex_index_backwards; // Index of vertex with minimum f function value for backwards run
	float min_vertex_cost_backwards; // Least cost path from starting point to all vertices in backwards run
	float current_heuristic_value_backwards; // Current heuristic function value for a vertex in the backwards run
	int deletion_index_backwards; // Actual index of min_vertex_index_backwards in the priority queue for the backwards run
	int expanded_nodes_backwords_count = 0; // Number of expanded vertices in the backwards run 

	std::vector<int> visited_vertices_backwards; // Keep track on what vertices were visited in the backwards run
	std::vector<int> parent_vertices_backwards; // Keep track of parent in the backwards run
	std::vector<float> min_cost_to_vertices_backwards; // Least cost path from starting point to all vertices in the backwards run
	std::vector<int> min_index_queue_backwards; // Priority queue for vertices with minimum f values in the backwards run
	std::vector<int> in_queue_backwards; // Keep track on what vertices are in the indexes queue in the backwards run
	std::vector<int> depth_vertices_backwards; // Depth of vertices in search tree in the backwards run
	std::vector<int> neighbors_backwards; // Store the neighbors of the current vertex in this vector in the backwards run
	std::vector<int> candidates_backwards; // Current graph vertices in the priority queue with minimum f value in the backwards run
	std::vector<int> closed_backwards; // Closed vertices list for backwards run 

	 // Initialization of vectors
	for (k = 0; k < G.GetVertexCount(); k++)
	{
		visited_vertices_forwards.push_back(0);
		in_queue_forwards.push_back(0);
		depth_vertices_forwards.push_back(0);
		parent_vertices_forwards.push_back(-1);
		min_cost_to_vertices_forwards.push_back(FLT_MAX);
		candidates_forwards.push_back(0);

		visited_vertices_backwards.push_back(0);
		in_queue_backwards.push_back(0);
		depth_vertices_backwards.push_back(0);
		parent_vertices_backwards.push_back(-1);
		min_cost_to_vertices_backwards.push_back(FLT_MAX);
		candidates_backwards.push_back(0);
	}

	// Initilize the start of the queue and paths costs vector in the forwards run
	min_index_queue_forwards.push_back(start);
	min_cost_to_vertices_forwards[start] = G.GetVertexCost(start);

	// Initilize the start of the queue and paths costs vector in the backwards run
	min_index_queue_backwards.push_back(end);
	min_cost_to_vertices_backwards[end] = G.GetVertexCost(end);

	while (min_index_queue_forwards.empty() == false && min_index_queue_backwards.empty() == false)
	{
		// Get the vertex index in the queue which has the least cost path from the start added with heuristic value ( f value )
		// in the forwards run

		min_vertex_index_forwards = min_index_queue_forwards[0];
		min_vertex_cost_forwards = min_cost_to_vertices_forwards[min_index_queue_forwards[0]] + heuristic_function_forwards[min_index_queue_forwards[0]];
		current_heuristic_value_forwards = heuristic_function_forwards[min_index_queue_forwards[0]];
		deletion_index_forwards = 0;

		for (j = 0; j < min_index_queue_forwards.size(); j++)
		{
			if ((min_cost_to_vertices_forwards[min_index_queue_forwards[j]] + heuristic_function_forwards[min_index_queue_forwards[j]]) < min_vertex_cost_forwards)
			{
				min_vertex_cost_forwards = (min_cost_to_vertices_forwards[min_index_queue_forwards[j]] + heuristic_function_forwards[min_index_queue_forwards[j]]);
				min_vertex_index_forwards = min_index_queue_forwards[j];
				current_heuristic_value_forwards = heuristic_function_forwards[min_index_queue_forwards[j]];
				deletion_index_forwards = j;
			}
		}

		// Get All the vertices in the queue that have a minimum value of f in the forwards run

		std::fill(candidates_forwards.begin(), candidates_forwards.end(), 0);

		for (i = 0; i < min_index_queue_forwards.size(); i++)
		{
			if (min_cost_to_vertices_forwards[min_index_queue_forwards[i]] + heuristic_function_forwards[min_index_queue_forwards[i]] == min_vertex_cost_forwards)
			{
				candidates_forwards[min_index_queue_forwards[i]] = 1;
			}
		}

		// Get the vertex index in the queue which has the least cost path from the start added with heuristic value ( f value )
        // in the backwards run

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

		// Get All the vertices in the queue that have a minimum value of f in the backwards run

		std::fill(candidates_backwards.begin(), candidates_backwards.end(), 0);

		for (i = 0; i < min_index_queue_backwards.size(); i++)
		{
			if (min_cost_to_vertices_backwards[min_index_queue_backwards[i]] + heuristic_function_backwards[min_index_queue_backwards[i]] == min_vertex_cost_backwards)
			{
				candidates_backwards[min_index_queue_backwards[i]] = 1;
			}
		}

		// Check if out of the forwards and backwards priority queues we have a common vertex with minimum f value
		// and we get it's heuristic value

		identical = false;

		for (k = 0; k < G.GetVertexCount(); k++)
		{
			if (candidates_forwards[k] == 1 && candidates_backwards[k] == 1)
			{
				min_vertex_index_forwards = k;
				min_vertex_index_backwards = k;
				current_heuristic_value_forwards = heuristic_function_forwards[k];
				current_heuristic_value_backwards = heuristic_function_backwards[k];
				identical = true;
				break;
			}
		}

		// If out of the forwards and backwards priority queues we have a common vertex with minimum f value then we get it's
		// deletion index in both the forwards queue and the backwards queue.

		if (identical == true) 
		{
			for (j = 0; j < min_index_queue_forwards.size(); j++)
			{
				if (min_vertex_index_forwards == min_index_queue_forwards[j])
				{
					deletion_index_forwards = j;
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

		// Update heuristic sum of expanded nodes in both the forwards and backwards run

		heuristic_sum_forwards += current_heuristic_value_forwards; 

		heuristic_sum_backwards += current_heuristic_value_backwards;

		// Pop minimum index from the forwards and backwards queues 

		min_index_queue_forwards.erase(min_index_queue_forwards.begin() + deletion_index_forwards); 

		min_index_queue_backwards.erase(min_index_queue_backwards.begin() + deletion_index_backwards);

		// Update colsed lists

		closed_forwards.push_back(min_vertex_index_forwards);

		closed_backwards.push_back(min_vertex_index_backwards);

		// Mark vertices as visited in both the forwards and backwards runs 

		visited_vertices_forwards[min_vertex_index_forwards] = 1;

		visited_vertices_backwards[min_vertex_index_backwards] = 1;

		// Mark vertices as deleted from the queues in both the forwards and backwards runs 

		in_queue_forwards[min_vertex_index_forwards] = 0;

		in_queue_backwards[min_vertex_index_backwards] = 0;

		// Update the number of expanded vertices in both the forwards and backwards runs 

		expanded_nodes_forwards_count++;

		expanded_nodes_backwords_count++;

		if (min_vertex_index_forwards == min_vertex_index_backwards) // Check if the forwards run and the backwards run collide
		{
			mutual_vertex = min_vertex_index_forwards;

			// Find the mutual vertices in the forwards and backwards min queues

			float min_cost_path = FLT_MAX;
			float current_min;

			std::vector<int> mutual_vertices_min_queues; 

			std::sort(min_index_queue_forwards.begin(), min_index_queue_forwards.end());
			std::sort(min_index_queue_backwards.begin(), min_index_queue_backwards.end());

			std::set_intersection(min_index_queue_forwards.begin(), min_index_queue_forwards.end(),
				min_index_queue_backwards.begin(), min_index_queue_backwards.end(),
				back_inserter(mutual_vertices_min_queues));

			// A case where there are more mutual vertices between the forwards and backwards queues
            // other than the collision vertex

			if(mutual_vertices_min_queues.size() > 0)
			{

				for (q = 0; q < mutual_vertices_min_queues.size(); q++)
				{
					current_min = min_cost_to_vertices_forwards[mutual_vertices_min_queues[q]] +
						          min_cost_to_vertices_backwards[mutual_vertices_min_queues[q]] -
						          G.GetVertexCost(mutual_vertices_min_queues[q]);

					if (current_min < min_cost_path)
					{
						min_cost_path = current_min;
						mutual_vertex = mutual_vertices_min_queues[q]; // Update current mutual vertex between the forwards and backwards queues
					}
				}
			}
			
			// Find the mutual vertices in the forwards and backwards closed lists

			std::vector<int> mutual_vertices_closed_lists;

			std::sort(closed_forwards.begin(), closed_forwards.end());
			std::sort(closed_backwards.begin(), closed_backwards.end());

			std::set_intersection(closed_forwards.begin(), closed_forwards.end(),
				closed_backwards.begin(), closed_backwards.end(),
				back_inserter(mutual_vertices_closed_lists));

			// A case where there are more mutual vertices between the forwards and backwards closed lists
			// other than the collision vertex

			if (mutual_vertices_closed_lists.size() > 0)
			{

				for (q = 0; q < mutual_vertices_closed_lists.size(); q++)
				{
					current_min = min_cost_to_vertices_forwards[mutual_vertices_closed_lists[q]] +
						min_cost_to_vertices_backwards[mutual_vertices_closed_lists[q]] -
						G.GetVertexCost(mutual_vertices_closed_lists[q]);

					if (current_min < min_cost_path)
					{
						min_cost_path = current_min;

						// Update current mutual vertex between the forwards and backwards closed lists
						mutual_vertex = mutual_vertices_closed_lists[q]; 
					}
				}
			}

			// Use parents of vertices in the forwards run to retrieve the optimal backwards path vertices in a vector

			vertex = parent_vertices_forwards[mutual_vertex];

			while (parent_vertices_forwards[vertex] != -1)
			{
				solution_length_forwards++;
				solution_length++;
				result_path_values_forwards.push_back(vertex);
				vertex = parent_vertices_forwards[vertex];
			}

			result_path_values_forwards.push_back(start); // Add the starting point of the grid to the forwards vertices vector
			solution_length_forwards++;
			solution_length++;

			std::reverse(result_path_values_forwards.begin(), result_path_values_forwards.end()); // Reverse the forwards run vector

			result_path_values_forwards.push_back(mutual_vertex); // Add the mutual forwards and backwards runs vertex to the vector 

			// Get the optimal forwards path and indicate where it ends

			result_path_forwards = GetResultPathString(result_path_values_forwards);

			result_path_forwards.append(" (Path begins at " + 
			std::to_string(start / G.GetRowColLength()) + "," + std::to_string(start % G.GetRowColLength()) + 
			" and ends at " + std::to_string(mutual_vertex / G.GetRowColLength()) + "," + std::to_string(mutual_vertex % G.GetRowColLength()) + ")");

			result_path_values_forwards.pop_back(); // Delete the last vertex in the forwards run optimal path

			vertex = mutual_vertex;

			// Use parents of vertices in the backwards run to retrieve the optimal backwards path vertices in a vector

			while (parent_vertices_backwards[vertex] != -1) 
			{
				solution_length_backwards++;
				solution_length++;
				result_path_values_backwards.push_back(vertex);
				vertex = parent_vertices_backwards[vertex];
			}

			result_path_values_backwards.push_back(end); // Add the ending point of the grid to the backwards vertices vector
			solution_length_backwards++;
			solution_length++;

		    // Get the optimal backwards path and indicate where it starts

			result_path_backwards = GetResultPathString(result_path_values_backwards);

			result_path_backwards.append(" (Path begins at " +
			std::to_string(mutual_vertex / G.GetRowColLength()) + "," + std::to_string(mutual_vertex % G.GetRowColLength()) +
			" and ends at " + std::to_string(end / G.GetRowColLength()) + "," + std::to_string(end % G.GetRowColLength()) + ")");

			// Get the optimal path by appending the optimal backwards vector with the forwards optimal vector

			for (q = 0; q < result_path_values_forwards.size(); q++)
			{
				result_path_values.push_back(result_path_values_forwards[q]);
			}

			for (q = 0; q < result_path_values_backwards.size(); q++)
			{
				result_path_values.push_back(result_path_values_backwards[q]);
			}

			solution_length--;

			// Calculate the average of search tree depths in both the forwards and backwards runs

			avg_search_tree_depth_forwards = float(search_tree_vertices_depth_sum_forwards) / float(search_tree_vertices_count_forwards);

			avg_search_tree_depth_backwards = float(search_tree_vertices_depth_sum_backwards) / float(search_tree_vertices_count_backwards);

			result_path = GetResultPathString(result_path_values); // Get the optimal path

			// Calculate the optimal forwards and backwards costs with also the overall optimal cost

			result_cost = min_cost_to_vertices_forwards[mutual_vertex] + min_cost_to_vertices_backwards[mutual_vertex]
				          - G.GetVertexCost(mutual_vertex) - G.GetVertexCost(start);

			result_cost_forwards = min_cost_to_vertices_forwards[mutual_vertex] - G.GetVertexCost(start);

			result_cost_backwards = min_cost_to_vertices_backwards[mutual_vertex] - G.GetVertexCost(mutual_vertex);

			// Calculate the number of expanded vertices in forwards and backwards runs with also the overall run

			number_of_expanded_nodes_forwards = expanded_nodes_forwards_count;

			number_of_expanded_nodes_backwards = expanded_nodes_backwords_count;

			number_of_expanded_nodes = expanded_nodes_forwards_count + expanded_nodes_backwords_count;

			algorithm_run_status = true; // Mark that we found a solution and exit the algorithm

			return;
		}

		neighbors_forwards = G.GetNeighbors(min_vertex_index_forwards); // Get neighbors of current vertex in the forwards run

		for (i = 0; i < neighbors_forwards.size(); i++)
		{
			if (visited_vertices_forwards[neighbors_forwards[i]] == 0) // Check if current neighbor is visited in the forwards run
			{
				if (in_queue_forwards[neighbors_forwards[i]] == 1) // Check if current neighbor is in the queue in the forwards run
				{
					if (min_cost_to_vertices_forwards[neighbors_forwards[i]] > (min_cost_to_vertices_forwards[min_vertex_index_forwards] + G.GetVertexCost(neighbors_forwards[i])))
					{
						// Update parent and update path cost to current neighbor if needed in the forwards run

						parent_vertices_forwards[neighbors_forwards[i]] = min_vertex_index_forwards;
						min_cost_to_vertices_forwards[neighbors_forwards[i]] = (min_cost_to_vertices_forwards[min_vertex_index_forwards] + G.GetVertexCost(neighbors_forwards[i]));
					}

					// Update the max and min of search tree depths in the forwards run

					if ((depth_vertices_forwards[min_vertex_index_forwards] + 1) > max_search_tree_depth_forwards) max_search_tree_depth_forwards = (depth_vertices_forwards[min_vertex_index_forwards] + 1);
					if ((depth_vertices_forwards[min_vertex_index_forwards] + 1) < min_search_tree_depth_forwards) min_search_tree_depth_forwards = (depth_vertices_forwards[min_vertex_index_forwards] + 1);

					// Update the sum and of search tree depths and the number of vertices in the search tree of the forwards run

					search_tree_vertices_depth_sum_forwards += (depth_vertices_forwards[min_vertex_index_forwards] + 1);
					search_tree_vertices_count_forwards++;
				}

				else
				{
					// Add to queue, update parent, depth and set path cost to current neighbor in the forwards run

					in_queue_forwards[neighbors_forwards[i]] = 1;
					min_index_queue_forwards.push_back(neighbors_forwards[i]);
					parent_vertices_forwards[neighbors_forwards[i]] = min_vertex_index_forwards;
					depth_vertices_forwards[neighbors_forwards[i]] = depth_vertices_forwards[min_vertex_index_forwards] + 1;
					min_cost_to_vertices_forwards[neighbors_forwards[i]] = (min_cost_to_vertices_forwards[min_vertex_index_forwards] + G.GetVertexCost(neighbors_forwards[i]));

					// Update the max and min of search tree depths in the forwards run

					if (depth_vertices_forwards[neighbors_forwards[i]] > max_search_tree_depth_forwards) max_search_tree_depth_forwards = depth_vertices_forwards[neighbors_forwards[i]];
					if (depth_vertices_forwards[neighbors_forwards[i]] < min_search_tree_depth_forwards) min_search_tree_depth_forwards = depth_vertices_forwards[neighbors_forwards[i]];

					// Update the sum and of search tree depths and the number of vertices in the search tree of the forwards run

					search_tree_vertices_depth_sum_forwards += depth_vertices_forwards[neighbors_forwards[i]];
					search_tree_vertices_count_forwards++;
				}
			}
		}

		neighbors_backwards = G.GetNeighbors(min_vertex_index_backwards); // Get neighbors of current vertex in the backwards run

		for (i = 0; i < neighbors_backwards.size(); i++)
		{
			if (visited_vertices_backwards[neighbors_backwards[i]] == 0) // Check if current neighbor is visited in the backwards run
			{
				if (in_queue_backwards[neighbors_backwards[i]] == 1) // Check if current neighbor is in the queue in the backwards run
				{
					if (min_cost_to_vertices_backwards[neighbors_backwards[i]] > (min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i])))
					{
						// Update parent and update path cost to current neighbor if needed in the backwards run

						parent_vertices_backwards[neighbors_backwards[i]] = min_vertex_index_backwards;
						min_cost_to_vertices_backwards[neighbors_backwards[i]] = min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i]);
					}

					// Update the max and min of search tree depths in the backwards run

					if ((depth_vertices_backwards[min_vertex_index_backwards] + 1) > max_search_tree_depth_backwards) max_search_tree_depth_backwards = (depth_vertices_backwards[min_vertex_index_backwards] + 1);
					if ((depth_vertices_backwards[min_vertex_index_backwards] + 1) < min_search_tree_depth_backwards) min_search_tree_depth_backwards = (depth_vertices_backwards[min_vertex_index_backwards] + 1);

					// Update the sum and of search tree depths and the number of vertices in the search tree of the backwards run

					search_tree_vertices_depth_sum_backwards += (depth_vertices_backwards[min_vertex_index_backwards] + 1);
					search_tree_vertices_count_backwards++;
				}

				else
				{
					// Add to queue, update parent, depth and set path cost to current neighbor in the backwards run

					in_queue_backwards[neighbors_backwards[i]] = 1;
					min_index_queue_backwards.push_back(neighbors_backwards[i]);
					parent_vertices_backwards[neighbors_backwards[i]] = min_vertex_index_backwards;
					depth_vertices_backwards[neighbors_backwards[i]] = depth_vertices_backwards[min_vertex_index_backwards] + 1;
					min_cost_to_vertices_backwards[neighbors_backwards[i]] = min_cost_to_vertices_backwards[min_vertex_index_backwards] + G.GetVertexCost(neighbors_backwards[i]);

					// Update the max and min of search tree depths in the backwards run

					if (depth_vertices_backwards[neighbors_backwards[i]] > max_search_tree_depth_backwards) max_search_tree_depth_backwards = depth_vertices_backwards[neighbors_backwards[i]];
					if (depth_vertices_backwards[neighbors_backwards[i]] < min_search_tree_depth_backwards) min_search_tree_depth_backwards = depth_vertices_backwards[neighbors_backwards[i]];

					// Update the sum and of search tree depths and the number of vertices in the search tree of the backwards run

					search_tree_vertices_depth_sum_backwards += depth_vertices_backwards[neighbors_backwards[i]];
					search_tree_vertices_count_backwards++;
				}
			}
		}
	}

	algorithm_run_status = false; // Failed to find a solution
}


