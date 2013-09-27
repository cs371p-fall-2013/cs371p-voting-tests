// --------------------------------
// projects/collatz/TestVoting.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    %   g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

    %   valgrind TestVoting > TestVoting.out
*/

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

// // ----
// // eval
// // ----


TEST(Voting, eval_1) {
    std::vector<string> v;

    std::string candidates [3] = {"John Doe","Jane Smith","Sirhan Sirhan"};
    int votes1 [] = {1, 2, 3};
    int votes2 [] = {1, 2, 3};
    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    int cand = 3;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("John Doe") == 0);}


TEST(Voting, eval_2) {
    std::vector<string> v;

    std::string candidates [2] = {"John Doe", "Sirhan Sirhan"};
    int votes1 [] = {1, 2};
    int votes2 [] = {2, 1};
    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    int cand = 2;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("John Doe") == 0);
    ASSERT_TRUE(v[1].compare("Sirhan Sirhan") == 0);}


TEST(Voting, eval_3) {
    std::vector<string> v;

    std::string candidates [3] = {"John Doe","Jane Smith","Sirhan Sirhan"};
    int votes1 [] = {1, 2, 3};
    int votes2 [] = {1, 2, 3};
    int votes3 [] = {2, 3, 1};
    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::deque<int> dVotes3 (votes3, votes3 + sizeof(votes3)/sizeof(int));

    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    ballots.push_back(dVotes3);

    int cand = 3;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("John Doe") == 0);}


TEST(Voting, eval_4) {
    std::vector<string> v;

    std::string candidates [4] = {"John Doe","Jane Smith","Sirhan Sirhan", "Chris Coney"};
    int votes1 [] = {4, 1, 2, 3};
    int votes2 [] = {4, 1, 2, 3};
    int votes3 [] = {4, 2, 3, 1};
    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::deque<int> dVotes3 (votes3, votes3 + sizeof(votes3)/sizeof(int));

    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    ballots.push_back(dVotes3);

    int cand = 4;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("Chris Coney") == 0);}


TEST(Voting, eval_5) {
    std::vector<string> v;

    std::string candidates [4] = {"John Doe","Jane Smith","Sirhan Sirhan", "Chris Coney"};
    int votes1 [] = {2, 1, 3, 4};
    int votes2 [] = {2, 1, 3, 4};
    int votes3 [] = {2, 2, 3, 1};
    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::deque<int> dVotes3 (votes3, votes3 + sizeof(votes3)/sizeof(int));

    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    ballots.push_back(dVotes3);

    int cand = 4;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("Jane Smith") == 0);}

TEST(Voting, eval_6) {
    std::vector<string> v;

    std::string candidates [4] = {"John Doe","Jane Smith","Sirhan Sirhan", "Chris Coney"};
    int votes1 [] = {1, 2, 3, 4};
    int votes2 [] = {2, 3, 4, 1};
    int votes3 [] = {3, 4, 1, 2};
    int votes4 [] = {4, 1, 2, 3};

    std::deque<int> dVotes1 (votes1, votes1 + sizeof(votes1)/sizeof(int));
    std::deque<int> dVotes2 (votes2, votes2 + sizeof(votes2)/sizeof(int));
    std::deque<int> dVotes3 (votes3, votes3 + sizeof(votes3)/sizeof(int));
    std::deque<int> dVotes4 (votes4, votes4 + sizeof(votes4)/sizeof(int));

    std::vector< std::deque<int> > ballots;
    ballots.push_back(dVotes1);
    ballots.push_back(dVotes2);
    ballots.push_back(dVotes3);
    ballots.push_back(dVotes4);

    int cand = 4;
    v = voting_eval(candidates, ballots, cand);
    ASSERT_TRUE(v[0].compare("John Doe") == 0);
    ASSERT_TRUE(v[1].compare("Jane Smith") == 0);
    ASSERT_TRUE(v[2].compare("Sirhan Sirhan") == 0);
    ASSERT_TRUE(v[3].compare("Chris Coney") == 0);
}
// -----
// solve
// -----

// TEST(Voting, solve_1) {
//     std:: string input = "1\n\n3\nJohn Doe\nJane Smith\nSirhanSirhan";
//     std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhanSirhan");
//     voting_solve(r);
//     ASSERT_TRUE(input == "1\n\n3\nJohn Doe\nJane Smith\nSirhanSirhan");
// }

// TEST(Voting, solve_2) {
//     std::istringstream r("1\n 2\n John Doe\n Jane Smith\n 1 2\n 1 2");
//     std::ostringstream w;
//     voting_solve(r, w);
//     ASSERT_TRUE(w.str() == "John Doe");}    
