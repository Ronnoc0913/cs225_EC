#include <catch2/catch_test_macros.hpp>
#include <pagerank.h>

#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>

// Complications: 
// Comparing doubles with varying levels of precision
// (Our pagerank algorithm is basically correct to a certain level of precision,
// after which it differs from the NetworkX results)
// ^ because of this, comparing by ranks is more accurate?
// Comparing very large datasets: compromise by just comparing first five

// Helper Functions
template <typename T>
bool isEqual(std::vector<T> expected, std::vector<T> output) {
    if (expected.size() != output.size()) {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++) {
        if (expected[i] != output[i]) {
            return false;
        }
    }

    if (expected == output) return true;

    return false;
}

std::vector<int> scoreToRank(std::vector<double> pagerank) {
    // accepts an vector<double> of pagerank scores and ranks them from largest to smallest
    // output is a vector<int> of node labels ranked from highest score to lowest

    std::map<double, int> pagerankMap;

    for (size_t i = 0; i < pagerank.size(); ++i) {
        pagerankMap.insert({pagerank[i], i+1});
    }

    std::vector<int> ranking;
    for (const auto& pair : pagerankMap) {
        ranking.push_back(pair.second);
    }
    std::reverse(ranking.begin(), ranking.end());

    return ranking;
}

// Test Cases

TEST_CASE("Correct Score: Small Dataset", "[small]")
{
    std::vector<double> expected;
    expected.push_back(0.163); // 0.16271695346751378
    expected.push_back(0.082); // 0.08172837651407977
    expected.push_back(0.363); // 0.36346825390511567
    expected.push_back(0.239); // 0.2391038064085376
    expected.push_back(0.025); // 0.025
    expected.push_back(0.128); // 0.1279826097047531

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small.txt", 6);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Small Dataset", "[small]")
{    
    std::vector<int> expected;
    expected.push_back(3);
    expected.push_back(4);
    expected.push_back(1);
    expected.push_back(6);
    expected.push_back(2);
    expected.push_back(5);

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small.txt", 6);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 1000, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);

    // for (size_t i = 0; i < actual.size(); i++) {
    //     std::cout << actual[i] << std::endl;
    // }

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Score: Small Dataset with Loop", "[small]")
{
   
    std::vector<double> expected;
    expected.push_back(0.0); // 0.1164948582054956
    expected.push_back(0.0); // 0.06354275239697872
    expected.push_back(0.0); // 0.24021230934791263
    expected.push_back(0.0); // 0.15695866282842416
    expected.push_back(0.0); // 0.021428571428571432
    expected.push_back(0.0); // 0.08948910375557087 
    expected.push_back(100.0); // 0.3118737420370464

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small-loop.txt", 7);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Small Dataset with Loop", "[small]")
{   
    std::vector<int> expected;
    expected.push_back(7);
    expected.push_back(3);
    expected.push_back(4);
    expected.push_back(1);
    expected.push_back(6);
    expected.push_back(2);
    expected.push_back(5);

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small-loop.txt", 7);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 1000, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);

    REQUIRE(isEqual(expected, actual));
}

/*
Expected values as found by NetworkX (python):

small.txt
{1: 0.16271695346751378,
2: 0.08172837651407977,
3: 0.36346825390511567,
4: 0.2391038064085376,
6: 0.1279826097047531,
5: 0.025}

small-loop.txt
{1: 0.1164948582054956,
2: 0.06354275239697872,
3: 0.24021230934791263,
4: 0.15695866282842416,
6: 0.08948910375557087,
5: 0.021428571428571432,
7: 0.3118737420370464}

*/

/* 
The big files are too big so I'll just test the top 5:
 
"Wiki-Vote.txt"
Correct Scores (First 5 Nodes):
(3, 0.00020539498232448021),
(4, 5.0487823458630175e-05),
(5, 5.0487823458630175e-05),
(6, 0.00031183250978437466),
(7, 5.0487823458630175e-05),

Correct Ranking (Top 5):
(25, 5.0487823458630175e-05),
(4, 5.0487823458630175e-05),
(5, 5.0487823458630175e-05),
(7, 5.0487823458630175e-05),
(9, 5.0487823458630175e-05),

"twitter_combined.txt"
Correct Scores (First 5 Nodes):
(12, 0.0003663345736484223),
(13, 0.00026880194196060385),
(14, 1.1139614450545228e-05),
(17, 6.930478439163134e-06),
(20, 0.0004232418764090157)

Correct Ranking (Top 5):
(54226675, 2.4656752770650927e-06),
(33870122, 2.474594918258814e-06),
(36729081, 2.474594918258814e-06),
(61428016, 2.474594918258814e-06),
(45123184, 2.474594918258814e-06),

"web-Stanford.txt"
Correct Scores (First 5 Nodes):
(1, 5.334886410003276e-07),
(2, 0.00015488633564989099),
(3, 9.61870322298689e-07),
(4, 5.334886410003276e-07),
(5, 1.0462729097290746e-06),

Correct Ranking (Top 5):
(1, 5.334886410003276e-07),
(4, 5.334886410003276e-07),
(8, 5.334886410003276e-07),
(24, 5.334886410003276e-07),
(26, 5.334886410003276e-07),

"web-BerkStan.txt"
Correct Scores (First 5 Nodes):
(1, 1.830613564418469e-05),
(2, 5.277322767121117e-06),
(3, 5.459406614138215e-07),
(4, 4.987598172226909e-07),
(5, 4.766957674528825e-06),

Correct Ranking (Top 5):
(25, 2.2381527449245456e-07),
(26, 2.2381527449245456e-07),
(27, 2.2381527449245456e-07),
(28, 2.2381527449245456e-07),
(794, 2.2381527449245456e-07),

"web-Google.txt"
Correct Scores (First 5 Nodes):
(6, 2.8281106711282054e-07),
(12, 2.8281106711282054e-07),
(18, 2.8281106711282054e-07),
(24, 2.8281106711282054e-07),
(25, 2.8281106711282054e-07),

Correct Ranking (Top 5):
(1, 1.830613564418469e-05),
(2, 5.277322767121117e-06),
(3, 5.459406614138215e-07),
(4, 4.987598172226909e-07),
(5, 4.766957674528825e-06),

*/
