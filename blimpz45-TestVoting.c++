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
/*
TEST(Voting, read) {
    std::istringstream r("John Smith\nJane Doe\nJorge Luis\n");
    
		int result;
    result = getCandidates(3, r);
		
    ASSERT_TRUE(result == 3);
  }
	TEST(Voting, read2) {
    std::istringstream r("John Smith\nJane Doe\nJorge Luis\nJack Shepard");
    
		int result;
    result = getCandidates(4, r);
		
    ASSERT_TRUE(result == 4);
  }
	TEST(Voting, read3) {
    std::istringstream r("John Smith\nJane Doe\nJorge Luis\nJack Shepard\nRobert Williams");
    
		int result;
    result = getCandidates(5, r);
		
    ASSERT_TRUE(result == 5);
  }
	*/
	
TEST(Voting, solve) {
    std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;
		
    election(r,w);
		
ASSERT_TRUE(w.str() == "John Smith\n");  
}
TEST(Voting, solve2) {
    std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n2 1 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;
		
    election(r,w);
		
ASSERT_TRUE(w.str() == "Jane Doe\n");  
}
TEST(Voting, solve3) {
    std::istringstream r("2\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;
		
    election(r,w);
		
ASSERT_TRUE(w.str() == "John Smith\nJane Doe");  
}

TEST(Voting, ballots) {
	std::istringstream r("1 2 3\n3 2 1\n 2 1 3\n 2 3 1\n");
	int num_ballots;
	int num_candidates = 3;
	int voters = 0;
	
	voters = getBallots(num_ballots, voters, num_candidates);

	ASSERT_TRUE(voters == 4);
}
TEST(Voting, ballots2) {
	std::istringstream r("1 2 3\n3 2 1\n 2 1 3\n 2 3 1\n3 1 2");
	int num_ballots;
	int num_candidates = 3;
	int voters = 0;
	
	voters = getBallots(num_ballots, voters, num_candidates);

	ASSERT_TRUE(voters == 5);
}
TEST(Voting, ballots3) {
	std::istringstream r("1 2 3\n3 2 1\n 2 1 3\n");
	int num_ballots;
	int num_candidates = 3;
	int voters = 0;
	
	voters = getBallots(num_ballots, voters, num_candidates);

	ASSERT_TRUE(voters == 3);
}