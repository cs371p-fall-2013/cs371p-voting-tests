// -----------------------------
// Jacob Kovar
// jrk2593
// CS371P - Glenn Downing - 10am
// -----------------------------

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

// ----------
// TestVoting
// ----------

// -----------------
// read_cases_number
// -----------------

TEST(Voting, read_cases_1)
{
	std::istringstream r("1\n\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(cases == 1);
}

TEST(Voting, read_cases_2)
{
	std::istringstream r("1\n3\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
	ASSERT_TRUE(cases == 1);
}


TEST(Voting, read_cases_3)
{
	std::istringstream r("a\n\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
}

TEST(Voting, read_cases_4)
{
	std::istringstream r("-1\n\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
	ASSERT_TRUE(cases == -1);
}

TEST(Voting, read_cases_5)
{
	std::istringstream r("1\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
	ASSERT_TRUE(cases == 1);
}

TEST(Voting, read_cases_6)
{
	std::istringstream r("1a\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
	ASSERT_TRUE(cases == 1);
}

TEST(Voting, read_cases_7)
{
	std::istringstream r("\n\n");
	int cases;
	const bool b = read_cases_number(r, cases);
	ASSERT_TRUE(b == false);
}

// ---------------------
// read_candidate_number
// ---------------------

TEST(Voting, read_cand_num_1)
{
	std::istringstream r("1\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b > 0 && b <= 20);
}

TEST(Voting, read_cand_num_2)
{
	std::istringstream r("a\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

TEST(Voting, read_cand_num_3)
{
	std::istringstream r("21\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

TEST(Voting, read_cand_num_4)
{
	std::istringstream r("-1\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

TEST(Voting, read_cand_num_5)
{
	std::istringstream r("1a\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

TEST(Voting, read_cand_num_6)
{
	std::istringstream r("\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

TEST(Voting, read_cand_num_7)
{
	std::istringstream r("\n");
	const int b = read_candidate_number(r);
	ASSERT_TRUE(b == -1);
}

// ---------------
// read_candidates
// ---------------

TEST(Voting, read_candidates_1)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
	std::ostringstream w;
	int num = 3;
	read_candidates(r,num);
	voting_print(w,num,0);//prints out all the candidates in the array
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

TEST(Voting, read_candidates_2)
{
	std::istringstream r("John Doe\n");
	std::ostringstream w;
	int num = 1;
	read_candidates(r,num);
	voting_print(w,num,0);//prints out all the candidates in the array
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, read_candidates_3)
{
	std::istringstream r("I\nLove\nBacon!");
	std::ostringstream w;
	int num = 3;
	read_candidates(r,num);
	voting_print(w,num,0);//prints out all the candidates in the array
	ASSERT_TRUE(w.str() == "I\nLove\nBacon!\n");
}


// ------------
// record_votes
// ------------
 
TEST(Voting, record_votes_1)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1 3\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(voters == 5);
	ASSERT_TRUE(highest_num_votes == 3);
	ASSERT_TRUE(highest_votes_cand_index == 1);
	ASSERT_TRUE(lowest_num_votes == 1);
}

TEST(Voting, record_votes_2)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 2 3\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

TEST(Voting, record_votes_3)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1 3 4\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(voters == 5);
	ASSERT_TRUE(highest_num_votes == 3);
	ASSERT_TRUE(highest_votes_cand_index == 1);
	ASSERT_TRUE(lowest_num_votes == 1);
}

TEST(Voting, record_votes_4)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1 4\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

TEST(Voting, record_votes_5)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1 21\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

TEST(Voting, record_votes_6)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1 -1\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

TEST(Voting, record_votes_7)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 1\n2 3 1\n2 3 1\n1 2 3\n3 2 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

TEST(Voting, record_votes_8)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 3 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(voters == 1);
	ASSERT_TRUE(highest_num_votes == 1);
	ASSERT_TRUE(highest_votes_cand_index == 1);
	ASSERT_TRUE(lowest_num_votes == 1);
}

TEST(Voting, record_votes_9)
{
	std::istringstream c("1\n2\n3");
	read_candidates(c, 3);

	std::istringstream r("2 a 1");
	int num = 3;
	int voters = 0;
	int highest_num_votes = 0;
	int highest_votes_cand_index = -1;
	int lowest_num_votes = 1001;

	const bool b = record_votes(r, num, voters, highest_num_votes, highest_votes_cand_index, lowest_num_votes);
	ASSERT_TRUE(b == false);
}

// ---------------
// voting_election
// ---------------

TEST(Voting, election_1)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num = 3;
	int ret = voting_election(r,num);
	ASSERT_TRUE(ret == 3);
}

TEST(Voting, election_2)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n\n");
	int num = 3;
	int ret = voting_election(r,num);
	ASSERT_TRUE(ret == 0);
}

TEST(Voting, election_3)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 1 3\n2 3 1\n2 3 1\n3 1 2");
	int num = 3;
	int ret = voting_election(r,num);
	ASSERT_TRUE(ret == 4);
}

TEST(Voting, election_4)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");
	int num = 3;
	int ret = voting_election(r,num);
	ASSERT_TRUE(ret == 2);
}

TEST(Voting, election_5)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 3 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");
	int num = 3;
	int ret = voting_election(r,num);
	ASSERT_TRUE(ret == -1);
}

// ------------
// voting print
// ------------

TEST(Voting, print_1)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	std::ostringstream w;
	int num = 3;
	int ret = voting_election(r,num);
	voting_print(w,num,ret);
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, print_2)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n\n");
	std::ostringstream w;
	int num = 3;
	int ret = voting_election(r,num);
	voting_print(w,num,ret);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

TEST(Voting, print_3)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 1 3\n2 3 1\n2 3 1\n3 1 2");
	std::ostringstream w;
	int num = 3;
	int ret = voting_election(r,num);
	voting_print(w,num,ret);
	ASSERT_TRUE(w.str() == "Jane Smith\n");
}

TEST(Voting, print_4)
{
	std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");
	std::ostringstream w;
	int num = 3;
	int ret = voting_election(r,num);
	voting_print(w,num,ret);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

// ----------
// voting_run
// ----------

TEST(Voting, run_1)
{
	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	std::ostringstream w;
	voting_run(r, w);
	ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, run_2)
{
	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\n");
	std::ostringstream w;
	voting_run(r, w);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

TEST(Voting, run_3)
{
	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 1 3\n2 3 1\n2 3 1\n3 1 2");
	std::ostringstream w;
	voting_run(r, w);
	ASSERT_TRUE(w.str() == "Jane Smith\n");
}

TEST(Voting, run_4)
{
	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");
	std::ostringstream w;
	voting_run(r, w);
	ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}
