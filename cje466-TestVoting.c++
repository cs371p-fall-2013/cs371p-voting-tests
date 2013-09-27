//Acceptance Test  
//Cristhian & Aaron
// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"


// -----
// solve
// -----

TEST(Voting, solve_1) {
    std::istringstream r("1\n\n1\nJose\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Jose\n");}

TEST(Voting, solve_2) {
    std::istringstream r("1\n\n1\nLazy Cat\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Lazy Cat\n");}

TEST(Voting, solve_3) {
    std::istringstream r("1\n\n3\nVegeta\nGohan\nTrunks\n1 2 3\n2 1 3\n2 3 1\n2 3 1\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Gohan\n");}

TEST(Voting, solve_4) {
    std::istringstream r("1\n\n1\nJose\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Jose\n");}

//-------
//findHighestScore
//
TEST(MyTest, FindHighestScore_1) {
    int a [4] = {0};
    a[0] = 10;
    int highest  = findHighestScore(a);
    ASSERT_TRUE(highest == 10);}

TEST(MyTest, FindHighestScore_2) {
    int a [1] = {1};
    a[0] = 100;
    int highest  = findHighestScore(a);
    ASSERT_TRUE(highest == 100);}

TEST(MyTest, FindHighestScore_3) {
    int a [4] = {0};
    a[0] = 999;
    a[1] = 1;
    a[2] = 10;
    a[3] = 110;
    int highest  = findHighestScore(a);
    ASSERT_TRUE(highest == 999);}

TEST(MyTest, FindHighestScore_4) {
    int a [10] = {0};
    a[0] = 1;
    int highest  = findHighestScore(a);
    ASSERT_TRUE(highest == 1);}

//-------
//findLowestScore
//
TEST(MyTest_1, findLowestScore_1) {
    int a [4] = {12};
    a[0] = 10;
    int highest  = findLowestScore(a);
    ASSERT_TRUE(highest == 10);}

TEST(MyTest_1, findLowestScore_2) {
    int a [1] = {100};
    a[0] = 1;
    int highest  = findLowestScore(a);
    ASSERT_TRUE(highest == 1);}

TEST(MyTest_1, findLowestScore_3) {
    int a [4] = {10};
    a[0] = 1;
    int highest  = findLowestScore(a);
    ASSERT_TRUE(highest == 1);}

TEST(MyTest_1, findLowestScore_4) {
    int a [10] = {20};
    a[0] = 2;
    int highest  = findLowestScore(a);
    ASSERT_TRUE(highest == 2);}

// Candidate Class
Candidate c ("testName");

// Testing constructor
TEST(Voting, candidate_constructor) {
    string test = "testName";
    ASSERT_TRUE(test == c.name);
}

// addBallot
TEST(Voting, candidate_addBallot) {
    deque<int> t = {1, 2, 3};
    c.addBallot(t);
    ASSERT_TRUE(c.ballots[0].ballot[0] == 1);
    ASSERT_TRUE(c.ballots.size() == 1);
}

TEST(Voting, candidate_addBallot2) {
    deque<int> t = {1, 2};
    c.addBallot(t);
    ASSERT_TRUE(c.ballots[1].ballot[0] == 1 && c.ballots[1].ballot[1] == 2);
}

TEST(Voting, candidate_addBallot3) {
    deque<int> t = {5};
    c.addBallot(t);
    ASSERT_TRUE(c.ballots[2].ballot[0] == 5);
    ASSERT_TRUE(c.ballots.size() == 3);
}


// getNumBallots()
TEST(Voting, candidate_getNumBallots1) {
    ASSERT_TRUE(c.getNumBallots() == 3);
}

TEST(Voting, candidate_getNumBallots2) {
    deque<int> t = {2, 3, 5};
    c.addBallot(t);
    ASSERT_TRUE(c.getNumBallots() == 4);
}

TEST(Voting, candidate_getNumBallots3) {
    Candidate b ("test2");
    ASSERT_TRUE(b.getNumBallots() == 0);
}

// Ballot Class
deque<int> testBallot = {2, 3, 4};
Ballot b (testBallot);
// popVote
TEST(Voting, ballot_popVote) {
    ASSERT_TRUE(b.popVote() == 2);
}

TEST(Voting, ballot_popVote2) {
    ASSERT_TRUE(b.popVote() == 3);
}

TEST(Voting, ballot_popVote3) {
    ASSERT_TRUE(b.popVote() == 4);
    ASSERT_TRUE(b.getSize() == 0);
}
// getSize
TEST(Voting, ballot_getSize) {
    Ballot c (testBallot);
    ASSERT_TRUE(c.getSize() == 3);
}

TEST(Voting, ballot_getSize2) {
    deque<int> testBallot2 = {0};
    Ballot c (testBallot2);
    ASSERT_TRUE(c.getSize() == 1);
}

TEST(Voting, ballot_getSize3) {
    deque<int> testBallot3 = {2, 3, 5, 2};
    Ballot c (testBallot3);
    ASSERT_TRUE(c.getSize() == 4);
}


