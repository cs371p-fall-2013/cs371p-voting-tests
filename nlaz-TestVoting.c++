// --------------------------------
// Skeleton from:
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// 
// Adapted to: TestVoting.c++
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

// -----
// check_winners
// -----
TEST(Voting, winners1) {
    Ballot a;
    a.AddVote(1);
    Candidate candidate1("Hank Schrader");
    candidate1.AddBallot(a);
    std::vector<Candidate> candidates = {candidate1};
    std::vector<Candidate> winners;
    int num_ballots = 1;
    ASSERT_TRUE(check_winners(candidates,winners,num_ballots));
    ASSERT_TRUE(winners.size() == 1);}

TEST(Voting, winners2) {
    Ballot a;
    Ballot b;
    Ballot c;
    a.AddVote(1);
    a.AddVote(2);
    a.AddVote(3);
    b.AddVote(2);
    b.AddVote(1);
    b.AddVote(3);
    c.AddVote(3);
    c.AddVote(2);
    c.AddVote(1);
    Candidate candidate1("Hank Schrader");
    Candidate candidate2("Elvis Presley");
    Candidate candidate3("Bob Burnquist");
    candidate1.AddBallot(a);
    candidate2.AddBallot(b);
    candidate3.AddBallot(c);

    std::vector<Candidate> candidates = {candidate1,candidate2,candidate3};
    std::vector<Candidate> winners;
    int num_ballots = 3;
    ASSERT_TRUE(check_winners(candidates,winners,num_ballots));
    ASSERT_TRUE(winners.size() == 3);}

TEST(Voting, winners3) {
    Ballot a;
    Ballot b;
    Ballot c;
    Ballot d;
    a.AddVote(1);
    a.AddVote(2);
    a.AddVote(3);
    b.AddVote(2);
    b.AddVote(1);
    b.AddVote(3);
    c.AddVote(1);
    c.AddVote(2);
    c.AddVote(3);

    Candidate candidate1("Hank Schrader");
    Candidate candidate2("Elvis Presley");
    Candidate candidate3("Bob Burnquist");
    candidate1.AddBallot(a);
    candidate2.AddBallot(b);
    candidate1.AddBallot(c);


    std::vector<Candidate> candidates = {candidate1,candidate2,candidate3};
    std::vector<Candidate> winners;
    int num_ballots = 3;
    ASSERT_TRUE(check_winners(candidates,winners,num_ballots));
    ASSERT_TRUE(winners.size() == 1);}    
// -----
// remove_losers
// -----
    
TEST(Voting, losers1) {
    Candidate candidate1("Hank Schrader");
    std::vector<Candidate> candidates;
    candidates.push_back(candidate1);
    remove_losers(candidates);
    ASSERT_TRUE(!candidate1.IsActive());}    

TEST(Voting, losers2) {
    Ballot a;
    a.AddVote(1);
    a.AddVote(2);
    a.AddVote(3);
    Ballot b;
    b.AddVote(1);
    b.AddVote(2);
    b.AddVote(3);
    Ballot c;
    c.AddVote(2);
    c.AddVote(1);
    c.AddVote(3);
    std::vector<Candidate> candidates;
    Candidate candidate1("Hank Schrader");
    Candidate candidate2("Marie Schrader");
    Candidate candidate3("Walter White");
    candidates.push_back(candidate1);
    candidates.push_back(candidate2);
    candidates.push_back(candidate3);
    candidate1.AddBallot(a);
    candidate1.AddBallot(b);
    candidate2.AddBallot(c);
    ASSERT_TRUE(candidate1.IsActive());
    ASSERT_TRUE(!candidate3.IsActive());
    ASSERT_TRUE(candidate2.IsActive());}


TEST(Voting, losers3) {
    Ballot a;
    a.AddVote(1);
    a.AddVote(2);
    a.AddVote(3);
    a.AddVote(4);
    Ballot b;
    b.AddVote(2);
    b.AddVote(3);
    b.AddVote(4);
    b.AddVote(1);
    Candidate candidate1("Hank Schrader");
    Candidate candidate2("Walter White Jr.");
    Candidate candidate3("Marie Schrader");
    Candidate candidate4("Skyler White");
    candidate1.AddBallot(a);
    candidate2.AddBallot(b);
    std::vector<Candidate> candidates;
    candidates.push_back(candidate1);
    candidates.push_back(candidate2);
    candidates.push_back(candidate3);
    candidates.push_back(candidate4);
    ASSERT_TRUE(candidate1.IsActive());
    ASSERT_TRUE(candidate2.IsActive());
    ASSERT_TRUE(!candidate3.IsActive());
    ASSERT_TRUE(!candidate4.IsActive());}

// -----
// voting_eval_case
// -----
  
TEST(Voting, eval_case1) {
    Ballot a;
    a.AddVote(1);
    a.AddVote(2);
    Ballot b;
    b.AddVote(1);
    b.AddVote(2);
    Ballot c;
    c.AddVote(2);
    c.AddVote(1);
    
    Candidate candidate1("Niko Lazaris");
    candidate1.AddBallot(a);
    candidate1.AddBallot(b);
    Candidate candidate2("Alan Boozek");
    candidate2.AddBallot(c);
    
    std::vector<Candidate> candidates = {candidate1,candidate2};
    std::vector<Candidate> winners;
    int num_ballots = 3;

    voting_eval_case(candidates, winners, num_ballots);
    ASSERT_TRUE(winners.size() == 1);}    

TEST(Voting, eval_case2) {
    Ballot a;
    a.AddVote(1);
    a.AddVote(2);
    a.AddVote(3);
    Ballot b;
    b.AddVote(1);
    b.AddVote(2);
    b.AddVote(3);
    Ballot c;
    c.AddVote(2);
    c.AddVote(1);
    c.AddVote(3);
    Ballot d;
    d.AddVote(2);
    d.AddVote(1);
    d.AddVote(3);

    Candidate candidate1("Superman");
    candidate1.AddBallot(a);
    candidate1.AddBallot(b);
    Candidate candidate2("Aquaman");
    Candidate candidate3("Batman");
    candidate3.AddBallot(c);
    candidate3.AddBallot(d);
    
    std::vector<Candidate> candidates = {candidate1,candidate2,candidate3};
    std::vector<Candidate> winners;
    int num_ballots = 4;

    voting_eval_case(candidates, winners, num_ballots);
    ASSERT_TRUE(winners.size() == 2);}

TEST(Voting, eval_case3) {
    Ballot a;
    a.AddVote(1);
    Ballot b;
    b.AddVote(1);
    Ballot c;
    c.AddVote(1);
   
    Candidate candidate1("Superman");
    candidate1.AddBallot(a);
    candidate1.AddBallot(b);
    candidate1.AddBallot(c);

    
    std::vector<Candidate> candidates = {candidate1};
    std::vector<Candidate> winners;
    int num_ballots = 3;

    voting_eval_case(candidates, winners, num_ballots);
    ASSERT_TRUE(winners.size() == 1);} 

// -----
// voting_print
// -----

TEST(Voting, print1) {
    std::ostringstream w;
    Candidate candidate1("Jacky Kuo");
    Candidate candidate2("Niko Lazaris");
    Candidate candidate3("Alan Boozek");
    std::vector<Candidate> result = {candidate1,candidate2,candidate3};
    voting_print(w, result, true);
    ASSERT_TRUE(w.str() == "Jacky Kuo\nNiko Lazaris\nAlan Boozek\n");}


TEST(Voting, print2) {
    std::ostringstream w;
    Candidate candidate1("Aquaman");
    Candidate candidate2("The Flash");
    Candidate candidate3("Captain Marvel");
    Candidate candidate4("Superman");
    Candidate candidate5("Batman");
    Candidate candidate6("Robin");
    Candidate candidate7("The Joker");
    std::vector<Candidate> result = {candidate1,candidate2,candidate3,candidate4,candidate5,candidate6,candidate7};
    voting_print(w, result, true);
    ASSERT_TRUE(w.str() == "Aquaman\nThe Flash\nCaptain Marvel\nSuperman\nBatman\nRobin\nThe Joker\n");}

TEST(Voting, print3) {
    std::ostringstream w;
    Candidate candidate1("Jake");
    Candidate candidate2("Finn");
    std::vector<Candidate> result = {candidate1,candidate2};
    voting_print(w, result, false);
    ASSERT_TRUE(w.str() == "Jake\nFinn\n\n");}    
// -----
// voting_solve
// -----

TEST(Voting, solve1) {
    std::istringstream r("1\n\n3\nSuperman\nBatman\nAquaman\n1 2 3\n2 1 3\n1 2 3\n2 1 3\n3 1 2\n\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Superman\n");}

TEST(Voting, solve2) {
    std::istringstream r("2\n\n3\nSuperman\nBatman\nAquaman\n1 2 3\n2 1 3\n1 2 3\n2 1 3\n3 1 2\n\n2\nWalter White\nJesse Pinkman\n1 2\n2 1\n\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Superman\n\nWalter White\nJesse Pinkman\n");}    


