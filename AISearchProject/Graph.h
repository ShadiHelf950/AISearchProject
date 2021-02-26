#pragma once
#include "vector"
#include <string>

// Neighbor Types:

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define UPPER_RIGHT 4
#define UPPER_LEFT 5
#define BOTTOM_RIGHT 6
#define BOTTOM_LEFT 7


#define MAX_NEIGHBORS 8 // Maximum number of neighbors ( cell has valid cells ( not -1 ) in all 8 directions )

// Class Functionality : A class to represent the graph that we get from the input grid ( we store the vertices' prices and edges )

class Graph
{
	/****************************************************** Functions *************************************************************/

   // NOTE : Functions explanations are in the cpp file.

public:

	Graph();

	Graph(int s);

	float GetVertexCost(int index) const;

	int GetVertexCount() const;

	bool IsValidEdge(int index, int neighbor_index) const;

	int GetNeighbor(int index, int neighbor_index) const;

	int GetNeighborType(int index, int neighbor) const;

	int GetRowColLength() const;

	std::vector<int> GetNeighbors(int index) const;

	void AddVertex(int index, float vertex_cost);

	void AddEdge(int index, int neighbor_index);

private:

	int size; // Number of vertices in the graph

	int row_col_length; // Length of a column or a row in the grid

	std::vector<float> vertices_costs; // Cost of vertices

	std::vector<std::vector<int>> edges; // Edges list of the graph
};