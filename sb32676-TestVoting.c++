// --------------------------------
// projects/collatz/TestVoting.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------


/*
	name: Seung Youp Baek
	eid: sb32676
	cdid: sb32676
	email: bsy6766@gmail.com
	course: CS371p 10am
*/

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

// -----------
// TestVoting
// -----------


// -----
// read_candidate
// -----
TEST(Voting, read_candidate1){
	std::istringstream r("2\na\nb\n");
	Candidate c_arr[MAX_CANDIDATES];
	int total_candidates = 0;
	voting_read_candidates(r, total_candidates, c_arr);
	ASSERT_TRUE(total_candidates == 2);
	ASSERT_TRUE(strcmp(c_arr[0].name, "a") == 0); 
	ASSERT_TRUE(strcmp(c_arr[1].name, "b") == 0); 
}

TEST(Voting, read_candidate2){
	std::istringstream r("5\nabc\ndef\nghi\njkl\nmno");
	Candidate c_arr[MAX_CANDIDATES];
	int total_candidates = 0;
	voting_read_candidates(r, total_candidates, c_arr);
	ASSERT_TRUE(total_candidates == 5);
	ASSERT_TRUE(strcmp(c_arr[0].name, "abc") == 0); 
	ASSERT_TRUE(strcmp(c_arr[1].name, "def") == 0); 
	ASSERT_TRUE(strcmp(c_arr[2].name, "ghi") == 0); 
	ASSERT_TRUE(strcmp(c_arr[3].name, "jkl") == 0); 
	ASSERT_TRUE(strcmp(c_arr[4].name, "mno") == 0); 
}

TEST(Voting, read_candidate3){
	std::istringstream r("1\nI'm_the_winner");
	Candidate c_arr[MAX_CANDIDATES];
	int total_candidates = 0;
	voting_read_candidates(r, total_candidates, c_arr);
	ASSERT_TRUE(total_candidates == 1);
	ASSERT_TRUE(strcmp(c_arr[0].name, "I'm_the_winner") == 0); 
}

// -----
// read_ballots
// -----
TEST(Voting, read_ballots1){
	std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int total_ballots = 0;
	int bal[MAX_VOTERS][MAX_CANDIDATES];
	int col[MAX_VOTERS];
	voting_read_ballots(r, total_ballots, 3, bal, col);
	ASSERT_TRUE(total_ballots == 5);
	ASSERT_TRUE(bal[0][0] == 0);
	ASSERT_TRUE(bal[0][1] == 1);
	ASSERT_TRUE(bal[0][2] == 2);
	ASSERT_TRUE(bal[1][0] == 1);
	ASSERT_TRUE(bal[1][1] == 0);
	ASSERT_TRUE(bal[1][2] == 2);
	ASSERT_TRUE(bal[2][0] == 1);
	ASSERT_TRUE(bal[2][1] == 2);
	ASSERT_TRUE(bal[2][2] == 0);
	ASSERT_TRUE(bal[3][0] == 0);
	ASSERT_TRUE(bal[3][1] == 1);
	ASSERT_TRUE(bal[3][2] == 2);
	ASSERT_TRUE(bal[4][0] == 2);
	ASSERT_TRUE(bal[4][1] == 0);
	ASSERT_TRUE(bal[4][2] == 1);
}


TEST(Voting, read_ballots2){
        std::istringstream r("1 2 3 4 5 6 7 8 9 10");
        int total_ballots = 0;
        int bal[MAX_VOTERS][MAX_CANDIDATES];
        int col[MAX_VOTERS];
        voting_read_ballots(r, total_ballots, 10, bal, col);
        ASSERT_TRUE(total_ballots == 1);
        ASSERT_TRUE(bal[0][0] == 0);
        ASSERT_TRUE(bal[0][1] == 1);
        ASSERT_TRUE(bal[0][2] == 2);
        ASSERT_TRUE(bal[0][3] == 3);
        ASSERT_TRUE(bal[0][4] == 4);
        ASSERT_TRUE(bal[0][5] == 5);
        ASSERT_TRUE(bal[0][6] == 6);
        ASSERT_TRUE(bal[0][7] == 7);
        ASSERT_TRUE(bal[0][8] == 8);
	ASSERT_TRUE(bal[0][9] == 9);
}

TEST(Voting, read_ballots3_count_check){
	std::istringstream r("1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
        int total_ballots = 0;
        int bal[MAX_VOTERS][MAX_CANDIDATES];
        int col[MAX_VOTERS];
        voting_read_ballots(r, total_ballots, 1, bal, col);
        ASSERT_TRUE(total_ballots == 20);
}
// -----
// eval
// -----

TEST(Voting, eval1){
	std::istringstream r("3\na\nb\nc\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int max = 0;
	int min = MAX_VOTERS;
	int t_ballots = 0;
	int t_candidates = 0;
	int winner_id = -1;
	int bal[MAX_VOTERS][MAX_CANDIDATES];
	int col[MAX_VOTERS];
	std::vector<std::string> print_name;
	Candidate c_arr[MAX_CANDIDATES];
	
	voting_read_candidates(r, t_candidates, c_arr);
	voting_read_ballots(r, t_ballots, t_candidates, bal, col);
	
	voting_eval(max, min, t_ballots, t_candidates, winner_id, bal, col, print_name, c_arr);
	
	ASSERT_TRUE(t_candidates == 3);
	ASSERT_TRUE(t_ballots == 5);
	ASSERT_TRUE(max == 3);
	ASSERT_TRUE(winner_id == 0);
	ASSERT_TRUE(print_name[winner_id].compare("a") == 0);
}

TEST(Voting, eval2){
        std::istringstream r("2\na\nb\n1 2\n2 1\n1 2\n2 1\n1 2");
        int max = 0;
        int min = MAX_VOTERS;
        int t_ballots = 0;
        int t_candidates = 0;
        int winner_id = -1;
        int bal[MAX_VOTERS][MAX_CANDIDATES];
        int col[MAX_VOTERS];
        std::vector<std::string> print_name;
        Candidate c_arr[MAX_CANDIDATES];

        voting_read_candidates(r, t_candidates, c_arr);
        voting_read_ballots(r, t_ballots, t_candidates, bal, col);

        voting_eval(max, min, t_ballots, t_candidates, winner_id, bal, col, print_name, c_arr);

        ASSERT_TRUE(t_candidates == 2);
        ASSERT_TRUE(t_ballots == 5);
        ASSERT_TRUE(max == 3);
        ASSERT_TRUE(winner_id == 0);
        ASSERT_TRUE(print_name[winner_id].compare("a") == 0);
}


// -----
// solve
// -----



TEST(Voting, solve1){
	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	std::ostringstream w;
	voting_solve(r, w);
	ASSERT_TRUE(w.str() ==	"John Doe\n");
}

TEST(Voting, solve2){
	std::istringstream r("5\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        ASSERT_TRUE(w.str() ==  "John Doe\n\nJohn Doe\n\nJohn Doe\n\nJohn Doe\n\nJohn Doe\n");
}

TEST(Voting, solve3){
	std::istringstream r("1\n\n2\na\nb\n1 2\n2 1\n1 2\n2 1\n1 2");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "a\n");
}

TEST(Voting, solve4){
        std::istringstream r("1\n\n7\ns\nepoidnfrxfgvvyhcuamylwdhtdopjmhijbtzsuzrvcjv\nvptvxlabdqrhaagkgrxwyuczvkiscyz\ngiuqwilt\nqvhtkwdzilffntxnfbudqiynrvsrwpehlxd\nbsuzziicvrannvffdycge\njayqywvrnihdvavxtfxtrqldgjabcqjxhpgutybkkpeu\n4 3 7 1 6 2 5\n2 6 4 5 7 3 1\n5 1 2 6 3 7 4\n6 4 1 2 5 3 7\n3 2 4 7 6 1 5\n3 2 5 6 7 1 4\n2 5 6 3 7 4 1\n7 2 1 3 6 5 4\n2 5 6 7 1 4 3");
        std::ostringstream w;
        voting_solve(r,w);
        ASSERT_TRUE(w.str() == "epoidnfrxfgvvyhcuamylwdhtdopjmhijbtzsuzrvcjv\n");
}


// -----
// print
// -----

TEST(Voting, print1){
	std::vector<std::string> v{"John Doe", "Sirhan Sirhan", "Random name"};
	std::ostringstream w;
	voting_print(w, v);
	ASSERT_TRUE(w.str() == "John Doe\nSirhan Sirhan\nRandom name\n");
}

TEST(Voting, print2){
	std::vector<std::string> v{"the name must be less than 80 characters"};
        std::ostringstream w;
        voting_print(w, v);
        ASSERT_TRUE(w.str() == "the name must be less than 80 characters\n");
}

TEST(Voting, print3){
	std::vector<std::string> v{"a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np"};
        std::ostringstream w;
        voting_print(w, v);
        ASSERT_TRUE(w.str() == "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\n");
}

