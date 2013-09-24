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


#include "gtest/gtest.h"

#include "Voting.h"
#include "Election.h"
#include "Voter.h"
#include "Candidate.h"

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read_basic) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Sirhan Sirhan") == 0);
}

TEST(Voting, read_votes_basic) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    //const bool b = voting_read(r, i, j);
    //ASSERT_TRUE(b == true);
    //ASSERT_TRUE(i ==    1);
    //ASSERT_TRUE(j ==   10);
    }

/*
// ----
// eval
// ----

TEST(Voting, eval_1) {
    const int v = voting_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Voting, eval_2) {
    const int v = voting_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Voting, eval_3) {
    const int v = voting_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Voting, eval_4) {
    const int v = voting_eval(900, 1000);
    ASSERT_TRUE(v == 174);}


// -----
// print
// -----

TEST(Voting, print) {
    std::ostringstream w;
    voting_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
*/
// -----
// solve
// -----
/*
TEST(Voting, solve) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");}
*/
