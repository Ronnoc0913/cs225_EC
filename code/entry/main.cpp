#include <iostream>
#include "pagerank.h"

int main()
{
    string filename = "../../data/small-loop.txt"; 
    int numNodes = 7;

    vector<vector<int>> adjacencyMatrix = createAdjacencyMatrix(filename, numNodes);
    vector<vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);

    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nTransition Probability Matrix:" << endl;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            cout << transitionMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}