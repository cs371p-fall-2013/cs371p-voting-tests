// -----------------------------------
// Project by: Mitch Stephan (mjs4373)
//             Chris Chung (cc37684)
// cs371p-voting/TestVoting.c++
// -----------------------------------

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

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
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


// ----------
// TestVoting
// ----------

// ------------
// voting_clean
// ------------
TEST(Voting, clean_1) 
{
    names[1] = "hello";
    counts[1] = 35;
    autoWin = 100;
    autoWinCandidate = 1;
    finished = true;
    voting_clean();
    ASSERT_TRUE(names[1] == "");
    ASSERT_TRUE(counts[0] == 0);
    ASSERT_TRUE(autoWin == 1000);
    ASSERT_TRUE(autoWinCandidate == -1);
    ASSERT_TRUE(finished == false);
}

TEST(Voting, clean_2) 
{
    names[1] = "hi";
    counts[1] = 3;
    autoWin = 10;
    autoWinCandidate = 13;
    finished = true;
    voting_clean();
    ASSERT_TRUE(names[1] == "");
    ASSERT_TRUE(counts[0] == 0);
    ASSERT_TRUE(autoWin == 1000);
    ASSERT_TRUE(autoWinCandidate == -1);
    ASSERT_TRUE(finished == false);
}

TEST(Voting, clean_3) 
{
    names[1] = "yo";
    counts[1] = 5;
    autoWin = 0;
    autoWinCandidate = 0;
    finished = true;
    voting_clean();
    ASSERT_TRUE(names[1] == "");
    ASSERT_TRUE(counts[0] == 0);
    ASSERT_TRUE(autoWin == 1000);
    ASSERT_TRUE(autoWinCandidate == -1);
    ASSERT_TRUE(finished == false);
}

// ------------
// voting_print
// ------------
TEST(Voting, print_1)
{
    voting_clean();
    names[1] = "a";
    ostringstream w;
    voting_print(w, 1);
    ASSERT_TRUE(w.str() == "a\n");
    ASSERT_TRUE(finished = true);
}

TEST(Voting, print_2)
{
    voting_clean();
    names[2] = "b";
    ostringstream w;
    voting_print(w, 2);
    ASSERT_TRUE(w.str() == "b\n");
    ASSERT_TRUE(finished = true);
}

TEST(Voting, print_3)
{
    voting_clean();
    names[1] = "hi";
    ostringstream w;
    voting_print(w, 1);
    ASSERT_TRUE(w.str() == "hi\n");
    ASSERT_TRUE(finished = true);
}

// ----------------
// voting_isAutoWin
// ----------------
TEST(Voting, isAutoWin_1)
{
    voting_clean();
    names[1] = "a";
    autoWinCandidate = 1;
    ostringstream w;
    const bool result = voting_isAutoWin(w);
    ASSERT_TRUE(w.str() == "a\n");
    ASSERT_TRUE(result == true);
}

TEST(Voting, isAutoWin_2)
{
    voting_clean();
    names[2] = "b";
    autoWinCandidate = 2;
    ostringstream w;
    const bool result = voting_isAutoWin(w);
    ASSERT_TRUE(w.str() == "b\n");
    ASSERT_TRUE(result == true);
}

TEST(Voting, isAutoWin_3)
{
    voting_clean();
    ostringstream w;
    const bool result = voting_isAutoWin(w);
    ASSERT_TRUE(result == false);
}

// -------------------
// voting_printWinners
// -------------------
TEST(Voting, printWinners_1)
{
    voting_clean();
    numCandidates = 1;
    names[1] = "a";
    counts[1] = 2;
    ostringstream w;
    voting_printWinners(w, 1);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, printWinners_2)
{
    voting_clean();
    numCandidates = 2;
    names[1] = "a";
    names[2] = "b";
    counts[1] = 2;
    counts[2] = 1;
    ostringstream w;
    voting_printWinners(w, 1);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, printWinners_3)
{
    voting_clean();
    numCandidates = 2;
    names[1] = "a";
    names[2] = "b";
    counts[1] = 2;
    counts[2] = 2;
    ostringstream w;
    voting_printWinners(w, 1);
    ASSERT_TRUE(w.str() == "a\nb\n");
}

// -------------------
// voting_assignBallot
// -------------------
TEST(Voting, assignBallot_1)
{
    voting_clean();
    ASSERT_TRUE(counts[1] == 0);
    voting_assignBallot("1 2 3", -1);
    ASSERT_TRUE(counts[1] == 1);
}

TEST(Voting, assignBallot_2)
{
    voting_clean();
    counts[1] = 2;
    counts[2] = 3;
    voting_assignBallot("1 2 3", 2);
    ASSERT_TRUE(counts[2] == 4);
}

TEST(Voting, assignBallot_3)
{
    voting_clean();
    ASSERT_TRUE(counts[2] == 0);
    voting_assignBallot("2 1 3", -1);
    ASSERT_TRUE(counts[2] == 1);
}

// ---------------
// voting_readCase
// ---------------
TEST(Voting, readCase_1)
{
    istringstream r("2\na\nb\n1 2\n");
    ostringstream w;
    voting_readCase(r, w);
    ASSERT_TRUE(numCandidates == 2);
    ASSERT_TRUE(counts[1] == 1);
    ASSERT_TRUE(autoWin == 1);
    ASSERT_TRUE(autoWinCandidate == 1);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, readCase_2)
{
    istringstream r("2\na\nb\n1 2\n1 2\n");
    ostringstream w;
    voting_readCase(r, w);
    ASSERT_TRUE(numCandidates == 2);
    ASSERT_TRUE(counts[1] == 2);
    ASSERT_TRUE(autoWin == 2);
    ASSERT_TRUE(autoWinCandidate == 1);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, readCase_3)
{
    istringstream r("2\na\nb\n1 2\n2 1\n");
    ostringstream w;
    voting_readCase(r, w);
    ASSERT_TRUE(numCandidates == 2);
    ASSERT_TRUE(counts[1] == 1);
    ASSERT_TRUE(counts[2] == 1);
    ASSERT_TRUE(autoWin == 2);
}

// -----------
// voting_eval
// -----------
TEST(Voting, eval_1)
{
    voting_clean();
    numCandidates = 3;
    autoWin = 3;
    ballots[3][0] = "3 1 2";
    counts[1] = 2;
    counts[2] = 1;
    counts[3] = 1;
    ostringstream w;
    voting_eval(w);
    ASSERT_TRUE(counts[1] == 3);
    ASSERT_TRUE(counts[2] == 1);
    ASSERT_TRUE(finished == true);
}

TEST(Voting, eval_2)
{
    voting_clean();
    numCandidates = 2;
    counts[1] = 1;
    counts[2] = 1;
    ostringstream w;
    voting_eval(w);
    ASSERT_TRUE(counts[1] == 1);
    ASSERT_TRUE(counts[2] == 1);
    ASSERT_TRUE(finished == true);
}

TEST(Voting, eval_3)
{
    voting_clean();
    numCandidates = 4;
    ballots[3][0] = "3 1 2 3";
    ballots[4][0] = "4 2 3 4";
    counts[1] = 2;
    counts[2] = 2;
    counts[3] = 1;
    counts[4] = 1;
    ostringstream w;
    voting_eval(w);
    ASSERT_TRUE(counts[1] == 3);
    ASSERT_TRUE(counts[2] == 3);
    ASSERT_TRUE(counts[3] == 0);
    ASSERT_TRUE(counts[4] == 0);
    ASSERT_TRUE(finished == true);
}

// ------------
// voting_solve
// ------------
TEST(Voting, solve_1)
{
    istringstream r("1\n\n1\na\n1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, solve_2)
{
    istringstream r("1\n\n2\na\nb\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\nb\n");
}

TEST(Voting, solve_3)
{
    istringstream r("2\n\n1\na\n1\n\n2\na\nb\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\n\na\nb\n");
}