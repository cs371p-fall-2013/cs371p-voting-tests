// --------------------------------
// projects/Voting/TestVoting.c++
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
// voting_add_voter
// ----

TEST(Voting, voting_add_voter) {
	struct candidate cand[1];
	cand[0].voters[0] = -1;

	voting_add_voter(cand, 0, 1);

    ASSERT_TRUE(cand[0].voters[0] == 1);
}

TEST(Voting, voting_add_voter_2) {
	struct candidate cand[1];
	cand[0].voters[0] = 1;
	cand[0].voters[1] = -1;

	voting_add_voter(cand, 0, 1);

    ASSERT_TRUE(cand[0].voters[1] == 1);
}

TEST(Voting, voting_add_voter_3) {
	struct candidate cand[2];
	cand[1].voters[0] = 1;
	cand[1].voters[1] = -1;

	voting_add_voter(cand, 1, 2);

    ASSERT_TRUE(cand[1].voters[1] == 2);
}

// ----
// voting_move_voter
// ----

TEST(Voting, voting_move_voter) {
	struct candidate cand[2];
	cand[0].voters[0] = 1;
	cand[1].voters[0] = -1;

	voting_move_voter(cand, 0, 1, 1);

    ASSERT_TRUE(cand[0].voters[0] == -1);
    ASSERT_TRUE(cand[1].voters[0] == 1);
}

TEST(Voting, voting_move_voter_2) {
	struct candidate cand[2];
	cand[0].voters[0] = 1;
	cand[1].voters[0] = 2;
	cand[1].voters[1] = 3;
	cand[1].voters[2] = -1;

	voting_move_voter(cand, 0, 1, 1);

    ASSERT_TRUE(cand[0].voters[0] == -1);
    ASSERT_TRUE(cand[1].voters[2] == 1);
}

TEST(Voting, voting_move_voter_3) {
	struct candidate cand[3];
	cand[1].voters[0] = 4;
	cand[1].voters[1] = 1;
	cand[2].voters[0] = 2;
	cand[2].voters[1] = 3;
	cand[2].voters[2] = -1;

	voting_move_voter(cand, 1, 2, 1);

    ASSERT_TRUE(cand[1].voters[1] == -1);
    ASSERT_TRUE(cand[2].voters[2] == 1);
}

// ----
// voting_winner
// ----


TEST(Voting, voting_winner) {
	struct candidate cand[20];
	cand[0].in = true;
	cand[1].in = false;
	cand[2].in = false;
	cand[3].in = false;
	cand[4].in = false;
	cand[5].in = false;
	cand[6].in = false;
	cand[7].in = false;
	cand[8].in = false;
	cand[9].in = false;
	cand[10].in = false;
	cand[11].in = false;
	cand[12].in = false;
	cand[13].in = false;
	cand[14].in = false;
	cand[15].in = false;
	cand[16].in = false;
	cand[17].in = false;
	cand[18].in = false;
	cand[19].in = false;

	cand[0].numVotes = 1;
	cand[1].numVotes = 0;
	cand[2].numVotes = 0;
	cand[3].numVotes = 0;
	cand[4].numVotes = 0;
	cand[5].numVotes = 0;
	cand[6].numVotes = 0;
	cand[7].numVotes = 0;
	cand[7].numVotes = 0;
	cand[8].numVotes = 0;
	cand[9].numVotes = 0;
	cand[10].numVotes = 0;
	cand[11].numVotes = 0;
	cand[12].numVotes = 0;
	cand[13].numVotes = 0;
	cand[14].numVotes = 0;
	cand[15].numVotes = 0;
	cand[16].numVotes = 0;
	cand[17].numVotes = 0;
	cand[17].numVotes = 0;
	cand[18].numVotes = 0;
	cand[19].numVotes = 0;
	
	int result = voting_winner(cand, 1);

    ASSERT_TRUE(result == 0);
}

TEST(Voting, voting_winner_2) {
	struct candidate cand[20];
	cand[0].in = true;
	cand[1].in = true;
	cand[2].in = false;
	cand[3].in = false;
	cand[4].in = false;
	cand[5].in = false;
	cand[6].in = false;
	cand[7].in = false;
	cand[8].in = false;
	cand[9].in = false;
	cand[10].in = false;
	cand[11].in = false;
	cand[12].in = false;
	cand[13].in = false;
	cand[14].in = false;
	cand[15].in = false;
	cand[16].in = false;
	cand[17].in = false;
	cand[18].in = false;
	cand[19].in = false;

	cand[0].numVotes = 1;
	cand[1].numVotes = 0;
	cand[2].numVotes = 0;
	cand[3].numVotes = 0;
	cand[4].numVotes = 0;
	cand[5].numVotes = 0;
	cand[6].numVotes = 0;
	cand[7].numVotes = 0;
	cand[7].numVotes = 0;
	cand[8].numVotes = 0;
	cand[9].numVotes = 0;
	cand[10].numVotes = 0;
	cand[11].numVotes = 0;
	cand[12].numVotes = 0;
	cand[13].numVotes = 0;
	cand[14].numVotes = 0;
	cand[15].numVotes = 0;
	cand[16].numVotes = 0;
	cand[17].numVotes = 0;
	cand[17].numVotes = 0;
	cand[18].numVotes = 0;
	cand[19].numVotes = 0;
	
	int result = voting_winner(cand, 1);

    ASSERT_TRUE(result == 0);
}

TEST(Voting, voting_winner_3) {
	struct candidate cand[20];
	cand[0].in = true;
	cand[1].in = true;
	cand[2].in = false;
	cand[3].in = false;
	cand[4].in = false;
	cand[5].in = false;
	cand[6].in = false;
	cand[7].in = false;
	cand[8].in = false;
	cand[9].in = false;
	cand[10].in = false;
	cand[11].in = false;
	cand[12].in = false;
	cand[13].in = false;
	cand[14].in = false;
	cand[15].in = false;
	cand[16].in = false;
	cand[17].in = false;
	cand[18].in = false;
	cand[19].in = false;

	cand[0].numVotes = 1;
	cand[1].numVotes = 0;
	cand[2].numVotes = 0;
	cand[3].numVotes = 0;
	cand[4].numVotes = 0;
	cand[5].numVotes = 0;
	cand[6].numVotes = 0;
	cand[7].numVotes = 0;
	cand[7].numVotes = 0;
	cand[8].numVotes = 0;
	cand[9].numVotes = 0;
	cand[10].numVotes = 0;
	cand[11].numVotes = 0;
	cand[12].numVotes = 0;
	cand[13].numVotes = 0;
	cand[14].numVotes = 0;
	cand[15].numVotes = 0;
	cand[16].numVotes = 0;
	cand[17].numVotes = 0;
	cand[17].numVotes = 0;
	cand[18].numVotes = 0;
	cand[19].numVotes = 0;
	
	int result = voting_winner(cand, 1);

    ASSERT_TRUE(result == 0);
}

// ----
// read
// ----

TEST(Voting, read) {
    std::istringstream r("2\n\n");
    string result;
    voting_read(r, result);
    ASSERT_TRUE(result.compare("2") == 0);}

TEST(Voting, read_2) {
    std::istringstream r("1\nJohn Doe\n1 2 3\n3 2 1\n\n");
    string result;
    voting_read(r, result);
    ASSERT_TRUE(result.compare("1\nJohn Doe\n1 2 3\n3 2 1") == 0);}

TEST(Voting, read_3) {
    std::istringstream r("2\nJohn Doe\nJane Smith\n1 2 3\n3 2 1\n2 3 1\n\n");
    string result;
    voting_read(r, result);
    ASSERT_TRUE(result.compare("2\nJohn Doe\nJane Smith\n1 2 3\n3 2 1\n2 3 1") == 0);}

TEST(Voting, read_4) {
    std::istringstream r("2\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n3 2 1\n2 3 1\n1 3 2\n\n");
    string result;
    voting_read(r, result);
    ASSERT_TRUE(result.compare("2\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n3 2 1\n2 3 1\n1 3 2") == 0);}

// ------------
// voting_parse
// ------------

TEST(Voting, parse_1) {
    int numCand = 0;
    int numVoters = 0;
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n3 2 1\n");
    struct ballot voters[1000];
    struct candidate cand[20];
    voting_parse(numCand, numVoters, r, voters, cand);
    ASSERT_TRUE(numCand == 3);
    ASSERT_TRUE(numVoters == 2);
    ASSERT_TRUE(voters[0].index == 0);
    ASSERT_TRUE(cand[0].name.compare("John Doe") == 0);
    ASSERT_TRUE(cand[0].in);
    ASSERT_TRUE(cand[0].voters[0] == -1);
}
    
TEST(Voting, parse_2) {
    int numCand = 0;
    int numVoters = 0;
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    struct ballot voters[1000];
    struct candidate cand[20];
    voting_parse(numCand, numVoters, r, voters, cand);
    ASSERT_TRUE(numCand == 3);
    ASSERT_TRUE(numVoters == 5);
    ASSERT_TRUE(voters[0].index == 0);
    ASSERT_TRUE(cand[0].name.compare("John Doe") == 0);
    ASSERT_TRUE(cand[0].in);
    ASSERT_TRUE(cand[0].voters[0] == -1);
}

TEST(Voting, parse_3) {
    int numCand = 0;
    int numVoters = 0;
    std::istringstream r("2\nJohn Doe\nJane Smith\n1 2 3\n3 2 1\n2 3 1\n1 3 2\n");
    struct ballot voters[1000];
    struct candidate cand[20];
    voting_parse(numCand, numVoters, r, voters, cand);
    ASSERT_TRUE(numCand == 2);
    ASSERT_TRUE(numVoters == 4);
    ASSERT_TRUE(voters[0].index == 0);
    ASSERT_TRUE(cand[0].name.compare("John Doe") == 0);
    ASSERT_TRUE(cand[0].in);
    ASSERT_TRUE(cand[0].voters[0] == -1);
}

// ------------
// voting_tie
// ------------

TEST(Voting, tie_1) {
    struct candidate cand[20];
    cand[0].name = "John Doe";
    cand[0].numVotes = 10;
    cand[0].in = true;
    cand[1].name = "Jane Smith";
    cand[1].numVotes = 10;
    cand[1].in = true; 
    cand[2].in = false;
    cand[3].in = false;
    cand[4].in = false;
    cand[5].in = false;
    cand[6].in = false;
    cand[7].in = false;
    cand[8].in = false;
    cand[9].in = false;
    cand[10].in = false;
    cand[11].in = false;
    cand[12].in = false;
    cand[13].in = false;
    cand[14].in = false;
    cand[15].in = false;
    cand[16].in = false;
    cand[17].in = false;
    cand[18].in = false;
    cand[19].in = false;
    ASSERT_TRUE(voting_tie(cand));
}

TEST(Voting, tie_2) {
    struct candidate cand[20];
    cand[0].name = "John Doe";
    cand[0].numVotes = 14;
    cand[0].in = true;
    cand[1].name = "Jane Smith";
    cand[1].numVotes = 10;
    cand[1].in = true; 
    cand[2].name = "Hey Oh";
    cand[2].numVotes = 17;
    cand[2].in = true;
    cand[3].in = false;
    cand[4].in = false;
    cand[5].in = false;
    cand[6].in = false;
    cand[7].in = false;
    cand[8].in = false;
    cand[9].in = false;
    cand[10].in = false;
    cand[11].in = false;
    cand[12].in = false;
    cand[13].in = false;
    cand[14].in = false;
    cand[15].in = false;
    cand[16].in = false;
    cand[17].in = false;
    cand[18].in = false;
    cand[19].in = false;
    ASSERT_TRUE(!voting_tie(cand));
}

TEST(Voting, tie_3) {
    struct candidate cand[20];
    cand[0].name = "John Doe";
    cand[0].numVotes = 10;
    cand[0].in = true;
    cand[1].name = "Jane Smith";
    cand[1].numVotes = 10;
    cand[1].in = true; 
    cand[2].name = "Hey Oh";
    cand[2].numVotes = 10;
    cand[2].in = true;
    cand[3].in = false;
    cand[4].in = false;
    cand[5].in = false;
    cand[6].in = false;
    cand[7].in = false;
    cand[8].in = false;
    cand[9].in = false;
    cand[10].in = false;
    cand[11].in = false;
    cand[12].in = false;
    cand[13].in = false;
    cand[14].in = false;
    cand[15].in = false;
    cand[16].in = false;
    cand[17].in = false;
    cand[18].in = false;
    cand[19].in = false;
    ASSERT_TRUE(voting_tie(cand));
}
// ----
// eval
// ----

TEST(Voting, eval_1) {
	string result;
	voting_eval("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2", result);
    ASSERT_TRUE(result.compare("John Doe\n") == 0);
}

TEST(Voting, eval_2) {
	string result;
	voting_eval("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2", result);
    ASSERT_TRUE(result.compare("John Doe\n") == 0);
}

TEST(Voting, eval_3) {
	string result;
	voting_eval("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 1 2\n3 1 2", result);
    ASSERT_TRUE(result.compare("John Doe\nJane Smith\nSirhan Sirhan\n") == 0);
}


// -----
// print
// -----

// -----
// solve
// -----


TEST(Voting, solve_1) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("John Doe\n") == 0);}
    
TEST(Voting, solve_2) {
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("John Doe\n\nJohn Doe\n") == 0);}
  
TEST(Voting, solve_3) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 1 2\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("John Doe\nJane Smith\nSirhan Sirhan\n") == 0);}
	
