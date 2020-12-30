#include "pch.h"
#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(int s)
{
	size = s * s;

	row_col_length = s;

	std::vector<int> neighbors = { -1,-1,-1,-1,-1,-1,-1,-1 };

	for (int i = 0; i < size; i++)
	{
		vertices_costs.push_back(-1);
		edges.push_back(neighbors);
	}
}

float Graph::GetVertexCost(int index) const
{
	return vertices_costs[index];
}

int Graph::GetVertexCount() const
{
	return size;
}

bool Graph::IsValidEdge(int index, int neighbor_index) const
{
	return (edges[index][neighbor_index] == 1);
}

int Graph::GetNeighbor(int index, int neighbor_index) const
{
	if (IsValidEdge(index, neighbor_index) == 1)
	{
		if (neighbor_index == UP)
		{
			return index - row_col_length;
		}

		else if (neighbor_index == DOWN)
		{
			return index + row_col_length;
		}

		else if (neighbor_index == RIGHT)
		{
			return index + 1;
		}

		else if (neighbor_index == LEFT)
		{
			return index - 1;
		}

		else if (neighbor_index == UPPER_RIGHT)
		{
			return index - row_col_length + 1;
		}

		else if (neighbor_index == UPPER_LEFT)
		{
			return index - row_col_length - 1;
		}

		else if (neighbor_index == BOTTOM_RIGHT)
		{
			return index + row_col_length + 1;
		}

		else if (neighbor_index == BOTTOM_LEFT)
		{
			return index + row_col_length - 1;
		}

	}

	return -1;
}

int Graph::GetNeighborType(int index, int neighbor) const
{
	for (int i = 0; i < MAX_NEIGHBORS; i++)
	{
		if (GetNeighbor(index, i) == neighbor)
		{
			return i;
		}
	}

	return -1;
}

int Graph::GetRowColLength() const
{
	return row_col_length;
}

std::vector<int> Graph::GetNeighbors(int index) const
{
	std::vector<int> neighbors;

	if(IsValidEdge(index, UP) == 1) neighbors.push_back(index - row_col_length);

    if(IsValidEdge(index, DOWN) == 1) neighbors.push_back(index + row_col_length);

	if(IsValidEdge(index, RIGHT) == 1) neighbors.push_back(index + 1);

	if(IsValidEdge(index, LEFT) == 1) neighbors.push_back(index - 1);

	if(IsValidEdge(index, UPPER_RIGHT) == 1) neighbors.push_back(index - row_col_length + 1);

	if(IsValidEdge(index, UPPER_LEFT) == 1) neighbors.push_back(index - row_col_length - 1);

    if(IsValidEdge(index, BOTTOM_RIGHT) == 1) neighbors.push_back(index + row_col_length + 1);

	if(IsValidEdge(index, BOTTOM_LEFT) == 1) neighbors.push_back(index + row_col_length - 1);
		 
	return neighbors;
}

void Graph::AddVertex(int index, float vertex_cost)
{
	vertices_costs[index] = vertex_cost;
}

void Graph::AddEdge(int index, int neighbor_index)
{
	edges[index][neighbor_index] = 1;
}


