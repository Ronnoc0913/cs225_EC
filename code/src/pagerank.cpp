#include "pagerank.h"

#include <iostream>
#include <stdexcept>

vector<vector<int>> createAdjacencyMatrix(const string &filename, int numNodes)
{
    ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("File unable to open");
    }

    int from, to;
    vector<vector<int>> adjacencyMatrix(numNodes, vector<int>(numNodes, 0));

    while (file >> from >> to) {
        std::cout << "from: " << from << ", to: " << to << std::endl;
        adjacencyMatrix[from-1][to-1] = 1;
    }

    file.close();

    return adjacencyMatrix;
}

vector<vector<double>> createTransitionMatrix(const vector<vector<int>>& adjacencyMatrix) {
    int numNodes = adjacencyMatrix.size();
    vector<vector<double>> transitionMatrix(numNodes, vector<double>(numNodes, 0.0));

    for (int i = 0; i < numNodes; ++i) {
        double sum = 0.0;
        for (int j = 0; j < numNodes; j++) {
            sum += adjacencyMatrix[i][j];
        }

        if (sum > 0.0) {
            for (int j = 0; j < numNodes; j++) {
                transitionMatrix[i][j] = adjacencyMatrix[i][j] / sum;
            }
        }
    }

    return transitionMatrix;
}
