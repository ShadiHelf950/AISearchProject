#include "pch.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include "Utils.h"

std::pair<std::string,Graph> Utils::GetParametersAndGraph(const std::string& filePath)
{
	std::string algorithm_name;

	int n;

	int start;
	int end;

	std::string x;
	std::string y;

	std::string final_row_value;
	std::string line;
	std::string temp_line;
	std::string token;
	std::string delimeter = ", ";
	size_t pos = 0;
	int line_count = 1;
	int count = 0;
	int row, col;

	std::string object_name = Utils::GetFileName(filePath);

	std::ifstream object(filePath.c_str());

	while (std::getline(object, line))
	{
		if (line_count == 1)
		{
			algorithm_name = line;
		}

		else if (line_count == 2)
		{
			n = std::atoi(line.c_str());
			break;
		}

		line_count++;
	}

	Graph G = Graph(n);

	line_count++;

	while (std::getline(object, line))
	{
		if (line_count == 3)
		{
			pos = line.std::string::find(",");

			x = line.std::string::substr(0, pos);
			y = line.std::string::substr(pos+1, line.length()-pos-1);

			start = std::atoi(x.c_str()) * n + std::atoi(y.c_str());
		}

		else if (line_count == 4)
		{
			pos = line.std::string::find(",");

			x = line.std::string::substr(0, pos);
			y = line.std::string::substr(pos + 1, line.length() - pos - 1);

			end = std::atoi(x.c_str()) * n + std::atoi(y.c_str());
		}

		else if (line_count >= 5)
		{
			temp_line = line.substr(1, line.length()-1);

			while ((pos = temp_line.find(delimeter)) != std::string::npos)
			{
				token = temp_line.substr(0, pos);

				temp_line.erase(0, pos + delimeter.length());

				G.AddVertex(count, std::atoi(token.c_str()));

				count++;
			}

			final_row_value = temp_line;
			G.AddVertex(count, std::atoi(final_row_value.c_str()));
			count++;
		}

		line_count++;
	}

	for (int vertex_index = 0; vertex_index < G.GetVertexCount(); vertex_index++)
	{
		row = vertex_index / n;
		col = vertex_index % n;

		if (row == 0 && col == 0)
		{
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
		}

		else if (row == 0 && col == n - 1)
		{
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
		}

		else if (row == n - 1 && col == 0)
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
		}

		else if (row == n - 1 && col == n - 1)
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
		}

		else if (row == 0 && (0 < col && col < n - 1))
		{
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
			if(G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
		}

		else if (row == n - 1 && (0 < col && col < n - 1))
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
			if(G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
		}

		else if ((0 < row && row < n - 1) && col == 0)
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
			if(G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
		}

		else if ((0 < row && row < n - 1) && col == n - 1)
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
			if(G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
		}

		else if ((0 < row && row < n - 1) && (0 < col && col < n - 1))
		{
			if(G.GetVertexCost(vertex_index - n) != -1) G.AddEdge(vertex_index, UP);
			if(G.GetVertexCost(vertex_index + n) != -1) G.AddEdge(vertex_index, DOWN);
			if(G.GetVertexCost(vertex_index + 1) != -1) G.AddEdge(vertex_index, RIGHT);
			if(G.GetVertexCost(vertex_index - 1) != -1) G.AddEdge(vertex_index, LEFT);
			if(G.GetVertexCost(vertex_index - n + 1) != -1) G.AddEdge(vertex_index, UPPER_RIGHT);
			if(G.GetVertexCost(vertex_index + n + 1) != -1) G.AddEdge(vertex_index, BOTTOM_RIGHT);
			if(G.GetVertexCost(vertex_index - n - 1) != -1) G.AddEdge(vertex_index, UPPER_LEFT);
			if(G.GetVertexCost(vertex_index + n - 1) != -1) G.AddEdge(vertex_index, BOTTOM_LEFT);
		}
	}

	return std::make_pair(algorithm_name + " " + std::to_string(start) + " " + std::to_string(end), G);
}

std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}
