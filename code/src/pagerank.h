#pragma once

#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

vector<vector<int>> createAdjacencyMatrix(const string& filename, int numNodes);

vector<vector<double>> createTransitionMatrix(const vector<vector<int>>& adjacencyMatrix);

vector<double> calculatePageRank(const vector<vector<double>>& transitionMatrix, int numIterations, double dampFactor = 0.85);
