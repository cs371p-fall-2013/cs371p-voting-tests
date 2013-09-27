// --------------------------
// CS371P - Assignment #2 - Voting
// Benjamin Pang
// bp7936 - bpang@utexas.edu
// --------------------------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// --------------
// get_num_rounds
// --------------

TEST(Voting, get_num_rounds_normal)
{
	std::istringstream r("50\n\n");
	int num_rounds = get_num_rounds(r);
	ASSERT_TRUE(num_rounds == 50);
}

TEST(Voting, get_num_rounds_large)
{
	std::istringstream r("999999\n\n");
	int num_rounds = get_num_rounds(r);
	ASSERT_TRUE(num_rounds == 999999);
}

TEST(Voting, get_num_rounds_min)
{
	std::istringstream r("1\n\n");
	int num_rounds = get_num_rounds(r);
	ASSERT_TRUE(num_rounds == 1);
}

// ------------------
// get_num_candidates
// ------------------

TEST(Voting, get_num_candidates_normal)
{
	std::istringstream r("10\n");
	int num_candidates = get_num_candidates(r);
	ASSERT_TRUE(num_candidates == 10);
}

TEST(Voting, get_num_candidates_max)
{
	std::istringstream r("20\n");
	int num_candidates = get_num_candidates(r);
	ASSERT_TRUE(num_candidates == 20);
}

TEST(Voting, get_num_candidates_min)
{
		std::istringstream r("0\n");
	int num_candidates = get_num_candidates(r);
	ASSERT_TRUE(num_candidates == 0);
}

// -------------
// get_max_votes
// -------------

TEST(Voting, get_max_votes_min)
{
	Candidate candidates[20];
	for(int i = 0; i < 20; i++)
		candidates[i].num_votes = 0;
	int max_votes = get_max_votes(candidates, 20);
	ASSERT_TRUE(max_votes == 0);
}

TEST(Voting, get_max_votes_large)
{
	Candidate candidates[5];
	for(int i = 0; i < 5; i++)
		candidates[i].num_votes = i * 50;
	int max_votes = get_max_votes(candidates, 5);
	ASSERT_TRUE(max_votes == 200);
}

TEST(Voting, get_max_votes_normal)
{
	Candidate candidates[8];
	for(int i = 0; i < 8; i++)
		candidates[i].num_votes = i;
	int max_votes = get_max_votes(candidates, 8);
	ASSERT_TRUE(max_votes == 7);
}

// -------------
// get_min_votes
// -------------

TEST(Voting, get_min_votes_large)
{
	Candidate candidates[20];
	for(int i = 0; i < 20; i++)
		candidates[i].num_votes = 999;
	int min_votes = get_min_votes(candidates, 20);
	ASSERT_TRUE(min_votes == 999);
}

TEST(Voting, get_min_votes_small)
{
	Candidate candidates[5];
	for(int i = 0; i < 5; i++)
		candidates[i].num_votes = (i + 1) * 200;
	int min_votes = get_min_votes(candidates, 5);
	ASSERT_TRUE(min_votes == 200);
}

TEST(Voting, get_min_votes_normal)
{
	Candidate candidates[8];
	for(int i = 0; i < 8; i++)
		candidates[i].num_votes = i;
	int min_votes = get_min_votes(candidates, 8);
	ASSERT_TRUE(min_votes == 1);
}

// ----------------------
// get_candidate_by_votes
// ----------------------

TEST(Voting, get_candidate_by_votes_small)
{
	Candidate candidates[8];
	for(int i = 0; i < 8; i++)
		candidates[i].num_votes = i;
	int candidate = get_candidate_by_votes(candidates, 8, 2);
	ASSERT_TRUE(candidate == 2);
}

TEST(Voting, get_candidate_by_votes_normal)
{
	Candidate candidates[8];
	for(int i = 0; i < 5; i++)
		candidates[i].num_votes = i * 50;
	int candidate = get_candidate_by_votes(candidates, 5, 200);
	ASSERT_TRUE(candidate == 4);
}

TEST(Voting, get_candidate_by_votes_large)
{
	Candidate candidates[8];
	for(int i = 0; i < 8; i++)
		candidates[i].num_votes = i;
	int candidate = get_candidate_by_votes(candidates, 8, 1000000);
	ASSERT_TRUE(candidate == -1);
}

// ---------------
// elim_candidates
// ---------------

TEST(Voting, elim_candidates_normal)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i;
	elim_candidates(candidates, 10, 5);
	ASSERT_TRUE(candidates[5].is_out);
}

TEST(Voting, elim_candidates_multiple)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i % 5;
	elim_candidates(candidates, 10, 0);
	ASSERT_TRUE(candidates[0].is_out);
	ASSERT_TRUE(candidates[5].is_out);
}

TEST(Voting, elim_candidates_multiple_2)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i;
	elim_candidates(candidates, 10, 0);
	elim_candidates(candidates, 10, 4);
	elim_candidates(candidates, 10, 3);
	ASSERT_TRUE(candidates[0].is_out);
	ASSERT_TRUE(candidates[4].is_out);
	ASSERT_TRUE(candidates[3].is_out);
}

// -------------
// shift_ballots
// -------------

TEST(Voting, shift_ballots_1)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i % 5;
	elim_candidates(candidates, 10, 0);
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 10; j++)
			ballots[i][j] = j;
	shift_ballots(candidates, ballots, 3);
	ASSERT_TRUE(ballots[0][0] == 0);
}

TEST(Voting, shift_ballots_2)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i;
	elim_candidates(candidates, 10, 1);
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 10; j++)
			ballots[i][j] = j;
	shift_ballots(candidates, ballots, 3);
	ASSERT_TRUE(ballots[0][0] == 0);
}

TEST(Voting, shift_ballots_3)
{
	Candidate candidates[10];
	for(int i = 0; i < 10; i++)
		candidates[i].num_votes = i;
	elim_candidates(candidates, 10, 0);
	elim_candidates(candidates, 10, 1);
	elim_candidates(candidates, 10, 2);
	elim_candidates(candidates, 10, 3);
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 10; j++)
			ballots[i][j] = j;
	shift_ballots(candidates, ballots, 3);
	ASSERT_TRUE(ballots[0][0] == 0);
}

// ---------------
// init_cand_votes
// ---------------

TEST(Voting, init_cand_votes_1)
{
	Candidate candidates[5];
	init_cand_votes(candidates, 5);
	ASSERT_TRUE(candidates[4].num_votes == 0);
}

TEST(Voting, init_cand_votes_2)
{
	Candidate candidates[200];
	init_cand_votes(candidates, 200);
	ASSERT_TRUE(candidates[199].num_votes == 0);
}

TEST(Voting, init_cand_votes_3)
{
	Candidate candidates[100];
	init_cand_votes(candidates, 100);
	ASSERT_TRUE(candidates[50].num_votes == 0);
}

// -----------
// voting_read
// -----------

TEST(Voting, voting_read_1)
{
	std::istringstream r("James Albright\nChaele Fletcher\nNorman Magnusson\n1 2 3\n3 2 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(candidates[0].name == "James Albright");
	ASSERT_TRUE(candidates[1].name == "Chaele Fletcher");
	ASSERT_TRUE(candidates[2].name == "Norman Magnusson");
	ASSERT_TRUE(ballots[0][0] == 1);
	ASSERT_TRUE(ballots[0][2] == 3);
	ASSERT_TRUE(ballots[2][1] == 2);
}

TEST(Voting, voting_read_2)
{
	std::istringstream r("xqW1245t\nFSmcqhwoeQE\nCWQcwqcwq\n3 2 1\n2 3 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(candidates[0].name == "xqW1245t");
	ASSERT_TRUE(candidates[1].name == "FSmcqhwoeQE");
	ASSERT_TRUE(candidates[2].name == "CWQcwqcwq");
	ASSERT_TRUE(ballots[0][0] == 3);
	ASSERT_TRUE(ballots[0][2] == 1);
	ASSERT_TRUE(ballots[2][1] == 2);
}

TEST(Voting, voting_read_3)
{
	std::istringstream r("a\nb\nc\n3 2 1\n2 3 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(candidates[0].name == "a");
	ASSERT_TRUE(candidates[1].name == "b");
	ASSERT_TRUE(candidates[2].name == "c");
}

// -----------
// voting_eval
// -----------

TEST(Voting, voting_eval_1)
{
	std::ostringstream w;
	std::istringstream r("James Albright\nChaele Fletcher\nNorman Magnusson\n1 2 3\n3 2 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	voting_eval(w, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(w.str() == "James Albright\n");
}

TEST(Voting, voting_eval_2)
{
	std::ostringstream w;
	std::istringstream r("xqW1245t\nFSmcqhwoeQE\nCWQcwqcwq\n3 2 1\n2 3 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	voting_eval(w, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(w.str() == "xqW1245t\nFSmcqhwoeQE\nCWQcwqcwq\n");
}

TEST(Voting, voting_eval_3)
{
	std::ostringstream w;
	std::istringstream r("a\nb\nc\n2 3 1\n2 3 1\n1 2 3");
	Candidate candidates[3];
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int num_ballots = 0;
	voting_read(r, 3, num_ballots, candidates, ballots);
	voting_eval(w, 3, num_ballots, candidates, ballots);
	ASSERT_TRUE(w.str() == "b\n");
}

// ------------
// voting_solve
// ------------

TEST(Voting, voting_solve_1)
{
	std::ostringstream w;
	std::istringstream r("1\n\n3\nJames Albright\nChaele Fletcher\nNorman Magnusson\n1 2 3\n3 2 1\n1 2 3");
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "James Albright\n");
}

TEST(Voting, voting_solve_2)
{
	std::ostringstream w;
	std::istringstream r("1\n\n3\nxqW1245t\nFSmcqhwoeQE\nCWQcwqcwq\n3 2 1\n2 3 1\n1 2 3");
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "xqW1245t\nFSmcqhwoeQE\nCWQcwqcwq\n");
}

TEST(Voting, voting_solve_3)
{
	std::ostringstream w;
	std::istringstream r("1\n\n3\na\nb\nc\n2 3 1\n2 3 1\n1 2 3");
	voting_solve(r, w);
	ASSERT_TRUE(w.str() == "b\n");
}