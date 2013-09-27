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

using namespace std;

// -----------
// TestVoting
// -----------

TEST(Voting, read_1) {
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhann\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1");          
    string candidates[20];
    int ballots[1000][20];
    int num_candidates;
    int num_ballots;
    voting_read(r, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(3, num_candidates);
    ASSERT_EQ(5, num_ballots);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

TEST(Voting, read_2) {
    istringstream r("1\nJohn Done\n1");          
    string candidates[20];
    int ballots[1000][20];
    int num_candidates;
    int num_ballots;
    voting_read(r, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(1, num_candidates);
    ASSERT_EQ(1, num_ballots);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

TEST(Voting, read_3) {
    istringstream r("10\nOne\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nJohn\n10 1 2 3 4 5 6 7 8 9\n1 2 3 4 5 6 7 8 9 10\n10 2 3 4 5 6 7 8 9 1");          
    string candidates[20];
    int ballots[1000][20];
    int num_candidates;
    int num_ballots;
    voting_read(r, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(10, num_candidates);
    ASSERT_EQ(3, num_ballots);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

TEST(Voting, eval_1) {
    string candidates[20];
    candidates[0] = "One";
    int ballots[1000][20];
    int testBallots[1000][20];
    for(int i=0; i<5; i++) {
        for(int j=0; j<1; j++) {
            ballots[i][j] = 1;
            testBallots[i][j] = 1;
        }
    }
    int num_candidates = 1;
    int num_ballots = 5;
    string result = voting_eval(candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ("One", result);
    ASSERT_EQ("One", candidates[0]);
    ASSERT_EQ("", candidates[1]);

    int same = true;
    for(int i=0; i<5; i++)
        for(int j=0; j<1; j++)
            if(ballots[i][j] != testBallots[i][j])
                same = false;
    ASSERT_EQ(true, same);
}

TEST(Voting, eval_2) {
    string candidates[20];
    candidates[0] = "One";
    candidates[1] = "Two";
    int ballots[1000][20];
    int testBallots[1000][20];
    for(int i=0; i<10; i++) {
        for(int j=0; j<2; j++) {
            ballots[i][j] = j+1;
            testBallots[i][j] = j+1;
        }
    }
    int num_candidates = 2;
    int num_ballots = 10;
    string result = voting_eval(candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ("One", result);
    ASSERT_EQ("One", candidates[0]);
    ASSERT_EQ("Two", candidates[1]);
    ASSERT_EQ("", candidates[2]);

    int same = true;
    for(int i=0; i<10; i++)
        for(int j=0; j<2; j++)
            if(ballots[i][j] != testBallots[i][j])
                same = false;
    ASSERT_EQ(true, same);
}

TEST(Voting, eval_3) {
    string candidates[20];
    candidates[0] = "One";
    candidates[1] = "Two";
    candidates[2] = "Three";
    int ballots[1000][20];
    int testBallots[1000][20];
    for(int i=0; i<20; i++) {
        for(int j=3; j>0; j--) {
            ballots[i][j-1] = j;
            testBallots[i][j-1] = j;
        }
    }
    int num_candidates = 3;
    int num_ballots = 20;
    string result = voting_eval(candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ("One", result);
    ASSERT_EQ("One", candidates[0]);
    ASSERT_EQ("Two", candidates[1]);
    ASSERT_EQ("Three", candidates[2]);
    ASSERT_EQ("", candidates[3]);

    int same = true;
    for(int i=0; i<20; i++)
        for(int j=0; j<2; j++)
            if(ballots[i][j] != testBallots[i][j])
                same = false;
    ASSERT_EQ(true, same);
}

TEST(Voting, eval_4) {
    string candidates[20];
    candidates[0] = "One";
    candidates[1] = "Two";
    candidates[2] = "Three";
    candidates[3] = "Four";
    candidates[4] = "Five";
    candidates[5] = "Six";
    candidates[6] = "Seven";
    candidates[7] = "Eight";
    candidates[8] = "Nine";
    candidates[9] = "Ten";
    candidates[10] = "Eleven";
    candidates[11] = "Twelve";
    candidates[12] = "Thirteen";
    candidates[13] = "Fourteen";
    candidates[14] = "Fifteen";
    candidates[15] = "Sixteen";
    candidates[16] = "Seventeen";
    candidates[17] = "Eighteen";
    candidates[18] = "Nineteen";
    candidates[19] = "Twenty";
    int ballots[1000][20];
    int testBallots[1000][20];
    for(int i=0; i<10; i++) {
        for(int j=20; j>0; j--) {
            ballots[i][20-j] = j;
            testBallots[i][20-j] = j;
        }
    }
    for(int i=10; i<20; i++) {
        for(int j=0; j<20; j++) {
            ballots[i][j] = j+1;
            testBallots[i][j] = j+1;
        }
    }
    int num_candidates = 20;
    int num_ballots = 20;
    string result = voting_eval(candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ("One\nTwenty", result);
    ASSERT_EQ("One", candidates[0]);
    ASSERT_EQ("Two", candidates[1]);
    ASSERT_EQ("Three", candidates[2]);

    int same = true;
    for(int i=0; i<20; i++)
        for(int j=0; j<20; j++)
            if(ballots[i][j] != testBallots[i][j])
                same = false;
    ASSERT_EQ(true, same);
}

TEST(Voting, solve_1) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe");
}

TEST(Voting, solve_2) {
    istringstream r("1\n\n1\nJohn Doe\n1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe");
}

TEST(Voting, solve_3) {
    istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n2 1\n1 2\n1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe");
}

TEST(Voting, print_1) {
    ostringstream w;
    voting_print(w, "John Doe");
    ASSERT_EQ("John Doe", w.str());
}

TEST(Voting, print_2) {
    ostringstream w;
    voting_print(w, "John Doe\nJane Doe");
    ASSERT_EQ("John Doe\nJane Doe", w.str());
}
