// --------------------------------
// projects/collatz/TestVoting.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------


// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"


// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int j;
    const bool b = voting_read(r, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(j ==   3);

    ASSERT_EQ(names[0] , "John Doe");
    ASSERT_EQ(names[1] , "Jane Smith");
    ASSERT_EQ(names[2] , "Sirhan Sirhan");

    ASSERT_EQ(votes[0][0].front() , 1);
    ASSERT_EQ(votes[1][0].front(), 2);
    ASSERT_EQ(votes[1][1].front(), 2);
    ASSERT_EQ(votes[0][1].front(), 1);
    ASSERT_EQ(votes[2][0].front(), 3);


}


// -----
// solve
// -----

TEST(Voting, solve) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");}

TEST(Voting, solve_0_votes){
    std::istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n2 1 3 4\n1 2 3 4\n2 1 3 4\n3 1 2 4\n3 4 2 1\n2 1 3 4\n1 2 3 4");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "A\n");}

TEST(Voting, solve_clear_winner){
    std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "A\n");}

TEST(Voting, solve_multiple_runs){
    std::istringstream r("3\n\n3\nA\nB\nC\n1 2 3\n\n3\nA\nB\nC\n1 2 3\n\n3\nA\nB\nC\n1 2 3\n\n3\nA\nB\nC\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "A\n\nA\n\nA\n");
}

TEST(Voting, solve_tie){
    std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n2 1 3\n3 1 2");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "A\nB\n");
}

TEST(Voting, solve_clear_tie){
    std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n2 1 3\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "A\nB\n");
}

// -----
// print
// -----

TEST(Voting, print_more){
    std::ostringstream w;
    voting_print(1, "John Doe", w);
    ASSERT_TRUE(w.str() == "John Doe\n\n");
}

TEST(Voting, print_one){
    std::ostringstream w;
    voting_print(0, "John Doe", w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

// ----
// eval
// ----

TEST(Voting, eval_one) {
    names[0] = "John Doe";
    votes.push_back(vector<queue<int>>());
    votes[0].push_back(queue<int>());
    votes[0].back().push(1);
    string winners = voting_eval(1);
    ASSERT_EQ(winners, "John Doe");
}

TEST(Voting, eval_multiple) {
    names[0] = "A";
    names[1] = "B";
    names[2] = "C";
    votes.clear();
    votes.push_back(vector<queue<int>>());
    votes[0].push_back(queue<int>());
    votes[0].back().push(1);
    votes[0].back().push(2);
    votes[0].back().push(3);
    votes[0].push_back(queue<int>());
    votes[0].back().push(1);
    votes[0].back().push(2);
    votes[0].back().push(3);
    votes.push_back(vector<queue<int>>());
    votes[1].push_back(queue<int>());
    votes[1].back().push(2);
    votes[1].back().push(1);
    votes[1].back().push(3);
    votes[1].push_back(queue<int>());
    votes[1].back().push(2);
    votes[1].back().push(3);
    votes[1].back().push(1);
    votes.push_back(vector<queue<int>>());
    votes[2].push_back(queue<int>());
    votes[2].back().push(3);
    votes[2].back().push(1);
    votes[2].back().push(2);
    string winners = voting_eval(3);
    ASSERT_EQ(winners, "A");
}

TEST(Voting, eval_tie){
    names[0] = "A";
    names[1] = "B";
    names[2] = "C";
    votes.clear();
    votes.push_back(vector<queue<int>>());
    votes[0].push_back(queue<int>());
    votes[0].back().push(1);
    votes[0].back().push(2);
    votes[0].back().push(3);
    votes[0].push_back(queue<int>());
    votes[0].back().push(1);
    votes[0].back().push(2);
    votes[0].back().push(3);
    votes.push_back(vector<queue<int>>());
    votes[1].push_back(queue<int>());
    votes[1].back().push(2);
    votes[1].back().push(1);
    votes[1].back().push(3);
    votes[1].push_back(queue<int>());
    votes[1].back().push(2);
    votes[1].back().push(1);
    votes[1].back().push(3);
    votes[1].push_back(queue<int>());
    votes[1].back().push(2);
    votes[1].back().push(3);
    votes[1].back().push(1);
    votes.push_back(vector<queue<int>>());
    votes[2].push_back(queue<int>());
    votes[2].back().push(3);
    votes[2].back().push(1);
    votes[2].back().push(2);
    string winners = voting_eval(3);
    ASSERT_EQ(winners, "A\nB");
}



