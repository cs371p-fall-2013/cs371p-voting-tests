// ----------------------------
// /cs371p-voting/TestVoting.c++
// Copyright (C) 2013
// CS371p Fall 2013
// Kevin Tran
// Pratik Patel
// ----------------------------

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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "gtest/gtest.h"

#include "Voting.h"


// -----------
// voting_read
// -----------

    TEST(Voting, read_1) 
    {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int num_cand;
        int num_ballots;
        int ballots[5][20];
        char names[4][81];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);

        ASSERT_EQ(num_cand, 3);
        ASSERT_EQ(num_ballots, 5);
        ASSERT_TRUE(strcmp(names[1], "John Doe") == 0);
        ASSERT_TRUE(strcmp(names[2], "Jane Smith") == 0);
        ASSERT_TRUE(strcmp(names[3], "Sirhan Sirhan") == 0);

    }


    TEST(Voting, read_2) 
    {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[5][81];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);

        ASSERT_TRUE(num_cand == 4);
        ASSERT_TRUE(num_ballots == 6);
        ASSERT_TRUE(strcmp(names[1], "Red") == 0);
        ASSERT_TRUE(strcmp(names[2], "Green") == 0);
        ASSERT_TRUE(strcmp(names[3], "Blue") == 0);
        ASSERT_TRUE(strcmp(names[4], "Orange") == 0);

    }


    TEST(Voting, read_3) 
    {
        std::istringstream r("6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
        int num_cand;
        int num_ballots;
        int ballots[1][20];
        char names[7][81];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);

        ASSERT_TRUE(num_cand == 6);
        ASSERT_TRUE(num_ballots == 1);
        ASSERT_TRUE(strcmp(names[1], "Abe") == 0);
        ASSERT_TRUE(strcmp(names[2], "Bay") == 0);
        ASSERT_TRUE(strcmp(names[3], "Cat") == 0);
        ASSERT_TRUE(strcmp(names[4], "Dog") == 0);
        ASSERT_TRUE(strcmp(names[5], "Eel") == 0);
        ASSERT_TRUE(strcmp(names[6], "Fat") == 0);
    }

    TEST(Voting, read_4) 
    {
        std::istringstream r("5\nK\nE\nV\nI\nN\n1 2 3 4 5\n2 1 3 4 5\n3 1 2 4 5\n4 1 2 3 5\n5 1 2 3 4");
        int num_cand;
        int num_ballots;
        int ballots[5][20];
        char names[6][81];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);

        ASSERT_TRUE(num_cand == 5);
        ASSERT_TRUE(num_ballots == 5);
        ASSERT_TRUE(strcmp(names[1], "K") == 0);
        ASSERT_TRUE(strcmp(names[2], "E") == 0);
        ASSERT_TRUE(strcmp(names[3], "V") == 0);
        ASSERT_TRUE(strcmp(names[4], "I") == 0);
        ASSERT_TRUE(strcmp(names[5], "N") == 0);
    }


  
// -----------
// voting_eval
// -----------


    TEST(Voting, eval_1) 
    {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int num_cand;
        int num_ballots;
        int ballots[5][20];
        char names[4][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);

        ASSERT_EQ(winning_tally, 3);
    }


    TEST(Voting, eval_2) 
    {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[5][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);

        ASSERT_EQ(winning_tally, 3);
    }


    TEST(Voting, eval_3) 
    {
        std::istringstream r("6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
        int num_cand;
        int num_ballots;
        int ballots[1][20];
        char names[7][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);

        ASSERT_EQ(winning_tally, 1);
    }


    TEST(Voting, eval_4) 
    {
        std::istringstream r("6\nP\nR\nA\nT\nI\nK\n1 2 3 4 5 6\n2 1 3 4 5 6\n3 1 2 4 5 6\n4 1 2 3 5 6\n5 1 2 3 4 6\n6 1 2 3 4 5");
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[7][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);

        ASSERT_EQ(winning_tally, 1);
    }


// ------------
// voting_print
// ------------


    TEST(Voting, print_1) 
    {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        int num_cand;
        int num_ballots;
        int ballots[5][20];
        char names[4][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(w, num_cand, names, tally, winning_tally);

        ASSERT_EQ(w.str(), "John Doe");
    }


    TEST(Voting, print_2) 
    {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        std::ostringstream w;
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[5][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(w, num_cand, names, tally, winning_tally);


        ASSERT_EQ(w.str(), "Red\nGreen");
    }


    TEST(Voting, print_3) 
    {
        std::istringstream r("6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
        std::ostringstream w;
        int num_cand;
        int num_ballots;
        int ballots[1][20];
        char names[7][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(w, num_cand, names, tally, winning_tally);

        ASSERT_EQ(w.str(), "Abe");
    }

    TEST(Voting, print_4) 
    {
        std::istringstream r("6\nP\nR\nA\nT\nI\nK\n1 2 3 4 5 6\n2 1 3 4 5 6\n3 1 2 4 5 6\n4 1 2 3 5 6\n5 1 2 3 4 6\n6 1 2 3 4 5");
        std::ostringstream w;
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[7][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);

        voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(w, num_cand, names, tally, winning_tally);

        ASSERT_EQ(w.str(), "P\nR\nA\nT\nI\nK");
    }


// -------------
// voting_solve
// -------------

    TEST(Voting, solve_1) 
    {
        std::istringstream r("1 6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
        std::ostringstream w;
        voting_solve(r, w);
        ASSERT_TRUE(w.str() == "Abe\n");
    }


    TEST(Voting, solve_2) 
    {
        std::istringstream r("2 3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        std::ostringstream w;
        voting_solve(r, w);
        ASSERT_TRUE(w.str() == "John Doe\n\nRed\nGreen\n");
    }


    TEST(Voting, solve_3) 
    {
        std::istringstream r("3 3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
        std::ostringstream w;
        voting_solve(r, w);
        ASSERT_TRUE(w.str() == "John Doe\n\nRed\nGreen\n\nAbe\n");
    }


    TEST(Voting, solve_4) 
    {
        std::istringstream r("1 5\nK\nE\nV\nI\nN\n1 2 3 4 5\n2 1 3 4 5\n3 1 2 4 5\n4 1 2 3 5\n5 1 2 3 4");
        std::ostringstream w;
        voting_solve(r, w);
        ASSERT_TRUE(w.str() == "K\nE\nV\nI\nN\n");
    }