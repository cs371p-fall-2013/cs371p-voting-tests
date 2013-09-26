/******************************************************************************
 * Program: Project 2: Voting
 * Students: Merrill Davis, Kyeong Park
 * UT EID: davismc2, ksp499 
 * CS ID: davismc, ksp499
 * Class: CS 371p
 * Fall 2013
 *
 * Purpose: solution for the Australian Voting problem (10142) found at 
 *  http://uva.onlinejudge.org
 *  
 *****************************************************************************/

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <list>		// list

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ------------
// voting_read_ballot
// ------------

TEST(Voting, read_ballot_1) {
    std::istringstream r("5 2 3 4 1\n10 9 8 7 6\n");
    ballot_t temp({5, 2, 3, 4, 1});
   	ballot_t temp_list;
    const bool b = voting_read_ballot (r, temp_list);
	ASSERT_TRUE(b == true);
    ASSERT_TRUE(temp_list == temp);
}

TEST(Voting, read_ballot_2) {
    std::istringstream r("\n\n");
    ballot_t temp;
   	ballot_t temp_list;
    const bool b = voting_read_ballot (r, temp_list);
	ASSERT_TRUE(b == false);
    ASSERT_TRUE(temp_list == temp);
}

TEST(Voting, read_ballot_3) {
    std::istringstream r("5\n");
    ballot_t temp({5});
   	ballot_t temp_list;
    const bool b = voting_read_ballot (r, temp_list);
	ASSERT_TRUE(b == true);
    ASSERT_TRUE(temp_list == temp);
}


// ------------
// voting_read_names
// ------------

TEST(Voting, read_names_1) {
    std::istringstream r("kyeong park\n");
    names_t temp({"kyeong park"});

   	names_t temp_list;
    const bool b = voting_read_names (r, temp_list, 1);
	ASSERT_TRUE(b == true);

    ASSERT_TRUE(temp_list == temp);
}

TEST(Voting, read_names_2) {
    std::istringstream r("kyeong park\nMerrill Davis");
    names_t temp({"kyeong park", "Merrill Davis"});

   	names_t temp_list;
    const bool b = voting_read_names (r, temp_list, 2);
	ASSERT_TRUE(b == true);

    ASSERT_TRUE(temp_list == temp);
}

TEST(Voting, read_names_3) {
    std::istringstream r("\n");
   //std::string temp;
    names_t temp({""});

   	names_t temp_list;
    const bool b = voting_read_names (r, temp_list, 1);
	ASSERT_TRUE(b == true);

    ASSERT_TRUE(temp_list == temp);
}


// -------------
// voting_print
// -------------

TEST(Voting, print_1) {
	std::ostringstream w;
	names_t temp({"Kyeong Park"});
	voting_print (w, temp);
    ASSERT_TRUE(w.str() == "Kyeong Park\n");
}

TEST(Voting, print_2) {
	std::ostringstream w;
	names_t temp({""});
	voting_print (w, temp);
    ASSERT_TRUE(w.str() == "\n");
}

TEST(Voting, print_3) {
	std::ostringstream w;
	names_t temp({"Kyeong Park", "Merrill Davis", "David John"});
	voting_print (w, temp);
    ASSERT_TRUE(w.str() == "Kyeong Park\nMerrill Davis\nDavid John\n");
}

// ------------
// voting_eval
// ------------

TEST(Voting, read_eval_1) {
	std::istringstream r("1\nKyeong Park\n1\n1\n1\n\n");

	names_t temp({"Kyeong Park"});

	int num_candidates;
	names_t name_list;					// List of candidates
	names_t winners;					// List of winning candidates
	std::list<ballot_t> all_ballots[MAX_CANDIDATES];	// Holds all ballots
  for (int i = 0; i < MAX_CANDIDATES; ++i) {
      all_ballots[i] = std::list<ballot_t>();
  }
	int tally[MAX_CANDIDATES] = {0};     // Vote total for each candidate, indexed by candidate number, doesn't use index 0
  int num_ballots;

  num_ballots = voting_read(r, tally, name_list, all_ballots, num_candidates);
  winners = voting_eval(r, tally, name_list, all_ballots, num_candidates, num_ballots);

    ASSERT_TRUE(winners == temp);
}

TEST(Voting, read_eval_2) {
	std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n3 1 2\n\n");

	names_t temp({"John Doe","Jane Smith","Sirhan Sirhan"});

	int num_candidates;
	names_t name_list;					// List of candidates
	names_t winners;					// List of winning candidates
	std::list<ballot_t> all_ballots[MAX_CANDIDATES];	// Holds all ballots
  for (int i = 0; i < MAX_CANDIDATES; ++i) {
      all_ballots[i] = std::list<ballot_t>();
  }
	int tally[MAX_CANDIDATES] = {0};     // Vote total for each candidate, indexed by candidate number, doesn't use index 0
  int num_ballots;

  num_ballots = voting_read(r, tally, name_list, all_ballots, num_candidates);
  winners = voting_eval(r, tally, name_list, all_ballots, num_candidates, num_ballots);

    ASSERT_TRUE(winners == temp);
}

TEST(Voting, read_eval_3) {
	std::istringstream r("2\nKyeong Park\nMerrill Davis\n1 2\n2 1\n2 1\n");

	names_t temp({"Merrill Davis"});

	int num_candidates;
	names_t name_list;					// List of candidates
	names_t winners;					// List of winning candidates
	std::list<ballot_t> all_ballots[MAX_CANDIDATES];	// Holds all ballots
  for (int i = 0; i < MAX_CANDIDATES; ++i) {
      all_ballots[i] = std::list<ballot_t>();
   }
	int tally[MAX_CANDIDATES] = {0};			// Vote total for each candidate, indexed by candidate number, doesn't use index 0
	int num_ballots;

	num_ballots = voting_read(r, tally, name_list, all_ballots, num_candidates);
	winners = voting_eval(r, tally, name_list, all_ballots, num_candidates, num_ballots);

    ASSERT_TRUE(winners == temp);
}


// ------------
// highest_vote_count
// ------------

TEST(Voting, highest_vote_count_1) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 5;
	tally[2] = 10;
	tally[3] = 2;	

    ASSERT_TRUE(highest_vote_count(tally, 3) == 10);
}

TEST(Voting, highest_vote_count_2) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

    ASSERT_TRUE(highest_vote_count(tally, 1) == 0);
}

// Make sure it reads the last value
TEST(Voting, highest_vote_count_3) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 41;
	tally[3] = 42;	

    ASSERT_TRUE(highest_vote_count(tally, 3) == 42);
}

// ------------
// lowest_vote_count
// ------------
// Should ignore any -1, they represent candidates that aren't in the running 
TEST(Voting, lowest_vote_count_1) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 5;
	tally[2] = 10;
	tally[3] = 2;	

    ASSERT_TRUE(lowest_vote_count(tally, 3) == 2);
}

TEST(Voting, lowest_vote_count_2) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally [1] = 20;

    ASSERT_TRUE(lowest_vote_count(tally, 1) == 20);
}

// Make sure it reads the last value
TEST(Voting, lowest_vote_count_3) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 42;
	tally[2] = 50;
	tally[3] = 30;	

    ASSERT_TRUE(lowest_vote_count(tally, 3) == 30);
}

// Make sure it ignores -1
TEST(Voting, lowest_vote_count_4) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 10;
	tally[2] = -1;
	tally[3] = 13;	
	tally[4] = 0;

    ASSERT_TRUE(lowest_vote_count(tally, 4) == 0);
}


// ------------
// all_tied
// ------------

TEST(Voting, all_tied_1) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 30;
	tally[2] = 50;
	tally[3] = 42;	

    ASSERT_TRUE(all_tied(tally, 30, 3) == false);
}

// includes an eliminated candidate
TEST(Voting, all_tied_2) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 30;
	tally[2] = -1;
	tally[3] = 30;	

    ASSERT_TRUE(all_tied(tally, 30, 3) == true);
}

// should be checking the last number
TEST(Voting, all_tied_3) {
	int tally[MAX_CANDIDATES];
	for (int i = 0; i < MAX_CANDIDATES; ++i)
		tally[i] = 0;

	tally[1] = 30;
	tally[2] = -1;
	tally[3] = 25;	

    ASSERT_TRUE(all_tied(tally, 30, 3) == false);
}


// ------------
// retally
// ------------

TEST(Voting, retally_1) {
	int tally[MAX_CANDIDATES] = {0};
	std::list<ballot_t> all_ballots[MAX_CANDIDATES];
	all_ballots[3].push_back(ballot_t({3, 2, 1}));
	all_ballots[1].push_back(ballot_t({1, 2, 3}));
	all_ballots[1].push_back(ballot_t({1, 3, 2}));
	tally[1] = 4;	// This should get removed by retally

	retally(tally, all_ballots, 3);
	ASSERT_TRUE(tally[0] == 0);	// Shouldn't be used, but was initialized at least
	ASSERT_TRUE(tally[1] == 2); // Would be 6 if retally didn't wipe values
	ASSERT_TRUE(tally[2] == 0);
	ASSERT_TRUE(tally[3] == 1);
}

TEST(Voting, retally_2) {
  int tally[MAX_CANDIDATES] = {0};
  std::list<ballot_t> all_ballots[MAX_CANDIDATES];
  all_ballots[3].push_back(ballot_t({3, 2, 1}));
  all_ballots[1].push_back(ballot_t({1, 2, 3}));
  all_ballots[1].push_back(ballot_t({1, 3, 2}));
  tally[1] = -1;  // Should now ignore the size of bucket 1

  retally(tally, all_ballots, 3);
  ASSERT_TRUE(tally[0] == 0); // Shouldn't be used, but was initialized at least
  ASSERT_TRUE(tally[1] == -1);
  ASSERT_TRUE(tally[2] == 0);
  ASSERT_TRUE(tally[3] == 1);
}

TEST(Voting, retally_3) {
  int tally[MAX_CANDIDATES] = {0};
  std::list<ballot_t> all_ballots[MAX_CANDIDATES];
  all_ballots[2].push_back(ballot_t({2, 3, 1}));
  all_ballots[2].push_back(ballot_t({2, 1, 3}));
  all_ballots[2].push_back(ballot_t({2, 3, 1}));

  retally(tally, all_ballots, 3);
  ASSERT_TRUE(tally[0] == 0); // Shouldn't be used, but was initialized at least
  ASSERT_TRUE(tally[1] == 0);
  ASSERT_TRUE(tally[2] == 3);
  ASSERT_TRUE(tally[3] == 0);
}


// ------------
// voting_solve
// ------------

TEST(Voting, solve_1) {
	std::istringstream r("1\n\n1\nKyeong Park\n1\n1\n1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n");
}

TEST(Voting, solve_2) {
	std::istringstream r("2\n\n1\nKyeong Park\n1\n1\n1\n\n2\nKyeong Park\nMerrill Davis\n1 2\n2 1\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n\nMerrill Davis\n");
}

TEST(Voting, solve_3) {
	std::istringstream r("3\n\n1\nKyeong Park\n1\n1\n1\n\n2\nKyeong Park\nMerrill Davis\n1 2\n2 1\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n\nKyeong Park\nMerrill Davis\n\nJohn\n");
}

TEST(Voting, solve_4) {
	std::istringstream r("2\n\n3\nJohn\nTed\nWill\n3 1 2\n2 1 3\n1 2 3\n3 2 1\n2 3 1\n1 3 2\n\n2\nMack\nKnife\n1 2\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "John\nTed\nWill\n\nMack\nKnife\n");
}

// Tests clear majority and situation where 7/2 = 3.5 so 4 votes should be enough to win
// Also, never ends the last line with an \n
TEST(Voting, solve_5) {
	std::istringstream r("2\n\n3\nFrank\nPete\nTodd\n2 1 3\n1 2 3\n1 3 2\n1 1 2\n\n2\nJim\nCarrey\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1\n2 1");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Frank\n\nCarrey\n");
}
