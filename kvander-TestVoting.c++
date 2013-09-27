// --------------------------------
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// ----------
// TestVoting
// ----------

// ----
// read
// ----

TEST(Voting, read_1) {
    istringstream r("1\nKyle Vanderhoof\n1");
    vector<Candidate> c;
    int total = 1;
    const bool b = voting_read(r, c, total);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(c.size() == 1);
    ASSERT_TRUE(c[0].name == "Kyle Vanderhoof");
    ASSERT_TRUE(c[0].votes == 1);
    ASSERT_TRUE(c[0].lost == false);}

TEST(Voting, read_2) {
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                    "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    vector<Candidate> c;
    int total = 5;
    const bool b = voting_read(r, c, total);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(c.size() == 3);
    ASSERT_TRUE(c[0].name == "John Doe");
	ASSERT_TRUE(c[1].name == "Jane Smith");
	ASSERT_TRUE(c[2].name == "Sirhan Sirhan");
	ASSERT_TRUE(c[0].votes == 2);
	ASSERT_TRUE(c[1].votes == 2);
	ASSERT_TRUE(c[2].votes == 1);
    ASSERT_TRUE(c[0].lost == false);
    ASSERT_TRUE(c[1].lost == false);
    ASSERT_TRUE(c[2].lost == false);}



TEST(Voting, read_3) {
    std::istringstream r("4\nJim Jim\nJohn John\nDoug Doug\nFred Fred\n"
                         "1 2 3 4\n2 1 3 4\n4 3 2 1\n2 1 4 3");
    std::vector<Candidate> c;
    int total = 4;
    const bool b = voting_read(r, c, total);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(c.size() == 4);
    ASSERT_TRUE(c[0].name == "Jim Jim");
    ASSERT_TRUE(c[1].name == "John John");
    ASSERT_TRUE(c[2].name == "Doug Doug");
    ASSERT_TRUE(c[3].name == "Fred Fred");
    ASSERT_TRUE(c[0].votes == 1);
    ASSERT_TRUE(c[1].votes == 2);
    ASSERT_TRUE(c[2].votes == 0);
    ASSERT_TRUE(c[3].votes == 1);
    ASSERT_TRUE(c[0].lost == false);
    ASSERT_TRUE(c[1].lost == false);
    ASSERT_TRUE(c[2].lost == false);
    ASSERT_TRUE(c[3].lost == false);}

// ----
// eval
// ----

TEST(Voting, eval_1) {
    vector<Candidate> candidates;
    vector<string> b;
    int total = 1;
    b.push_back("");
    Candidate c = {"Kyle Vanderhoof", 1, false, b};
    candidates.push_back(c);
    b = voting_eval(candidates, total);
    ASSERT_TRUE(b.size() == 1);
    ASSERT_TRUE(b[0] == "Kyle Vanderhoof");}

TEST(Voting, eval_2) {
    vector<Candidate> candidates;
    vector<string> b;
    int total = 5;
    b.push_back("2 3");
    b.push_back("2 3");
    Candidate c = {"John Doe", 2, false, b};
    candidates.push_back(c);
    b.clear();
    b.push_back("1 3");
    b.push_back("3 1");
    c = {"Jane Smith", 2, false, b};
    candidates.push_back(c);
    b.clear();
    b.push_back("1 2");
    c = {"Sirhan Sirhan", 1, false, b};
    candidates.push_back(c);
    b = voting_eval(candidates, total);
    ASSERT_TRUE(b.size() == 1);
    ASSERT_TRUE(b[0] == "John Doe");}
        

        
TEST(Voting, eval_3) {
    vector<Candidate> candidates;
    vector<string> b;
    int total = 3;
    b.push_back("2 3");
    Candidate c = {"John John", 1, false, b};
    candidates.push_back(c);
    b.clear();
    b.push_back("3 1");
    c = {"Tim Tim", 1, false, b};
    candidates.push_back(c);
    b.clear();
    b.push_back("1 2");
    c = {"Jeff Jeff", 1, false, b};
    candidates.push_back(c);
    b = voting_eval(candidates, total);
    ASSERT_TRUE(b.size() == 3);
    ASSERT_TRUE(b[0] == "John John");
    ASSERT_TRUE(b[1] == "Tim Tim");
    ASSERT_TRUE(b[2] == "Jeff Jeff");}

// -----
// print
// -----

TEST(Voting, print_1) {
    ostringstream w;
    vector<string> names;
    names.push_back("Jimmyjohnson FredJuniourTheFifteenthAndAHalf");
    voting_print(w, names);
    ASSERT_TRUE(w.str() == "Jimmyjohnson FredJuniourTheFifteenthAndAHalf\n");}
        
TEST(Voting, print_2) {
    ostringstream w;
    vector<string> names;
    names.push_back("Fred Fred");
    names.push_back("Jim Jim");
    names.push_back("Ted Ted");
    voting_print(w, names);
    ASSERT_TRUE(w.str() == "Fred Fred\nJim Jim\nTed Ted\n");}
        
TEST(Voting, print_3) {
    ostringstream w;
    vector<string> names;
    names.push_back("");
    voting_print(w, names);
    ASSERT_TRUE(w.str() == "\n");}

// -----
// solve
// -----
TEST(Voting, solve_1) {
    istringstream r("1\n\n1\nKyle Vanderhoof\n"
                    "1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Kyle Vanderhoof\n");}

TEST(Voting, solve_2) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                    "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");}
         
TEST(Voting, solve_3) {
    istringstream r("2\n\n1\nJohn John\n"
                             "1\n\n"
                         "3\nBob Bob\nFred Fred\nJim Jim\n"
                             "1 2 3\n2 1 3\n3 2 1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John John\n\n"
                                  "Bob Bob\nFred Fred\nJim Jim\n");}