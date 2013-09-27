// --------------------------------
// projects/voting/TestVoting.c++
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

    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

    % valgrind TestVoting > TestVoting.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "gtest/gtest.h"

#include "Voting.h"
// #include "Voting.c++"

// -----------
// TestVoting
// -----------

// ----
// read
// ----
// std::istream& r, vector<Candidate>& candidates, int& election, int& total_ballots
// TEST(Voting, read_1) {
//     std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3 \n2 1 3 \n1 2 3 \n2 1 3 \n3 1 2 \n2 1 3\n");
//     vector<Candidate> candidates;
//     int election = 1;
//     int total_ballots = 10;

//     const bool b = voting_read(r, candidates, election, total_ballots);
//     ASSERT_TRUE(b == true);
//     ASSERT_TRUE(candidates.at(0).get_name() == "John Doe");
//     ASSERT_TRUE(candidates.at(1).get_name() == "Jane Smith");
//     ASSERT_TRUE(candidates.at(2).get_name() == "Sirhan Sirhan");
// }

// TEST(Voting, read_2) {
//     std::istringstream r("1\n\n5\nVinnie Pinson\nYen Michelson\nElyse Chou\nPilar Scheel\nFaviola Steller\n1 2 4 5 3 \n5 2 1 4 3 \n5 2 3 4 1\n5 1 2 3 4 \n4 2 1 5 3\n");
//     vector<Candidate> candidates;
//     int election = 1;
//     int total_ballots = 10;

//     const bool b = voting_read(r, candidates, election, total_ballots);
//     ASSERT_TRUE(b == true);
//     ASSERT_TRUE(candidates.at(0).get_name() == "Vinnie Pinson");
//     ASSERT_TRUE(candidates.at(1).get_name() == "Yen Michelson");
//     ASSERT_TRUE(candidates.at(2).get_name() == "Elyse Chou");
//     ASSERT_TRUE(candidates.at(1).get_name() == "Pilar Scheel");
//     ASSERT_TRUE(candidates.at(2).get_name() == "Faviola Steller");
// }

// TEST(Voting, read_3) {
//     std::istringstream r("2\nOlga\nRebecca\n1 2 \n2 1 \n1 2 \n2 1 \n1 2 \n2 1\n\n2");
//     vector<Candidate> candidates;
//     int election = 1;
//     int total_ballots = 10;

//     const bool b = voting_read(r, candidates, election, total_ballots);
//     ASSERT_TRUE(b == true);
//     ASSERT_TRUE(candidates.at(0).get_name() == "Olga");
//     ASSERT_TRUE(candidates.at(1).get_name() == "Rebecca");
// }

// ----
// eval
// ----

// TEST(Voting, eval_1) {
//     const int v = voting_eval(1, 10);
//     ASSERT_TRUE(v == 20);}

// TEST(Voting, eval_2) {
//     const int v = voting_eval(100, 200);
//     ASSERT_TRUE(v == 125);}

// TEST(Voting, eval_3) {
//     const int v = voting_eval(201, 210);
//     ASSERT_TRUE(v == 89);}

// TEST(Voting, eval_4) {
//     const int v = voting_eval(900, 1000);
//     ASSERT_TRUE(v == 174);}

// -----
// print
// -----

// TEST(Voting, print_1) {
//     std::ostringstream w;
//     int num_election = 1;
//     vector<string> winners;
//     // winners.push_back("Vinnie Pinson");
//     // winners.push_back("Pilar Scheel");
//     voting_print(w, winners, num_election);
//     ASSERT_TRUE(w.str() == "Vinnie Pinson\nPilar Scheel");
// }

// TEST(Voting, print_2) {
//     std::ostringstream w;
//     voting_print(w, 1, 10, 20);
//     ASSERT_TRUE(w.str() == "1 10 20\n");}

// TEST(Voting, print_3) {
//     std::ostringstream w;
//     voting_print(w, 1, 10, 20);
//     ASSERT_TRUE(w.str() == "1 10 20\n");}

// -----
// solve
// -----

// TEST(Voting, solve_1) {
//     std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3 \n2 1 3 \n1 2 3 \n2 1 3 \n3 1 2 \n2 1 3\n");    
//     std::ostringstream w;
//     voting_solve(r, w);
//     ASSERT_TRUE(w.str() == "John Doe\n");}

// TEST(Voting, solve_2) {
//     std::istringstream r("1\n\n5\nVinnie Pinson\nYen Michelson\nElyse Chou\nPilar Scheel\nFaviola Steller\n1 2 4 5 3 \n5 2 1 4 3 \n5 2 3 4 1\n5 1 2 3 4 \n4 2 1 5 3\n");
//     std::ostringstream w;
//     voting_solve(r, w);
//     ASSERT_TRUE(w.str() == "Faviola Steller\n");}

// TEST(Voting, solve_3) {
//     std::istringstream r("3\n\n2\nOlga\nRebecca\n1 2 \n2 1 \n1 2 \n2 1 \n1 2 \n2 1\n\n2\nRebecca\nOlga\n1 2\n 2 1\n 1 2\n\n2\nOlga\nRebecca\n1 2\n 2 1\n1 2\n1 2\n2 1\n");  
//     std::ostringstream w;
//     voting_solve(r, w);
//     ASSERT_TRUE(w.str() == "Olga\nRebecca\n\nRebecca\n\nOlga\n");}