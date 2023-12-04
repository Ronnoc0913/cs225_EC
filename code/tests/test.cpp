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
    std::vector<double> expected;
    expected.push_back(0.16271695346751378);
    expected.push_back(0.2391038064085376);
    expected.push_back(0.08172837651407977);
    expected.push_back(0.36346825390511567);
    expected.push_back(0.2391038064085376);
    expected.push_back(0.1279826097047531);

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
