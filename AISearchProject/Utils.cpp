#include "pch.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include "Utils.h"

/*************************************************** Class Functions *******************************************************/

// CheckIfFloat(std::string str) : 

// Purpose :
// Check if given input string is a float number or not

// Parameters :
// 1. str : An input string

// Return Value : True if the input string is a float number and false otherwise

bool Utils::CheckIfFloat(std::string str)
{
	std::istringstream stream(str);
	float number;
	stream >> std::noskipws >> number; // noskipws considers leading whitespace invalid
	return stream.eof() && !stream.fail();
}



// GetParametersAndGraph(std::ifstream& object) : 

// Purpose :
// Parsing the info in the input file of the grid and getting the graph representation of the grid alongside
// the name of the search algorithm to run alongside the start and goal points

// Parameters :
// 1. object : The input file

// Return Value : A pair which consists of the name of the algorithm to run, the algorithm
// starting and ending points and the graph which we get from the grid 

std::pair<std::string,Graph> Utils::GetParametersAndGraph(std::ifstream& object)
{
	std::string algorithm_name; // Output algorithm name

	int n; // Length of row or column in the grid

	int start; // Start of search
	int end;   // Goal of search

	std::string x;
	std::string y;

	std::string final_row_value;
	std::string line;
	std::string temp_line;
	std::string token;
	std::string delimeter = ",";
	size_t pos = 0;
	int line_count = 1;
	int count = 0;
	int row, col;

	while (std::getline(object, line)) // Loop over the lines of the input file 
	{
		if (line_count == 1) // First line contains the name of the algorithm
		{
			algorithm_name = line;
		}

		else if (line_count == 2) // Second line contains the size of the rows and columns of the grid 
		{
			n = std::atoi(line.c_str());
			break;
		}

		line_count++;
	}

	Graph G = Graph(n); // The output graph with n x n dimensions

	line_count++;

	while (std::getline(object, line))
	{
		if (line_count == 3) // Get starting point coordinates
		{
			pos = line.std::string::find(",");

			x = line.std::string::substr(0, pos);
			y = line.std::string::substr(pos+1, line.length()-pos-1);

			start = std::atoi(x.c_str()) * n + std::atoi(y.c_str());
		}

		else if (line_count == 4) // Get goal point coordinates
		{
			pos = line.std::string::find(",");

			x = line.std::string::substr(0, pos);
			y = line.std::string::substr(pos + 1, line.length() - pos - 1);

			end = std::atoi(x.c_str()) * n + std::atoi(y.c_str());
		}

		else if (line_count >= 5) // Create the graph's vertices and add their prices 
		{
			temp_line = line;

			while ((pos = temp_line.find(delimeter)) != std::string::npos)
			{
				token = temp_line.substr(0, pos);

				temp_line.erase(0, pos + delimeter.length());

				G.AddVertex(count, std::stof(token)); // Add vertex price to the graph

				count++;
			}

			final_row_value = temp_line;
			G.AddVertex(count, std::stof(final_row_value)); // Add last vertex price in a row
			count++;
		}

		line_count++;
	}

	for (int vertex_index = 0; vertex_index < G.GetVertexCount(); vertex_index++) // Create the edges of the graph
	{
		if (G.GetVertexCost(vertex_index) != -1) // Check if vertex is not blocked
		{
			row = vertex_index / n;
			col = vertex_index % n;

			// In the following if conditions we check where is the vertex located and we check if it has valid neighbors

			if (row == 0 && col == 0) // Upper left most element
			{
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
			}

			else if (row == 0 && col == n - 1) // Upper right most element 
			{
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
			}

			else if (row == n - 1 && col == 0) // Lower left most element
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
			}

			else if (row == n - 1 && col == n - 1) // Lower right most element
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
			}

			else if (row == 0 && (0 < col && col < n - 1)) // First row
			{
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
				if (G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
			}

			else if (row == n - 1 && (0 < col && col < n - 1)) // Last row
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
				if (G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
			}

			else if ((0 < row && row < n - 1) && col == 0) // First column
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
				if (G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
			}

			else if ((0 < row && row < n - 1) && col == n - 1) // Last column
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
				if (G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
			}

			else if ((0 < row && row < n - 1) && (0 < col && col < n - 1)) // Vertex deeply inside the grid
			{
				if (G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
				if (G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
				if (G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
				if (G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
				if (G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
				if (G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
				if (G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
				if (G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
			}
		}
	}

	return std::make_pair(algorithm_name + " " + std::to_string(start) + " " + std::to_string(end), G);
}

