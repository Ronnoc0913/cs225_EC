#pragma once

#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> createAdjacencyMatrix(const string& filename, int numNodes);

vector<vector<double>> createTransitionMatrix(const vector<vector<int>>& adjacencyMatrix);
