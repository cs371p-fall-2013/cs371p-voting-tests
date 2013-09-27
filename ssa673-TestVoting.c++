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

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read_1) {
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    int i;
    int j;
    voting_read(r, i, j);
    ASSERT_TRUE(i ==    5);
    ASSERT_TRUE(j ==   3);}

TEST(Voting, read_2){
    std::istringstream r ("1\ndkkas\n1");
    int i;
    int j;
    voting_read(r, i, j);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   1);} 
TEST(Voting, read_3){
    std::istringstream r ("2\nsjel dfkis\nalkyggkeaa\n2 1\n1 2\n1 2\n");
    int i;
    int j;
    voting_read(r, i, j);
    ASSERT_TRUE(i ==    3);
    ASSERT_TRUE(j ==   2);} 
TEST(Voting, read_4){
    std::istringstream r ("3\nkgxgphosw  rhhzbntoy\nzrmp lvwhrv zy eeozv\naiobrwwrvnisspxc qqi\n3 1 2\n1 2 3\n3 1 2\n2 1 3\n2 3 1\n1 3 2\n2 1 3\n3 1 2\n1 2 3\n1 2 3\n");
    int i;
    int j;
    voting_read(r, i, j);
    ASSERT_TRUE(i ==    10);
    ASSERT_TRUE(j ==   3);}
TEST(Voting, read_5){
    std::istringstream r ("5\ndefhnswvq lv fumtphf\nm z zaium yn xgrmipc\nkcp j h ohudiplzljgk\nudo fprxsuwgrtxepb l\nwfbsgipqdkvl ryuprev\n5 3 2 1 4\n1 5 4 3 2\n4 2 1 3 5\n1 5 4 3 2\n2 4 3 5 1\n5 3 4 2 1\n4 5 1 3 2\n3 2 1 4 5\n2 5 4 3 1\n5 1 4 3 2\n3 4 5 2 1\n3 5 4 1 2\n3 1 5 2 4\n2 4 1 3 5\n4 2 3 1 5\n3 2 4 5 1\n4 2 5 3 1\n2 4 1 5 3\n2 3 5 4 1\n3 1 4 5 2\n5 2 4 3 1\n1 5 3 4 2\n2 4 5 3 1\n4 3 5 1 2\n2 3 1 5 4\n1 2 4 3 5\n2 4 3 1 5\n5 2 1 3 4\n1 4 5 3 2\n4 5 3 2 1\n4 2 5 3 1\n5 4 2 1 3\n4 2 1 3 5\n2 1 3 4 5\n1 5 3 4 2\n3 4 1 5 2\n5 4 3 1 2\n3 1 4 5 2\n5 4 1 2 3\n4 2 1 5 3\n2 4 3 1 5\n5 1 4 3 2\n2 4 5 1 3\n4 1 5 2 3\n5 1 3 4 2\n4 5 3 2 1\n1 4 5 3 2\n5 2 1 4 3\n2 5 3 4 1\n5 3 1 4 2\n1 4 3 2 5\n3 1 5 4 2\n1 3 5 4 2\n4 3 5 1 2\n2 4 3 1 5\n4 3 1 2 5\n1 2 3 5 4\n3 1 2 4 5\n3 2 4 5 1\n2 3 4 5 1\n4 5 2 1 3\n5 4 2 3 1\n4 3 1 5 2\n4 5 3 1 2\n1 4 2 5 3\n1 4 5 2 3\n2 3 4 5 1\n4 1 5 3 2\n5 1 3 2 4\n4 1 3 5 2\n4 2 5 1 3\n5 4 1 2 3\n1 3 4 2 5\n3 5 2 4 1\n4 2 1 3 5\n5 4 2 1 3\n5 2 3 1 4\n1 2 3 4 5\n3 4 1 2 5\n1 5 2 3 4\n3 2 4 1 5\n1 4 2 3 5\n2 3 1 5 4\n5 2 1 3 4\n3 4 1 2 5\n4 2 1 5 3\n4 1 3 5 2\n1 4 5 2 3\n1 3 2 4 5\n5 4 1 3 2\n3 2 1 4 5\n1 4 3 5 2\n1 4 2 3 5\n2 1 3 4 5\n2 3 5 4 1\n4 5 2 1 3\n4 2 1 5 3\n2 5 1 4 3\n4 5 1 3 2\n2 3 5 4 1\n5 3 2 1 4\n1 5 4 3 2\n4 2 1 3 5\n1 5 4 3 2\n2 4 3 5 1\n5 3 4 2 1\n4 5 1 3 2\n3 2 1 4 5\n2 5 4 3 1\n5 1 4 3 2\n3 4 5 2 1\n3 5 4 1 2\n3 1 5 2 4\n2 4 1 3 5\n4 2 3 1 5\n3 2 4 5 1\n4 2 5 3 1\n2 4 1 5 3\n2 3 5 4 1\n3 1 4 5 2\n5 2 4 3 1\n1 5 3 4 2\n2 4 5 3 1\n4 3 5 1 2\n2 3 1 5 4\n1 2 4 3 5\n2 4 3 1 5\n5 2 1 3 4\n1 4 5 3 2\n4 5 3 2 1\n4 2 5 3 1\n5 4 2 1 3\n4 2 1 3 5\n2 1 3 4 5\n1 5 3 4 2\n3 4 1 5 2\n5 4 3 1 2\n3 1 4 5 2\n5 4 1 2 3\n4 2 1 5 3\n2 4 3 1 5\n5 1 4 3 2\n2 4 5 1 3\n4 1 5 2 3\n5 1 3 4 2\n4 5 3 2 1\n1 4 5 3 2\n5 2 1 4 3\n2 5 3 4 1\n5 3 1 4 2\n1 4 3 2 5\n3 1 5 4 2\n1 3 5 4 2\n4 3 5 1 2\n2 4 3 1 5\n4 3 1 2 5\n1 2 3 5 4\n3 1 2 4 5\n3 2 4 5 1\n2 3 4 5 1\n4 5 2 1 3\n5 4 2 3 1\n4 3 1 5 2\n4 5 3 1 2\n1 4 2 5 3\n1 4 5 2 3\n2 3 4 5 1\n4 1 5 3 2\n5 1 3 2 4\n4 1 3 5 2\n4 2 5 1 3\n5 4 1 2 3\n1 3 4 2 5\n3 5 2 4 1\n4 2 1 3 5\n5 4 2 1 3\n5 2 3 1 4\n1 2 3 4 5\n3 4 1 2 5\n1 5 2 3 4\n3 2 4 1 5\n1 4 2 3 5\n2 3 1 5 4\n5 2 1 3 4\n3 4 1 2 5\n4 2 1 5 3\n4 1 3 5 2\n1 4 5 2 3\n1 3 2 4 5\n5 4 1 3 2\n3 2 1 4 5\n1 4 3 5 2\n1 4 2 3 5\n2 1 3 4 5\n2 3 5 4 1\n4 5 2 1 3\n4 2 1 5 3\n2 5 1 4 3\n4 5 1 3 2\n2 3 5 4 1\n");
    int i;
    int j;voting_read(r, i, j);
    ASSERT_TRUE(i ==    200);
    ASSERT_TRUE(j ==   5);} 


//eval
TEST(Voting, eval_1) {
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    int i;
    int j;
    int numWinners;
    voting_read(r, i, j);
    voting_eval(i, j, numWinners);
    ASSERT_TRUE(numWinners == 1);}

TEST(Voting, eval_2) {
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 1 2\n");
    int i;
    int j;
    int numWinners;
    voting_read(r, i, j);
    voting_eval(i, j, numWinners);
    ASSERT_TRUE(numWinners == 3);}
    
TEST(Voting, eval_3) {
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 2 3\n2 1 3\n");
    int i;
    int j;
    int numWinners;
    voting_read(r, i, j);
    voting_eval(i, j, numWinners);
    ASSERT_TRUE(numWinners == 2);}
    
TEST(Voting, eval_4) {
    std::istringstream r ("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n");
    int i;
    int j;
    int numWinners;
    voting_read(r, i, j);
    voting_eval(i, j, numWinners);
    ASSERT_TRUE(numWinners == 2);}


//solve
TEST(Voting, solve_1) {
    std::istringstream r ("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n");
    std::ostringstream x;
    voting_solve(r, x);
    ASSERT_TRUE(x.str() == "John Doe\nJane Smith\n");}
//after this does not do the line fixing because of global
TEST(Voting, solve_2) {
    std::istringstream r ("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 1 3\n3 1 2");
    std::ostringstream x;
    voting_solve(r, x);
    ASSERT_TRUE(x.str() == "Jane Smith\n\n");}
TEST(Voting, solve_3) {
    std::istringstream r ("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n3 1 2\n1 3 2");
    std::ostringstream x;
    voting_solve(r, x);
    ASSERT_TRUE(x.str() == "John Doe\nJane Smith\nSirhan Sirhan\n\n");}
TEST(Voting, solve_4) {
    std::istringstream r ("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n3 1 2\n");
    std::ostringstream x;
    voting_solve(r, x);
    ASSERT_TRUE(x.str() == "Jane Smith\n\n");}
TEST(Voting, solve_5) {
    std::istringstream r ("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n3 1 2\n3 1 2\n3 1 2\n3 1 2\n3 1 2\n");
    std::ostringstream x;
    voting_solve(r, x);
    ASSERT_TRUE(x.str() == "Sirhan Sirhan\n\n");}

//print
TEST(Voting, print_1) {
    std::ostringstream w;
    int numberOfWinners = 3;
    voting_print(w, numberOfWinners, 1, true);
    ASSERT_TRUE(w.str() == ("test\ntest\ntest\n"));}
TEST(Voting, print_2) {
    std::ostringstream w;
    int numberOfWinners = 2;
    voting_print(w, numberOfWinners, 1, true);
    ASSERT_TRUE(w.str() == ("test\ntest\n"));}
TEST(Voting, print_3) {
    std::ostringstream w;
    int numberOfWinners = 1;
    voting_print(w, numberOfWinners, 1, true);
    ASSERT_TRUE(w.str() == ("test\n"));}
TEST(Voting, print_4) {
    std::ostringstream w;
    int numberOfWinners = 4;
    voting_print(w, numberOfWinners, 1, true);
    ASSERT_TRUE(w.str() == ("test\ntest\ntest\ntest\n"));}
TEST(Voting, print_5) {
    std::ostringstream w;
    int numberOfWinners = 5;
    voting_print(w, numberOfWinners, 1, true);
    ASSERT_TRUE(w.str() == ("test\ntest\ntest\ntest\ntest\n"));}

