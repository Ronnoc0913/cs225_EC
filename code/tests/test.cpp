#include <catch2/catch_test_macros.hpp>

// #include (header files)

#include <vector>
#include <sstream>

// Things to implement for the test cases:
// Something to process .txt files to directed graphs
// Something output the final scores
// Or a ranked list of sites (from largest score to smallest)

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

    return true;
}

TEST_CASE("Correct Score: Small Dataset", "[small]")
{
    // Process "../../data/small.txt"

    std::vector<double> expected;
    expected.push_back(16.0);
    expected.push_back(16.0/3.0);
    expected.push_back(40.0);
    expected.push_back(76.0/3.0);
    expected.push_back(0.0);
    expected.push_back(40.0/3.0);

    // Run PageRank algorithm which returns a vector<double> of scores as an output

    std::vector<double> out = pagerankScores(); // Example

    REQUIRE(isEqual(expected, out));
}

TEST_CASE("Correct Ranking: Small Dataset", "[small]")
{
    // Process "../../data/small.txt"
    
    std::vector<int> expected;
    expected.push_back(3);
    expected.push_back(4);
    expected.push_back(1);
    expected.push_back(6);
    expected.push_back(2);
    expected.push_back(5);

    // Run PageRank algorithm which returns a vector<int> of ranks as an output

    std::vector<int> out = pagerankRanks(); // Example

    REQUIRE(isEqual(expected, out));
}

TEST_CASE("Correct Score: Small Dataset with Loop", "[small]")
{
    // Process "../../data/small.txt"
    
    std::vector<double> expected;
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(0.0);
    expected.push_back(100.0);

    // Run PageRank algorithm which returns a vector<int> of ranks as an output

    std::vector<int> out = pagerankRanks(); // Example

    REQUIRE(isEqual(expected, out));
}

TEST_CASE("Correct Ranking: Small Dataset with Loop", "[small]")
{
    // TO-DO: What to do if ranks are equal?
    // Possibility 1: push_back in vector in order of node number
    // (but it will not be clear that they are equal in rank)
    // Possibility 2: Use a map<int,int> instead of a vector to store ranks as (node, rank)
    // (but we will have to figure out how to implement that)

    // Process "../../data/small.txt"
    
    std::vector<int> expected;
    expected.push_back(7);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    expected.push_back(4);
    expected.push_back(5);
    expected.push_back(6);

    // Run PageRank algorithm which returns a vector<int> of ranks as an output

    std::vector<int> out = pagerankRanks(); // Example

    REQUIRE(isEqual(expected, out));
}

