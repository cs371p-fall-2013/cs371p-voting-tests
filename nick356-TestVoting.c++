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

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <queue>

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// ----------
// TestVoting
// ----------

// --------
// uva_read
// --------

TEST(Voting,read) {
	istringstream r("2\nJane Doe\nJohn Smith\n1 2\n2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 2);
	ASSERT_TRUE(ballots == 2);
}

TEST(Voting,read2) {
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 3);
	ASSERT_TRUE(ballots == 5);
}

TEST(Voting,read3) {
	istringstream r("5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 5);
	ASSERT_TRUE(ballots == 10);
}

TEST(Voting,read4) {
	istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 3 1 4\n3 4 2 1\n 3 4 2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 4);
	ASSERT_TRUE(ballots == 7);
}

// ---------
// uva_solve
// ---------

 TEST(Voting,solve) {
 	istringstream r("1\n\n2\nJane Doe\nJohn Smith\n1 2\n2 1\n");
 	ostringstream w;
 	uva_solve(r,w);
	ASSERT_TRUE(w.str() == "Jane Doe\nJohn Smith\n");
 }

TEST(Voting,solve2) {
	istringstream r("1\n\n5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	ostringstream w;
	uva_solve(r,w);
	ASSERT_TRUE(w.str() == "sally doo colly\n");
}

TEST(Voting,solve3) {
	istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
	uva_solve(r,w);
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting,solve4) {
	istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 3 1 4\n3 4 2 1\n 3 4 2 1\n");
	ostringstream w;
	uva_solve(r,w);
	ASSERT_TRUE(w.str() == "A\n");
}

// ---------
// mthenhalf
// ---------

TEST(Voting,half) {
	istringstream r("2\nJane Doe\nJohn Smith\n1 2\n2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 2);
	ASSERT_TRUE(ballots == 2);
	int result = mthenhalf(j,ballots);
	ASSERT_TRUE(result == -1);
}

TEST(Voting,half2) {
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 3);
	ASSERT_TRUE(ballots == 5);
	int result = mthenhalf(j,ballots);
	ASSERT_TRUE(result == -1);
}

TEST(Voting,half3) {
	istringstream r("5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 5);
	ASSERT_TRUE(ballots == 10);
	int result = mthenhalf(j,ballots);
	//cout << "result is " << result << endl;
	ASSERT_TRUE(result == -1);
}

TEST(Voting,half4) {
	istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 3 1 4\n3 4 2 1\n 3 4 2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 4);
	ASSERT_TRUE(ballots == 7);
	int result = mthenhalf(j,ballots);
	//cout << "result is " << result << endl;
	ASSERT_TRUE(result == -1);
}


// // ------
// // istied
// // ------

TEST(Voting,tied) {
	istringstream r("2\nJane Doe\nJohn Smith\n1 2\n2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 2);
	ASSERT_TRUE(ballots == 2);
	bool result = istied(j,ballots);
	ASSERT_TRUE(result == true);
}

TEST(Voting,tied2) {
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 3);
	ASSERT_TRUE(ballots == 5);
	bool result = istied(j,ballots);
	ASSERT_TRUE(result == false);
}

TEST(Voting,tied3) {
	istringstream r("5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 5);
	ASSERT_TRUE(ballots == 10);
	bool result = istied(j,ballots);
	ASSERT_TRUE(result == false);
}

TEST(Voting,tied4) {
	istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 3 1 4\n3 4 2 1\n 3 4 2 1\n");
	ostringstream w;
	int j;
	int ballots;
	uva_read(r,w,ballots,j);
	ASSERT_TRUE(j == 4);
	ASSERT_TRUE(ballots == 7);
	bool result = istied(j,ballots);
	ASSERT_TRUE(result == false);
}
