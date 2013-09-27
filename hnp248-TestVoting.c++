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

// using namespace std;
// -----------
// TestVoting
// -----------
TEST(Voting, solve_1_candidate)
{
    std::istringstream r("1\n\n1\na\n1\n");
    std::ostringstream w;
    voting_solve(r, w, 1);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, solve_2_candidate)
{
    std::istringstream r("1\n\n2\na\nb\n1\n2\n1\n2\n");
    std::ostringstream w;
    voting_solve(r, w, 1);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, solve_3_candidate)
{
    std::istringstream r("1\n\n3\na\nb\nc\n1\n2\n3\n1\n3\n2\n2\n1\n3\n");
    std::ostringstream w;
    voting_solve(r, w, 1);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, get_winner1)
{
    std::istringstream r("1\n\n1\na\n1\n");
    std::ostringstream w;
    voting_get_winner(r, w, 0, -1, 1);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, get_winner2)
{
    std::istringstream r("1\n\n2\na\nb\n1\n2\n1\n2\n");
    std::ostringstream w;
    voting_get_winner(r, w, 0, -1, 2);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, get_winner3)
{
    std::istringstream r("1\n\n3\na\nb\nc\n1\n2\n3\n1\n3\n2\n2\n1\n3\n");
    std::ostringstream w;
    voting_get_winner(r, w, 0, -1, 3);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Voting, get_name1)
{
    std::istringstream r("1\n\n1\na\n1\n");
    std::ostringstream w;
    voting_get_candidates_names(r, w, 1, 1);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, get_name2)
{
    std::istringstream r("1\n\n2\na\nb\n1\n2\n1\n2\n");
    std::ostringstream w;
    voting_get_candidates_names(r, w, 2, 1);
    ASSERT_TRUE(w.str() == "a\nb\n");
}

TEST(Voting, get_name3)
{
    std::istringstream r("1\n\n3\na\nb\nc\n1\n2\n3\n1\n3\n2\n2\n1\n3\n");
    std::ostringstream w;
    voting_get_candidates_names(r, w, 3, 1);
    ASSERT_TRUE(w.str() == "a\nb\nc\n");
}

TEST(Voting, get_voter1)
{
    std::istringstream r("1\n\n1\na\n1\n");
    std::ostringstream w;
    voting_get_voters(r, w, 1, 1);
    ASSERT_TRUE(w.str() == "1");
}

TEST(Voting, get_voter2)
{
    std::istringstream r("1\n\n2\na\nb\n1\n2\n1\n2\n");
    std::ostringstream w;
    voting_get_voters(r, w, 2, 2);
    ASSERT_TRUE(w.str() == "2");
}

TEST(Voting, get_voter3)
{
    std::istringstream r("1\n\n3\na\nb\nc\n1\n2\n3\n1\n3\n2\n2\n1\n3\n");
    std::ostringstream w;
    voting_get_voters(r, w, 3, 3);
    ASSERT_TRUE(w.str() == "3");
}