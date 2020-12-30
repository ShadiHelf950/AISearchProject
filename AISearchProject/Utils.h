#pragma once
#include <string>
#include "Graph.h"

class Utils
{
public:
	std::pair<std::string, Graph> GetParametersAndGraph(const std::string& filePath);
};