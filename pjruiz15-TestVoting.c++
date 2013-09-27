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
    std::istringstream r("1\nArthur King of Camelot\n1\n1\n1\n1\n1\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    w << election;
    assert(w.str() == "1\nArthur King of Camelot\n1\n1\n1\n1\n1\n");
}

TEST(Voting, read_2) {
    std::istringstream r("3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    w << election;
    assert(w.str() == "3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
}

TEST(Voting, read_3) {
    std::istringstream r("20\none\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    w << election;
    assert(w.str() == "20\none\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n");
}

// -----
// print
// -----

TEST(Voting, print_1) {
    std::istringstream r("1\nArthur King of Camelot\n1\n1\n1\n1\n1\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    voting_print(w, election);
    assert(w.str() == "Arthur King of Camelot\n");
}

TEST(Voting, print_2) {
    std::istringstream r("3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    voting_print(w, election);
    assert(w.str() == "John Smith\nJane Smith\nSirhan Sirhan\n");
}

TEST(Voting, print_3) {
    std::istringstream r("20\none\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n");
    Election election;
    voting_read(r, election);
    std::ostringstream w;
    voting_print(w, election);
    assert(w.str() == "one\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n");
}

// ----
// eval
// ----
TEST(Voting, eval_1) {
    std::istringstream r("1\nArthur King of Camelot\n1\n1\n1\n1\n1\n");
    Election election;
    voting_read(r, election);
    voting_eval(election);
    std::ostringstream w;
    election.ShowResults(w);
    assert(w.str() == "Arthur King of Camelot\n");
}

TEST(Voting, eval_2) {
    std::istringstream r("3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    Election election;
    voting_read(r, election);
    voting_eval(election);
    std::ostringstream w;
    election.ShowResults(w);
    assert(w.str() == "John Smith\n");
}

TEST(Voting, eval_3) {
    std::istringstream r("20\none\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n20 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 1");
    Election election;
    voting_read(r, election);
    voting_eval(election);
    std::ostringstream w;
    election.ShowResults(w);
    assert(w.str() == "twenty\n");
}

// -----
// solve
// -----

TEST(Voting, solve_1) {
    std::istringstream r("1\n\n1\nArthur King of Camelot\n1\n1\n1\n1\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    assert(w.str() == "Arthur King of Camelot\n");
}

TEST(Voting, solve_2) {
    std::istringstream r("1\n\n3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    assert(w.str() == "John Smith\n");
}

TEST(Voting, solve_3) {
    std::istringstream r("1\n\n20\none\ntwo\nthree\nfour\ndot\ndot\nblah\nblah\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\nyada\ntwenty\n20 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 1");
    std::ostringstream w;
    voting_solve(r, w);
    assert(w.str() == "twenty\n");
}

TEST(Voting, solve_4) {
    std::istringstream r("2\n\n3\nJohn Smith\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nJ J\nW W\n1 2\n2 1\n");
    std::ostringstream w;
    voting_solve(r, w);
    assert(w.str() == "John Smith\n\nJ J\nW W\n");
}
