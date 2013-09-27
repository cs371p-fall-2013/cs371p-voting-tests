/// --------------------------------
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

    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestVoting > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
using std::cout;
using std::endl;

#include "gtest/gtest.h"

#include "Voting.h"

extern int ballots[1000][20];
extern int ballot_counters[1000];
extern int candidate_votes[20];
extern int candidate_num;
extern int num_ballots;

// -----------
// TestVoting
// -----------

// ----
// read
// ----


TEST(Voting, read) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
    const bool b = voting_read(r);
    ASSERT_TRUE(b == true);
}

TEST(Voting, read_2) {
    std::istringstream r("6\nAgnes\nAgatha\nDolores\nGertrude\nHelen\nFlorence\n1 2 3 4 5 6 7\n7 3 2 1 4 6 5\n1 4 7 6 5 3 2\n");
    const bool b = voting_read(r);
    ASSERT_TRUE(b == true);
}


TEST(Voting, read_3) {
    std::istringstream r("4\nConstance\nChastity\nEdith\nCordelia\n3 4 2 1\n3 4 1 2\n2 3 1 4\n4 2 1 3\n");
    const bool b = voting_read(r);
    ASSERT_TRUE(b == true);
}


TEST(Voting, read_4) {
    std::istringstream r("7\nAhtahkakoop\nKaneonuskatew\nLittle Leaf\nPiloqutinnquaq\nChaubunagungamaug\nOne Who Yawns\nKisecawchuck\n1 2 3 4 5 6 7\n3 4 7 2 1 5 6 4\n2 4 3 1 6 5 7\n");
    const bool b = voting_read(r);
    ASSERT_TRUE(b == true);
}

// ----
// eval
// ----

TEST(Voting, eval_1) {
    std::ostringstream w;
    std::istringstream r("3\nBob\nJoe\nTom\n1 2 3\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    const bool b = voting_eval(w);
    ASSERT_TRUE(b);
    ASSERT_TRUE( w.str() == "Bob\n");
}

TEST(Voting, eval_2) {
    std::ostringstream w;
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    const bool b = voting_eval(w);
    ASSERT_TRUE(b);
    ASSERT_TRUE( w.str() == "John Doe\nJane Smith\n");
}

TEST(Voting, eval_3) {
    std::ostringstream w;
    std::istringstream r("6\nAgnes\nAgatha\nDolores\nGertrude\nHelen\nFlorence\n1 2 3 4 5 6 7\n7 3 2 1 4 6 5\n1 4 7 6 5 3 2\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    const bool b = voting_eval(w);
    ASSERT_TRUE(b);
    ASSERT_TRUE( w.str() == "Agnes\n");
}

TEST(Voting, eval_4) {
    std::ostringstream w;
    std::istringstream r("4\nConstance\nChastity\nEdith\nCordelia\n3 4 2 1\n3 4 1 2\n 2 3 1 4\n4 2 1 3\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    const bool b = voting_eval(w);
    ASSERT_TRUE(b);
    ASSERT_TRUE( w.str() == "Edith\n");
}

TEST(Voting, eval_5) {
    std::ostringstream w;
    std::istringstream r("7\nAhtahkakoop\nKaneonuskatew\nLittle Leaf\nPiloqutinnquaq\nChaubunagungamaug\nOne Who Yawns\nKisecawchuck\n1 2 3 4 5 6 7\n3 2 4 1 5 6 7\n4 3 1 5 6 7 2\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    const bool b = voting_eval(w);
    ASSERT_TRUE(b);
    ASSERT_TRUE( w.str() == "Ahtahkakoop\nLittle Leaf\nPiloqutinnquaq\n" );
}

// ----
// determine_least_votes
// ----
TEST(Voting, dlv_1) {
    std::ostringstream w;
    
    candidate_num = 2;
    candidate_votes[0] = 2;
    candidate_votes[1] = 1;
    
    num_ballots = 3;
    ballots[0][0] = 1;
    ballots[0][1] = 2;
    ballots[1][0] = 1;
    ballots[1][1] = 2;
    ballots[2][0] = 2;
    ballots[2][1] = 1;
    
    ballot_counters[0] = 0;
    ballot_counters[1] = 0;
    ballot_counters[2] = 0;

    determine_least_votes(w);

    ASSERT_TRUE( ballot_counters[2] == 1 );
}

TEST(Voting, dlv_2) {
    std::ostringstream w;
    
    candidate_num = 3;
    candidate_votes[0] = 2;
    candidate_votes[1] = 2;
    candidate_votes[2] = 1;
    
    num_ballots = 5;
    ballots[0][0] = 3;
    ballots[0][1] = 2;
    ballots[1][0] = 2;
    ballots[2][0] = 2;
    ballots[3][0] = 1;
    ballots[4][0] = 1;
    ballot_counters[0] = 0;
    ballot_counters[1] = 0;
    ballot_counters[2] = 0;
    ballot_counters[3] = 0;
    ballot_counters[4] = 0;

    determine_least_votes(w);

    ASSERT_TRUE( ballot_counters[0] == 1 );
    ASSERT_TRUE( ballot_counters[1] == 0 );
    ASSERT_TRUE( ballot_counters[2] == 0 );
    ASSERT_TRUE( ballot_counters[3] == 0 );
    ASSERT_TRUE( ballot_counters[4] == 0 );
}

TEST(Voting, dlv_3) {
    std::ostringstream w;
    
    candidate_num = 5;
    candidate_votes[0] = 2;
    candidate_votes[1] = 2;
    candidate_votes[2] = 1;
    candidate_votes[3] = 1;
    candidate_votes[4] = 1;
    
    num_ballots = 7;
    ballots[0][0] = 1;
    ballots[1][0] = 1;
    ballots[2][0] = 2;
    ballots[3][0] = 2;
    ballots[4][0] = 3;
    ballots[4][1] = 1;
    ballots[5][0] = 4;
    ballots[5][1] = 1;
    ballots[6][0] = 5;
    ballots[6][1] = 1;
    ballot_counters[0] = 0;
    ballot_counters[1] = 0;
    ballot_counters[2] = 0;
    ballot_counters[3] = 0;
    ballot_counters[4] = 0;
    ballot_counters[5] = 0;
    ballot_counters[6] = 0;

    determine_least_votes(w);

    ASSERT_TRUE( ballot_counters[0] == 0 );
    ASSERT_TRUE( ballot_counters[1] == 0 );
    ASSERT_TRUE( ballot_counters[2] == 0 );
    ASSERT_TRUE( ballot_counters[3] == 0 );
    ASSERT_TRUE( ballot_counters[4] == 1 );
    ASSERT_TRUE( ballot_counters[5] == 1 );
    ASSERT_TRUE( ballot_counters[6] == 1 );
}

// -----
// print
// -----

TEST(Voting, print) {
    std::ostringstream w;
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    voting_print(w);
    ASSERT_TRUE( w.str() == "3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");

}

TEST(Voting, print_3) {
    std::ostringstream w;
    std::istringstream r("6\nAgnes\nAgatha\nDolores\nGertrude\nHelen\nFlorence\n1 2 3 4 5 6\n3 2 1 4 6 5\n1 4 6 5 3 2\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    voting_print(w);
    ASSERT_TRUE( w.str() == "6\nAgnes\nAgatha\nDolores\nGertrude\nHelen\nFlorence\n1 2 3 4 5 6\n3 2 1 4 6 5\n1 4 6 5 3 2\n");
}

TEST(Voting, print_4) {
    std::ostringstream w;
    std::istringstream r("4\nConstance\nChastity\nEdith\nCordelia\n3 4 2 1\n3 4 1 2\n 2 3 1 4\n4 2 1 3\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    voting_print(w);
    ASSERT_TRUE( w.str() == "4\nConstance\nChastity\nEdith\nCordelia\n3 4 2 1\n3 4 1 2\n2 3 1 4\n4 2 1 3\n");
}

TEST(Voting, print_5) {
    std::ostringstream w;
    std::istringstream r("7\nAhtahkakoop\nKaneonuskatew\nLittle Leaf\nPiloqutinnquaq\nChaubunagungamaug\nOne Who Yawns\nKisecawchuck\n1 2 3 4 5 6 7\n3 2 4 1 5 6 7\n4 3 1 5 6 7 2\n");
    const bool a = voting_read(r);
    ASSERT_TRUE(a);
    voting_print(w);
    ASSERT_TRUE( w.str() == "7\nAhtahkakoop\nKaneonuskatew\nLittle Leaf\nPiloqutinnquaq\nChaubunagungamaug\nOne Who Yawns\nKisecawchuck\n1 2 3 4 5 6 7\n3 2 4 1 5 6 7\n4 3 1 5 6 7 2\n");
}

// -----
// solve
// -----
TEST(Voting, solve) {
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n\nJohn Doe\n");}


TEST(Voting, solve_2) {
    std::ostringstream w;
    std::istringstream r("1\n\n3\nBob\nJoe\nTom\n1 2 3\n");
    voting_solve(r, w);
    ASSERT_TRUE( w.str() == "Bob\n");
}


TEST(Voting, solve_3) {
    std::ostringstream w;
    std::istringstream r("1\n\n6\nAgnes\nAgatha\nDolores\nGertrude\nHelen\nFlorence\n1 2 3 4 5 6 7\n7 3 2 1 4 6 5\n1 4 7 6 5 3 2\n");
    voting_solve(r, w);
    ASSERT_TRUE( w.str() == "Agnes\n");
}

TEST(Voting, solve_4) {
    std::ostringstream w;
    std::istringstream r("1\n\n4\nConstance\nChastity\nEdith\nCordelia\n3 4 2 1\n3 4 1 2\n 2 3 1 4\n4 2 1 3\n");
    voting_solve(r,w);
    ASSERT_TRUE( w.str() == "Edith\n");
}

TEST(Voting, solve_5) {
    std::ostringstream w;
    std::istringstream r("1\n\n7\nAhtahkakoop\nKaneonuskatew\nLittle Leaf\nPiloqutinnquaq\nChaubunagungamaug\nOne Who Yawns\nKisecawchuck\n1 2 3 4 5 6 7\n3 2 4 1 5 6 7\n4 3 1 5 6 7 2\n");
    voting_solve(r, w);
    ASSERT_TRUE( w.str() == "Ahtahkakoop\nLittle Leaf\nPiloqutinnquaq\n" );
}

