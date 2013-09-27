// --------------------------------
// projects/voting/TestVoting.c++
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

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>   // vector

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// -----
// names
// -----

TEST(Voting, voting_names_1 ) {
	std::istringstream r("1\nJohn Doe");
  std::vector< person > names;
	int p = voting_names(r, names);
	ASSERT_TRUE(p == 1);
	ASSERT_TRUE(names[0].name == "John Doe");
}

TEST(Voting, voting_names_2 ) {
	std::istringstream r("2\nJohn Doe\nJane Smith");
  std::vector< person > names;
	int p = voting_names(r, names);
	ASSERT_TRUE(p == 2);
	ASSERT_TRUE(names[0].name == "John Doe");
	ASSERT_TRUE(names[1].name == "Jane Smith");
}

TEST(Voting, voting_names_3 ) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow");
  std::vector< person > names;
	int p = voting_names(r, names);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(names[0].name == "John Doe");
	ASSERT_TRUE(names[1].name == "Jane Smith");
	ASSERT_TRUE(names[2].name == "Correy Morrow");
}

TEST(Voting, voting_count_1) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n1 2 3\n1 2 3\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 3);
	ASSERT_TRUE(names[0].ballots.size() == 3);
}

TEST(Voting, voting_count_2) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 0);
	ASSERT_TRUE(names[0].ballots.size() == 0);
	ASSERT_TRUE(names[1].ballots.size() == 0);
	ASSERT_TRUE(names[1].ballots.size() == 0);
}

TEST(Voting, voting_count_3) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n1 2 3\n1 2 3\n\n\n2 3 1\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 3);
	ASSERT_TRUE(names[0].ballots.size() == 3);
	ASSERT_TRUE(names[1].ballots.size() == 0);
}

TEST(Voting, voting_eval_1) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n1 2 3\n1 2 3\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 3);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(b);
	ASSERT_TRUE(max_idx == 0);
	ASSERT_TRUE(min == 0);
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, voting_eval_2) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n2 1 3\n3 1 2\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 3);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(b);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nCorrey Morrow\n");
}

TEST(Voting, voting_eval_3) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n2 1 3\n1 2 3\n2 1 3\n3 1 2\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 5);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(!b);
}

TEST(Voting, voting_fix_1) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nCorrey Morrow\n1 2 3\n2 1 3\n1 2 3\n2 1 3\n3 1 2\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 3);
	ASSERT_TRUE(tv == 5);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(!b);
	std::vector<int> mins;
	voting_fix(names, mins, min);
	ASSERT_TRUE(names[0].ballots.size() == 3);
}

TEST(Voting, voting_fix_2) {
	std::istringstream r("4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n2 1 3 4\n3 1 2 4\n4 1 2 3\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 4);
	ASSERT_TRUE(tv == 6);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(!b);
	std::vector<int> mins;
	voting_fix(names, mins, min);
	ASSERT_TRUE(min == 1);
	ASSERT_TRUE(names[0].ballots.size() == 4);
	ASSERT_TRUE(names[1].ballots.size() == 2);
}

TEST(Voting, voting_fix_3) {
	std::istringstream r("4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
	std::vector< person > names;
	int p = voting_names(r, names);
	int tv = 0;
	voting_count(r, names, p, tv);
	ASSERT_TRUE(p == 4);
	ASSERT_TRUE(tv == 6);
	int max_idx = 0;
	int min = 1000;
	std::ostringstream w;
	bool b = voting_eval(names, tv, max_idx, min, w);
	ASSERT_TRUE(!b);
	std::vector<int> mins;
	voting_fix(names, mins, min);
	ASSERT_TRUE(min == 1);
	ASSERT_TRUE(names[0].ballots.size() == 3);
	ASSERT_TRUE(names[1].ballots.size() == 3);
}

TEST(Voting, voting_solve_1) {
	std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
	std::ostringstream w;
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\n");
}

TEST(Voting, voting_solve_2) {
	std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n");
	std::ostringstream w;
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, voting_solve_3) {
	std::istringstream r("2\n\n4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n\n4\nJohn Doe\nJane Smith\nCorrey Morrow\nDan\n1 2 3 4\n2 1 3 4\n1 2 3 4\n");
	std::ostringstream w;
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "John Doe\nJohn Doe\n");
}
