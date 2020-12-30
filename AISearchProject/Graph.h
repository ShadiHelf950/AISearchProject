#pragma once
#include "vector"
#include <string>
#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define UPPER_RIGHT 4
#define UPPER_LEFT 5
#define BOTTOM_RIGHT 6
#define BOTTOM_LEFT 7
#define MAX_NEIGHBORS 8

class Graph
{
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

	int size;
	int row_col_length;
	std::vector<float> vertices_costs;
	std::vector<std::vector<int>> edges;
};