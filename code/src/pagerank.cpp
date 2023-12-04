#include "pagerank.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

vector<vector<int>> createAdjacencyMatrix(const string &filename, int numNodes)
{
    ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("File unable to open");
    }

    int from, to;
    vector<vector<int>> adjacencyMatrix(numNodes, vector<int>(numNodes, 0));

    while (file >> from >> to) {
        // std::cout << "from: " << from << ", to: " << to << std::endl;
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

/*Function to calculate the PageRank of nodes in a graph
  TransitionMatrix: transition probability matrix of graph
  numIterations: maximum number of iterations to run the algorithm.
  dampFactor: damping factor */
vector<double> calculatePageRank(const vector<vector<double>>& transitionMatrix, int numIterations, double dampFactor){
    int numNodes = transitionMatrix.size(); 
    vector<double> pageRank(numNodes, 1.0 / numNodes);
    vector<double> newPageRank(numNodes, 0.0);

    for(int iter = 0; iter < numIterations; ++iter){
        double danglingRank = 0.0;
        //calculate total rank contribution from dangling nodes
        for(int i = 0; i < numNodes; ++i){
            // sum of probablilities in current row 
            double rowSum = std::accumulate(transitionMatrix[i].begin(), transitionMatrix[i].end(), 0.0);
            // if sum is zero, there is a dangling node
            if(rowSum == 0){
                danglingRank += pageRank[i] / numNodes;
            }
        }
        //calculate new pagerank value for each node
        for(int i = 0; i < numNodes; ++i){
            //teleportation contribution
            newPageRank[i] = (1.0 - dampFactor)/ numNodes;
            //add the rank contributions from other nodes
            for(int j = 0; j < numNodes; ++j){
                newPageRank[i] += dampFactor * transitionMatrix[j][i] * pageRank [j];
            }
            // Add the contribution from dangling nodes.
            newPageRank[i] += danglingRank * dampFactor;
        }

        double diff = 0.0;
        for(int i = 0; i < numNodes; ++i){
            diff += std::abs(newPageRank[i] - pageRank[i]);

        }
        if(diff < 0.001){
            break;
        }
        pageRank = newPageRank;

    }
    return pageRank;
}