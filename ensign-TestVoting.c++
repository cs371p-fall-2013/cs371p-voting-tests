// --------------------------------
// TestVoting.c++
// Copyright (C) 2013
// Katie Ensign Ryan Niemann
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

// ----
// read
// ----

TEST(Voting, read_UVa_example) {
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1];
		string names[MAX_CANDIDATES];
		int ballotIndex = 0;    
    const bool b = voting_read(r, ballots, names, ballotIndex);
    ASSERT_TRUE(b == true);
		ASSERT_TRUE(ballots[0][2] == 2);
		ASSERT_TRUE(ballots[3][3] == 3);
    ASSERT_TRUE(names[0] == "John Doe");
    ASSERT_TRUE(names[1] == "Jane Smith");
    ASSERT_TRUE(names[2] == "Sirhan Sirhan");
    ASSERT_TRUE(ballotIndex == 5);}

TEST(Voting, read_strange_characters) {
    istringstream r("2\n$&*#^\n*#$$\n1 2 \n2 1 \n1 2\n2 1\n1 2");
    int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1];
		string names[MAX_CANDIDATES];
		int ballotIndex = 0;    
    const bool b = voting_read(r, ballots, names, ballotIndex);
    ASSERT_TRUE(b == true);
		ASSERT_TRUE(ballots[0][2] == 2);
		ASSERT_TRUE(ballots[3][2] == 1);
    ASSERT_TRUE(names[0] == "$&*#^");
    ASSERT_TRUE(names[1] == "*#$$");
    ASSERT_TRUE(ballotIndex == 5);}

TEST(Voting, read_single_ballot) {
    istringstream r("3\na\nb\nc\n1 2 3");
    int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1];
		string names[MAX_CANDIDATES];
		int ballotIndex = 0;    
    const bool b = voting_read(r, ballots, names, ballotIndex);
    ASSERT_TRUE(b == true);
		ASSERT_TRUE(ballots[0][2] == 2);
		ASSERT_TRUE(ballots[0][3] == 3);
    ASSERT_TRUE(names[0] == "a");
    ASSERT_TRUE(names[1] == "b");
    ASSERT_TRUE(names[2] == "c");
    ASSERT_TRUE(ballotIndex == 1);}

TEST(Voting, read_max_candidates) {
    istringstream r("20\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr\ns\nt\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
    int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1];
		string names[MAX_CANDIDATES];
		int ballotIndex = 0;    
    const bool b = voting_read(r, ballots, names, ballotIndex);
    ASSERT_TRUE(b == true);
		ASSERT_TRUE(ballots[0][2] == 2);
		ASSERT_TRUE(ballots[0][3] == 3);
    ASSERT_TRUE(names[0] == "a");
    ASSERT_TRUE(names[1] == "b");
    ASSERT_TRUE(names[19] == "t");
    ASSERT_TRUE(ballotIndex == 1);}

// ----
// eval
// ----

TEST(Voting, eval_UVa_example) {
		string names[MAX_CANDIDATES] = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1, 2, 3},{1, 2, 1, 3},{1, 2, 3, 1},{1, 1, 2, 3},{1, 3, 1, 2}};
    int ballotIndex = 5;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
    ASSERT_TRUE(losers[0] == 3);
		ASSERT_TRUE(v[0] == "John Doe");}

TEST(Voting, eval_tie_at_beginning) {
		string names[MAX_CANDIDATES] = {"Red", "Green", "Blue", "Orange"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1, 2, 3, 4},{1, 2, 1, 3, 4},{1, 3, 2, 1, 4},{1, 4, 2, 3, 1}};
    int ballotIndex = 4;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
    ASSERT_TRUE(losers.empty());
		ASSERT_TRUE(v[0] == "Red");
		ASSERT_TRUE(v[1] == "Green");
		ASSERT_TRUE(v[2] == "Blue");
		ASSERT_TRUE(v[3] == "Orange");}

TEST(Voting, eval_tie_from_quiz) {
		string names[MAX_CANDIDATES] = {"Red", "Green", "Blue", "Orange"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1, 2, 3, 4},{1, 2, 1, 3, 4},{1, 2, 3, 1, 4},
			 {1, 1, 2, 3, 4},{1, 3, 4, 1, 2},{1, 4, 3, 2, 1}};
    int ballotIndex = 6;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
    ASSERT_TRUE(losers[0] == 3);
		ASSERT_TRUE(losers[1] == 4);
		ASSERT_TRUE(v[0] == "Red");
		ASSERT_TRUE(v[1] == "Green");}

TEST(Voting, eval_tricky_tie) {
		string names[MAX_CANDIDATES] = 
			{"Red", "Green", "Blue", "Orange", "Yellow", "Purple"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1, 2, 3, 4, 5, 6},{1, 2, 1, 3, 4, 5, 6},{1, 2, 3, 1, 4, 5, 6},
			 {1, 1, 2, 3, 4, 5, 6},{1, 2, 4, 1, 3, 5, 6},{1, 3, 4, 2, 1, 5, 6},
			 {1, 5, 4, 3, 1, 2, 6},{1, 4, 6, 2, 1, 3, 5},{1, 1, 5, 6, 4, 3, 2},
			 {1, 6, 5, 4, 3, 1, 2}};
    int ballotIndex = 10;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
    ASSERT_TRUE(losers[0] == 3);
		ASSERT_TRUE(losers[1] == 4);
		ASSERT_TRUE(losers[2] == 5);
		ASSERT_TRUE(losers[3] == 6);
		ASSERT_TRUE(v[0] == "Red");
		ASSERT_TRUE(v[1] == "Green");}

TEST(Voting, eval_tricky_win) {
		string names[MAX_CANDIDATES] = 
			{"Red", "Green", "Blue", "Orange", "Yellow", "Purple", "Gray", "Black"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1, 2, 3, 4, 5, 6, 7, 8},{1, 2, 1, 3, 4, 5, 6, 7, 8},
			 {1, 2, 3, 1, 4, 5, 6, 7, 8},{1, 1, 2, 3, 4, 5, 6, 7, 8},
			 {1, 3, 4, 1, 2, 5, 6, 7, 8},{1, 3, 4, 2, 1, 5, 6, 7, 8},
			 {1, 5, 4, 3, 1, 2, 6, 7, 8},{1, 4, 6, 2, 1, 3, 5, 7, 8},
			 {1, 6, 5, 1, 4, 3, 2, 7, 8},{1, 7, 6, 5, 4, 3, 1, 2, 8},
			 {1, 8, 7, 6, 5, 2, 4, 3, 1}};
    int ballotIndex = 11;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
		ASSERT_TRUE(losers[0] == 4);
		ASSERT_TRUE(losers[1] == 5);
		ASSERT_TRUE(losers[2] == 6);
		ASSERT_TRUE(losers[3] == 7);
		ASSERT_TRUE(losers[4] == 8);
		ASSERT_TRUE(losers[5] == 1);
		ASSERT_TRUE(v[0] == "Green");}

TEST(Voting, eval_single_candidate) {
		string names[MAX_CANDIDATES] = {"a"};
		int ballots[MAX_BALLOTS][MAX_CANDIDATES + 1] = 
			{{1, 1},{1, 1},{1, 1}};
    int ballotIndex = 3;
		vector<int> losers;
		const vector<string> v = voting_eval(names, ballots, ballotIndex, losers);
		ASSERT_TRUE(v[0] == "a");}

// -----
// print
// -----

TEST(Voting, print_one_test_case) {
    ostringstream w;
    vector<string> result = {"John Doe"};
		voting_print(w, result);
    ASSERT_TRUE(w.str() == "John Doe");}

TEST(Voting, print_many_test_cases) {
    ostringstream w;
    vector<string> result = {"Red","","Green"};
		voting_print(w, result);
    ASSERT_TRUE(w.str() == "Red\n\nGreen");}

TEST(Voting, print_many_test_cases_with_ties) {
    ostringstream w;
    vector<string> result = {"Apple","Banana","","Orange","Strawberry","Peach"};
		voting_print(w, result);
    ASSERT_TRUE(w.str() == "Apple\nBanana\n\nOrange\nStrawberry\nPeach");}

// -----
// solve
// -----

TEST(Voting, solve_UVa_example) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
		int numTestCases;
    voting_solve(r, w, numTestCases);
		ASSERT_TRUE(numTestCases == 1);
    ASSERT_TRUE(w.str() == "John Doe");}

TEST(Voting, solve_multiple_test_cases) {
    istringstream r("2\n\n3\nA\nB\nC\n1 2 3\n2 1 3\n3 2 1\n\n3\nD\nE\nF\n1 2 3\n1 3 2\n 2 1 3");
    ostringstream w;
		int numTestCases;
    voting_solve(r, w, numTestCases);
		ASSERT_TRUE(numTestCases == 2);
    ASSERT_TRUE(w.str() == "A\nB\nC\n\nD");}

TEST(Voting, solve_multiple_test_cases_2) {
    istringstream r("2\n\n2\nApple\nBanana\n1 2\n2 1\n\n3\nOrange\nStrawberry\nPeach\n1 2 3\n2 1 3\n2 3 1");
    ostringstream w;
		int numTestCases;
    voting_solve(r, w, numTestCases);
		ASSERT_TRUE(numTestCases == 2);
    ASSERT_TRUE(w.str() == "Apple\nBanana\n\nStrawberry");}
