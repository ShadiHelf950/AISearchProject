#include "pch.h"
#include "Graph.h"

/*************************************************** Class Functions *******************************************************/


// Graph() :

// Purpose :
// Default constructor for the Graph class

// Parameters : None

// Return Value : None

Graph::Graph()
{
}



// Graph(int s) :

// Purpose :
// Constructor for the Graph class which takes an integer s and initializes a graph with no edges and s * s  vertices

// Parameters :
// 1. s : The size of row or column of the search grid

// Return Value : None

Graph::Graph(int s)
{
	size = s * s;

	row_col_length = s;

	std::vector<int> neighbors = { -1,-1,-1,-1,-1,-1,-1,-1 }; // Each vertex is limited to 8 neighbors

	for (int i = 0; i < size; i++)
	{
		vertices_costs.push_back(-1);
		edges.push_back(neighbors);
	}
}



// GetVertexCost(int index) :

// Purpose :
// Get the cost of a vertex given the vertex's index

// Parameters :
// 1. index : Index of graph vertex

// Return Value : Cost of a vertex in the graph

float Graph::GetVertexCost(int index) const
{
	return vertices_costs[index];
}



// GetVertexCount() :

// Purpose :
// Get function for the size field ( Get the number of vertices in the graph )

// Parameters : None

// Return Value : The number of vertices in the graph

int Graph::GetVertexCount() const
{
	return size;
}



// IsValidEdge(int index, int neighbor_index) :

// Purpose :
// Given an index of a graph vertex and a neighbor type we return true if there is a neighbor link between the two parameters

// Parameters :
// 1. index : Index of graph vertex
// 2. neighbor_index : Neighbor type

// Return Value : True if there is a link between the two given parameters and false otherwise

bool Graph::IsValidEdge(int index, int neighbor_index) const
{
	return (edges[index][neighbor_index] == 1);
}



// GetNeighbor(int index, int neighbor_index) :

// Purpose :
// Given an index of a graph vertex and a neighbor type we return the actual neighbor index
// if there is a neighbor link between the two given parameters

// Parameters :
// 1. index : Index of graph vertex
// 2. neighbor_index : Neighbor type

// Return Value : Actual neighbor index if there is a neighbor link between the two given parameters and -1 otherwise

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



// GetNeighborType(int index, int neighbor) :

// Purpose :
// Given an index of a graph vertex and an index of an actual neighbor we return the type of neighbor that the second index is
// to the first index if there is a neighbor link between the two given indeces

// Parameters :
// 1. index : Index of graph vertex
// 2. neighbor : Index of an actual neighbor vertex

// Return Value : Neighbor type if there is a neighbor link between the two given indeces and -1 otherwise

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



// GetRowColLength() :

// Purpose :
// Get function for the row_col_length field ( Get length of a row or column in the grid )

// Parameters : None

// Return Value : The length of a row or column in the grid

int Graph::GetRowColLength() const
{
	return row_col_length;
}



// GetNeighbor(int index) :

// Purpose :
// Given an index of a graph vertex we return all the actual neighbor indeces that the given vertex has

// Parameters :
// 1. index : Index of graph vertex

// Return Value : All the actual neighbor indeces that the given vertex has

std::vector<int> Graph::GetNeighbors(int index) const
{
	std::vector<int> neighbors; // output vector

	// Check if there is a neighbor link between the given vertex index and all the neighbor types
	// and add to the output vector the suitable actual neighbor if there is indeed a link

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



// AddVertex(int index, float vertex_cost) :

// Purpose :
// Assign a real number as a cost of a vertex given the index of the vertex 

// Parameters :
// 1. index : Index of graph vertex
// 2. vertex_cost : A real number

// Return Value : None

void Graph::AddVertex(int index, float vertex_cost)
{
	vertices_costs[index] = vertex_cost;
}



// AddEdge(int index, int neighbor_index) :

// Purpose :
// Assign a neighbor link between a given graph vertex index and a neighbor type

// Parameters :
// 1. index : Index of graph vertex
// 2. neighbor_index : Neighbor type

// Return Value : None

void Graph::AddEdge(int index, int neighbor_index)
{
	edges[index][neighbor_index] = 1;
}


