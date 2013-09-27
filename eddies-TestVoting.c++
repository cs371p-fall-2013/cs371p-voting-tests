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
// voting_num_cases
// ----

TEST(Voting, voting_num_cases_0) {
    std::istringstream r("1\n\n10\n\n");
    int i;
    const bool b = voting_num_cases(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
}

TEST(Voting, voting_num_cases_empty) {
    std::istringstream r("");
    int i;
    const bool b = voting_num_cases(r, i);
    ASSERT_TRUE(b == false);
}

TEST(Voting, voting_num_cases_only_num) {
    std::istringstream r("5");
    int i;
    const bool b = voting_num_cases(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5);
}

// -----
// voting_solve
// -----

TEST(Voting, voting_solve_normal) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, voting_solve_tie) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n3 2 1\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

TEST(Voting, voting_solve_recount) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

// ----
// Election runElection, addCandidate, addBallot,
// distribute, addBallotTo, winnerPresent, tiePresent,
// identifyLosers, isLoser, findMaxVote
// ----

TEST(Voting, runElection_0) {
    std::ostringstream w;

    int num_cands = 3;

    std::string name0 = "John Doe";
    std::string name1 = "Jane Smith";
    std::string name2 = "Sirhan Sirhan";

    std::queue<int> q0;
    int q01 = 1;
    int q02 = 2;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    std::queue<int> q1;
    int q11 = 1;
    int q12 = 2;
    int q13 = 3;
    q1.push(q11);
    q1.push(q12);
    q1.push(q13);

    std::queue<int> q2;
    int q21 = 2;
    int q22 = 1;
    int q23 = 3;
    q2.push(q21);
    q2.push(q22);
    q2.push(q23);

    std::queue<int> q3;
    int q31 = 2;
    int q32 = 1;
    int q33 = 3;
    q3.push(q31);
    q3.push(q32);
    q3.push(q33);

    std::queue<int> q4;
    int q41 = 3;
    int q42 = 1;
    int q43 = 2;
    q4.push(q41);
    q4.push(q42);
    q4.push(q43);

    std::queue<int> q5;
    int q51 = 3;
    int q52 = 2;
    int q53 = 1;
    q5.push(q51);
    q5.push(q52);
    q5.push(q53);

    Election e (num_cands);

    Candidate c0;
    c0.setName(name0);
    Candidate c1;
    c1.setName(name1);
    Candidate c2;
    c2.setName(name2);

    Ballot b0 (q0);
    Ballot b1 (q1);
    Ballot b2 (q2);
    Ballot b3 (q3);
    Ballot b4 (q4);
    Ballot b5 (q5);

    e.addCandidate(c0);
    e.addCandidate(c1);
    e.addCandidate(c2);

    e.addBallot(b0);
    e.addBallot(b1);
    e.addBallot(b2);
    e.addBallot(b3);
    e.addBallot(b4);
    e.addBallot(b5);

    e.runElection(w);

    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan");
}

TEST(Voting, runElection_1) {
    std::ostringstream w;

    int num_cands = 3;

    std::string name0 = "John Doe";
    std::string name1 = "Jane Smith";
    std::string name2 = "Sirhan Sirhan";

    std::queue<int> q0;
    int q01 = 1;
    int q02 = 2;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    std::queue<int> q1;
    int q11 = 1;
    int q12 = 2;
    int q13 = 3;
    q1.push(q11);
    q1.push(q12);
    q1.push(q13);

    std::queue<int> q2;
    int q21 = 1;
    int q22 = 2;
    int q23 = 3;
    q2.push(q21);
    q2.push(q22);
    q2.push(q23);

    std::queue<int> q3;
    int q31 = 1;
    int q32 = 2;
    int q33 = 3;
    q3.push(q31);
    q3.push(q32);
    q3.push(q33);

    std::queue<int> q4;
    int q41 = 3;
    int q42 = 1;
    int q43 = 2;
    q4.push(q41);
    q4.push(q42);
    q4.push(q43);

    Election e (num_cands);

    Candidate c0;
    c0.setName(name0);
    Candidate c1;
    c1.setName(name1);
    Candidate c2;
    c2.setName(name2);

    Ballot b0 (q0);
    Ballot b1 (q1);
    Ballot b2 (q2);
    Ballot b3 (q3);
    Ballot b4 (q4);

    e.addCandidate(c0);
    e.addCandidate(c1);
    e.addCandidate(c2);

    e.addBallot(b0);
    e.addBallot(b1);
    e.addBallot(b2);
    e.addBallot(b3);
    e.addBallot(b4);

    e.runElection(w);

    ASSERT_TRUE(w.str() == "John Doe");
}

TEST(Voting, runElection_2) {
    std::ostringstream w;

    int num_cands = 3;

    std::string name0 = "John Doe";
    std::string name1 = "Jane Smith";
    std::string name2 = "Sirhan Sirhan";

    std::queue<int> q0;
    int q01 = 1;
    int q02 = 2;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    std::queue<int> q1;
    int q11 = 2;
    int q12 = 1;
    int q13 = 3;
    q1.push(q11);
    q1.push(q12);
    q1.push(q13);

    std::queue<int> q2;
    int q21 = 2;
    int q22 = 3;
    int q23 = 1;
    q2.push(q21);
    q2.push(q22);
    q2.push(q23);

    std::queue<int> q3;
    int q31 = 1;
    int q32 = 2;
    int q33 = 3;
    q3.push(q31);
    q3.push(q32);
    q3.push(q33);

    std::queue<int> q4;
    int q41 = 3;
    int q42 = 1;
    int q43 = 2;
    q4.push(q41);
    q4.push(q42);
    q4.push(q43);

    Election e (num_cands);

    Candidate c0;
    c0.setName(name0);
    Candidate c1;
    c1.setName(name1);
    Candidate c2;
    c2.setName(name2);

    Ballot b0 (q0);
    Ballot b1 (q1);
    Ballot b2 (q2);
    Ballot b3 (q3);
    Ballot b4 (q4);

    e.addCandidate(c0);
    e.addCandidate(c1);
    e.addCandidate(c2);

    e.addBallot(b0);
    e.addBallot(b1);
    e.addBallot(b2);
    e.addBallot(b3);
    e.addBallot(b4);

    e.runElection(w);

    ASSERT_TRUE(w.str() == "John Doe");
}

// ----
// Ballot getTop
// ----

TEST(Voting, ballot_getTop_0) {
    std::queue<int> q0;
    int q01 = 1;
    int q02 = 2;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    Ballot b0 (q0);

    ASSERT_TRUE(b0.getTop() == 1);
}

TEST(Voting, ballot_getTop_1) {
    std::queue<int> q0;
    int q01 = 2;
    int q02 = 1;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    Ballot b0 (q0);

    ASSERT_TRUE(b0.getTop() == 2);
}

TEST(Voting, ballot_getTop_2) {
    std::queue<int> q0;
    int q01 = 3;
    int q02 = 2;
    int q03 = 3;
    q0.push(q01);
    q0.push(q02);
    q0.push(q03);

    Ballot b0 (q0);

    ASSERT_TRUE(b0.getTop() == 3);
}

// ----
// Candidate setName and getName
// ----

TEST(Voting, Candidate_setName_getName_0) {
    std::string name = "John Doe";
    Candidate c0;
    c0.setName(name);
    ASSERT_TRUE(c0.getName() == "John Doe");
}

TEST(Voting, Candidate_setName_getName_2) {
    std::string name = "Jane Smith";
    Candidate c0;
    c0.setName(name);
    ASSERT_TRUE(c0.getName() == "Jane Smith");
}

TEST(Voting, Candidate_setName_getName_3) {
    std::string name = "Sirhan Sirhan";
    Candidate c0;
    c0.setName(name);
    ASSERT_TRUE(c0.getName() == "Sirhan Sirhan");
}
