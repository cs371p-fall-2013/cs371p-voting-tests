#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;

// read_ballot

TEST(Voting, read_ballot_1)
{
    vector<int> result = voting_read_ballot("1 2 3", 3);

    ASSERT_TRUE(result[0] == 0);
    ASSERT_TRUE(result[1] == 1);
    ASSERT_TRUE(result[2] == 2);
}

TEST(Voting, read_ballot_2)
{
    vector<int> result = voting_read_ballot("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20", 20);

    int i = 0;
    for(i = 0; i < 20; i++)
        ASSERT_TRUE(result[i] == i);
}

TEST(Voting, read_ballot_3)
{
    vector<int> result = voting_read_ballot("", 0);
}

TEST(Voting, read_ballot_4)
{
    vector<int> result = voting_read_ballot("20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1", 20);
    
    int i = 0;
    for(i = 0; i < 20; i++)
        ASSERT_TRUE(result[i] == 19 - i);
}

// eval

TEST(Voting, eval_1)
{
    std::istringstream r("1\nMelvin\n1\n1\n1\n1\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Melvin");
}

TEST(Voting, eval_2)
{
    std::istringstream r("3\nAbe\nBear\nCharlie\n1 2 3\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Abe");

    std::istringstream q("3\nAbe\nBear\nCharlie\n2 1 3\n\n");
    result = voting_eval(q);
    ASSERT_TRUE(result == "Bear");

    std::istringstream s("3\nAbe\nBear\nCharlie\n3 2 1\n\n");
    result = voting_eval(s);
    ASSERT_TRUE(result == "Charlie");
}

TEST(Voting, eval_3)
{    
    std::istringstream r("3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n1 2 3\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Abe");
}

TEST(Voting, eval_4)
{
    std::istringstream r("3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n3 2 1\n2 1 3\n2 3 1\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Bear");
}

TEST(Voting, eval_5)
{
    std::istringstream r("3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n2 1 3\n2 3 1\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Abe\nBear");

    std::istringstream q("3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n3 1 2\n3 2 1\n\n");
    result = voting_eval(q);
    ASSERT_TRUE(result == "Abe\nCharlie");

    std::istringstream s("3\nAbe\nBear\nCharlie\n3 2 1\n3 1 2\n2 1 3\n2 3 1\n\n");
    result = voting_eval(s);
    ASSERT_TRUE(result == "Bear\nCharlie");
}

TEST(Voting, eval_6)
{
    std::istringstream r("3\nAbe\nBear\nCharlie\n1 2 3\n2 1 3\n3 2 1\n\n");
    string result = voting_eval(r);
    ASSERT_TRUE(result == "Abe\nBear\nCharlie");
}

// print

TEST(Voting, print_1)
{
    std::ostringstream w;
    string input = "Abe";
    voting_print(w, input);
    ASSERT_TRUE(w.str() == "Abe\n");
}

TEST(Voting, print_2)
{
    std::ostringstream w;
    string input = "Abe\nCharlie";
    voting_print(w, input);
    ASSERT_TRUE(w.str() == "Abe\nCharlie\n");
}

TEST(Voting, print_3)
{
    std::ostringstream w;
    string input = "";
    voting_print(w, input);
    ASSERT_TRUE(w.str() == "\n");
}

// solve

TEST(Voting, solve_1)
{
    std::istringstream r("1\n\n3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n1 2 3\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Abe\n");
}

TEST(Voting, solve_2)
{
   std::istringstream r("2\n3\nAbe\nBear\nCharlie\n3 2 1\n3 1 2\n2 1 3\n2 3 1\n\n3\nAbe\nBear\nCharlie\n1 2 3\n2 1 3\n3 2 1\n\n");
   std::ostringstream w;
   voting_solve(r, w);
   ASSERT_TRUE(w.str() == "Bear\nCharlie\n\nAbe\nBear\nCharlie\n");
}
