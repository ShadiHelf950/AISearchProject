#include "pch.h"
#include "Graph.h"

Graph::Graph(std::string n, int s) : size(s), vertices(nullptr), edges(nullptr)
{
	vertices = NULL;
	edges = NULL;

	vertices = new int[size];

	for (int i = 0; i < size; i++)
	{
		vertices[i] = -1;
	}

	edges = new int*[size];

	for (int i = 0; i < 5; i++)
	{
		edges[i] = new int[size];

		for (int j = 0; j < size; j++)
		{
			edges[i][j] = -1;
		}
	}
}

Graph::~Graph()
{
	delete[] vertices;

	for (int i = 0; i < size; i++) delete[] edges[i];
	
	delete[] edges;
}

int Graph::GetVertex(int index) const
{
	return vertices[index];
}

bool Graph::IsValidEdge(int i, int j) const
{
	return (edges[i][j] == 1);
}

void Graph::AddVertex(int index, int vertex)
{
	vertices[index] = vertex;
}

void Graph::AddEdge(int i, int j)
{
	edges[i][j] = 1;
}
