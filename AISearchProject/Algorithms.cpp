#include "pch.h"
#include "Algorithms.h"
#include <sstream>
#include <list>
#include <iostream>

Algorithms::Algorithms() : G()
{
	search_depth = 0;
	result_cost = 0;
	number_of_expanded_nodes = 0;
	result_path = "";
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

void Algorithms::SetActiveAlgorithm(std::string algorithm)
{
	active_algorithm = algorithm;
}

void Algorithms::GetResultPathString(std::vector<int> result_path_values)
{
	int neighbor_type, previous_vertex, current_vertex;

	for (unsigned i = 0; i < result_path_values.size() - 1; i++)
	{
		previous_vertex = result_path_values[i];
		current_vertex  = result_path_values[i + 1];

		neighbor_type = G.GetNeighborType(previous_vertex, current_vertex);

		if (neighbor_type == UP)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "U";
			}

			else
			{
				result_path += "U-";
			}
		}

		else if (neighbor_type == DOWN)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "D";
			}

			else
			{
				result_path += "D-";
			}
		}

		else if (neighbor_type == RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "R";
			}

			else
			{
				result_path += "R-";
			}
		}

		else if (neighbor_type == LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "L";
			}

			else
			{
				result_path += "L-";
			}
		}

		else if (neighbor_type == UPPER_RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "RU";
			}

			else
			{
				result_path += "RU-";
			}
		}

		else if (neighbor_type == UPPER_LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "LU";
			}

			else
			{
				result_path += "LU-";
			}
		}

		else if (neighbor_type == BOTTOM_RIGHT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "RD";
			}

			else
			{
				result_path += "RD-";
			}
		}

		else if (neighbor_type == BOTTOM_LEFT)
		{
			if (i == result_path_values.size() - 2)
			{
				result_path += "LD";
			}

			else
			{
				result_path += "LD-";
			}
		}
	}
}

std::string Algorithms::GetResultPath() const
{
	return result_path;
}

int Algorithms::GetResultCost() const
{
	return result_cost;
}

int Algorithms::GetResultExpandedVertices() const
{
	return number_of_expanded_nodes;
}

void Algorithms::RunActiveAlgorithm()
{
	if (start == end)
	{
		algorithm_run_status = true;
		number_of_expanded_nodes = 1;
		result_cost = G.GetVertexCost(start);
		return;
	}

	if(active_algorithm._Equal("IDS")) IDS_Search();

	else if(active_algorithm._Equal("UCS")) UCS_Search();

	else if(active_algorithm._Equal("ASTAR")) ASTAR_Search();

	else if(active_algorithm._Equal("IDASTAR")) IDASTAR_Search();

	else if(active_algorithm._Equal("BIASTAR")) BIASTAR_Search();
}

void Algorithms::DLS_Search(int depth)
{
	unsigned int i;
	int current_vertex;
	int vertex;
	std::vector<int> result_path_values;
	std::vector<int> visited_vertices;
	std::vector<int> deleted_vertices;
	std::vector<int> depth_vertices;
	std::vector<int> parent_vertices;
	std::list<int> queue;
	std::vector<int> neighbors;

	for (int i = 0; i < G.GetVertexCount(); i++)
	{
		visited_vertices.push_back(0);
        deleted_vertices.push_back(0);
        depth_vertices.push_back(0);
		parent_vertices.push_back(-1);
	}

	visited_vertices[start] = 1;
	queue.push_back(start);

	while (queue.empty() == false)
	{
		current_vertex = queue.front();
		queue.pop_front();
		deleted_vertices[current_vertex] = 1;

		if (depth_vertices[current_vertex] == depth) break;

		neighbors = G.GetNeighbors(current_vertex);

		number_of_expanded_nodes++;

		for (i = 0; i < neighbors.size() ; i++)
		{
			if (visited_vertices[neighbors[i]] == 0 && deleted_vertices[neighbors[i]] == 0)
			{
				visited_vertices[neighbors[i]] = 1;
				queue.push_back(neighbors[i]);
				depth_vertices[neighbors[i]] = depth_vertices[current_vertex] + 1;
				parent_vertices[neighbors[i]] = current_vertex;

				if (neighbors[i] == end)
				{
					vertex = end;

					while (parent_vertices[vertex] != -1)
					{
						result_path_values.push_back(vertex);
						result_cost += G.GetVertexCost(vertex);

						vertex = parent_vertices[vertex];
					}

					result_cost += G.GetVertexCost(start);

					result_path_values.push_back(start);

					std::reverse(result_path_values.begin(), result_path_values.end());

					GetResultPathString(result_path_values);
					algorithm_run_status = true;
					return;
				}
			}
		}
	}
    
	algorithm_run_status = false;
}

void Algorithms::IDS_Search()
{
	int depth = 1;
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

}

void Algorithms::ASTAR_Search()
{
}

void Algorithms::IDASTAR_Search()
{
}

void Algorithms::BIASTAR_Search()
{
}
