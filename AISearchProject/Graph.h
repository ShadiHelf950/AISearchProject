#pragma once
#include "vector"
#include <string>

class Graph
{
public:

	Graph(std::string n, int s);

	~Graph();

	int GetVertex(int index) const;
	bool IsValidEdge(int i, int j) const;

	void AddVertex(int index, int vertex);
	void AddEdge(int i, int j);

private:
	std::string name;
	int size;
	int* vertices;
	int** edges;
};