#include <catch2/catch_test_macros.hpp>
#include <pagerank.h>

#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>

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
    expected.push_back(0.1627); // 0.16271695346751378
    expected.push_back(0.0817); // 0.08172837651407977
    expected.push_back(0.3634); // 0.36346825390511567
    expected.push_back(0.2391); // 0.2391038064085376
    expected.push_back(0.025); // 0.025
    expected.push_back(0.1279); // 0.1279826097047531

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small.txt", 6);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

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
    expected.push_back(0.1164); // 0.1164948582054956
    expected.push_back(0.0635); // 0.06354275239697872
    expected.push_back(0.2402); // 0.24021230934791263
    expected.push_back(0.1569); // 0.15695866282842416
    expected.push_back(0.0214); // 0.021428571428571432
    expected.push_back(0.0894); // 0.08948910375557087 
    expected.push_back(0.3118); // 0.3118737420370464

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/small-loop.txt", 7);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

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


TEST_CASE("Correct Score: Med BerkStan Dataset", "[med-berkstan]")
{
   
    std::vector<double> expected;
    expected.push_back(0.0083);
    expected.push_back(0.0181);
    expected.push_back(0.0045);
    expected.push_back(0.0035);
    expected.push_back(0.0088);
/*
(1, 0.008319119419334171),
 (2, 0.018160957963817635),
 (3, 0.004545450745540654),
 (4, 0.0035735404701778724),
 (5, 0.008848348429696845),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/med-berkstan.txt", 100);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Med BerkStan Dataset", "[med-berkstan]")
{   
    std::vector<int> expected;
    expected.push_back(34);
    expected.push_back(33);
    expected.push_back(30);
    expected.push_back(31);
    expected.push_back(7);

    /*
(34, 0.19436938217661967),
 (33, 0.1878260884067107),
 (30, 0.06085203288291541),
 (31, 0.057296794255172805),
 (7, 0.031127169475445724),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/med-berkstan.txt", 100);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 100, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}


TEST_CASE("Correct Score: Med Wiki Dataset", "[med-wiki]")
{
   
    std::vector<double> expected;
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0521);
    expected.push_back(0.0022);
    expected.push_back(0.0022);
/*
(3, 0.05210853378835487),
 (4, 0.0022640561687413195),
 (5, 0.0022640561687413195),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/med-wiki.txt", 100);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Med Wiki Dataset", "[med-wiki]")
{   
    std::vector<int> expected;
    expected.push_back(28);
    expected.push_back(54);
    expected.push_back(3);
    expected.push_back(56);
    expected.push_back(33);

    /*
(28, 0.10636516208461393),
 (54, 0.07201782509022862),
 (3, 0.05210853378835487),
 (56, 0.04353038495171783),
 (33, 0.04116625034823554),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/med-wiki.txt", 100);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 100, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}


TEST_CASE("Correct Score: Large BerkStan Dataset", "[large-berkstan]")
{
   
    std::vector<double> expected;
    expected.push_back(0.0008);
    expected.push_back(0.0018);
    expected.push_back(0.0004);
    expected.push_back(0.0003);
    expected.push_back(0.0008);
/*
(1, 0.00083240990404772),
 (2, 0.0018185177904752863),
 (3, 0.0004548093604545595),
 (4, 0.0003575331634675461),
 (5, 0.0008856873060140537),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/large-berkstan.txt", 1000);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Large BerkStan Dataset", "[large-berkstan]")
{   
    std::vector<int> expected;
    expected.push_back(861);
    expected.push_back(768);
    expected.push_back(40);
    expected.push_back(927);
    expected.push_back(372);

    /*
(861, 0.036802523198681984),
 (768, 0.03423100120520981),
 (40, 0.03127589443265558),
 (927, 0.028610857570783396),
 (372, 0.014206404510008304),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/large-berkstan.txt", 1000);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 100, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}


TEST_CASE("Correct Score: Large Wiki Dataset", "[large-wiki]")
{
   
    std::vector<double> expected;
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0052);
    expected.push_back(0.0022);
    expected.push_back(0.0022);
/*
(3, 0.05210853378835487),
 (4, 0.0022640561687413195),
 (5, 0.0022640561687413195),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/large-wiki.txt", 1000);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> actual = calculatePageRank(transitionMatrix, 1000, 0.85); 
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}

TEST_CASE("Correct Ranking: Large Wiki Dataset", "[large-wiki]")
{   
    std::vector<int> expected;
    expected.push_back(28);
    expected.push_back(271);
    expected.push_back(214);
    expected.push_back(86);
    expected.push_back(299);

    /*
(28, 0.01590998092104412),
 (271, 0.015343401912600347),
 (214, 0.010587168073526597),
 (86, 0.01057167898053414),
 (299, 0.010271916026706423),
 */

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix("../../data/large-wiki.txt", 1000);
    std::vector<std::vector<double>> transitionMatrix = createTransitionMatrix(adjacencyMatrix);
    std::vector<double> pagerank = calculatePageRank(transitionMatrix, 100, 0.85); 
    std::vector<int> actual = scoreToRank(pagerank);
    actual.resize(5);

    for (size_t i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << std::endl;
    }
    std::cout << std::endl;

    REQUIRE(isEqual(expected, actual));
}

