#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "Voting.h" // CandidateList, Ballot, BallotList, BallotsInfo

using namespace std;

// solve

TEST(VotingSolveTest, SingleCase) {
	istringstream in_stream("1\n\n2\nA\nB\n1 2\n1 2\n2 1\n");
	ostringstream out_stream;

	voting_solve(in_stream, out_stream);

	ASSERT_STREQ("A\n", out_stream.str().c_str());
}

TEST(VotingSolveTest, MultipleCases) {
	istringstream in_stream("2\n\n1\nA\n1\n\n2\nA\nB\n2 1\n");
	ostringstream out_stream;

	voting_solve(in_stream, out_stream);

	ASSERT_STREQ("A\n\nB\n", out_stream.str().c_str());
}

// handle_case

TEST(VotingHandleCaseTest, Basic) {
	istringstream in_stream("2\nA\nB\n1 2\n");
	ostringstream out_stream;

	voting_handle_case(in_stream, out_stream);

	ASSERT_STREQ("A\n", out_stream.str().c_str());
}

// read_candidates

TEST(VotingReadCandidatesTest, SingleCandidate) {
	istringstream in_stream("1\nA\n1\n1\n");
	CandidateList candidates;

	voting_read_candidates(in_stream, candidates);

	ASSERT_STREQ("A", candidates[0].c_str());
	ASSERT_EQ(1, candidates.size());
}

TEST(VotingReadCandidatesTest, LongerCandidateName) {
	istringstream in_stream("1\nA 1 ?   + \n1\n1\n");
	CandidateList candidates;

	voting_read_candidates(in_stream, candidates);

	ASSERT_STREQ("A 1 ?   + ", candidates[0].c_str());
	ASSERT_EQ(1, candidates.size());
}

TEST(VotingReadCandidatesTest, MultipleCandidates) {
	istringstream in_stream("2\nA\nB\n1 2\n2 1\n");
	CandidateList candidates;

	voting_read_candidates(in_stream, candidates);

	ASSERT_STREQ("A", candidates[0].c_str());
	ASSERT_STREQ("B", candidates[1].c_str());
	ASSERT_EQ(2, candidates.size());
}

// read_ballots

TEST(VotingReadBallotsTest, SingleBallot) {
	istringstream in_stream("1 2\n");
	int num_candidates = 2;
	BallotsInfo ballots_info;
	map<int, BallotList> expected_ballots_by_first_choice {
		{1, {{1, 2}}}
	};

	voting_read_ballots(in_stream, num_candidates, ballots_info);

	ASSERT_EQ(1, ballots_info.total_num_ballots);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

TEST(VotingReadBallotsTest, SingleVote) {
	istringstream in_stream("1\n");
	int num_candidates = 1;
	BallotsInfo ballots_info;
	map<int, BallotList> expected_ballots_by_first_choice {
		{1, {{1}}}
	};

	voting_read_ballots(in_stream, num_candidates, ballots_info);

	ASSERT_EQ(1, ballots_info.total_num_ballots);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

TEST(VotingReadBallotsTest, MultipleBallots) {
	istringstream in_stream("1 2\n2 1\n1 2\n");
	int num_candidates = 2;
	BallotsInfo ballots_info;
	map<int, BallotList> expected_ballots_by_first_choice {
		{1, {{1, 2}, {1, 2}}},
		{2, {{2, 1}}}
	};

	voting_read_ballots(in_stream, num_candidates, ballots_info);

	ASSERT_EQ(3, ballots_info.total_num_ballots);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

TEST(VotingReadBallotsTest, LargeNumberOfCandidates) {
	// old bug: was reading the 10 in front as 1
	istringstream in_stream("10 1 2 3 4 5 6 7 8 9\n");
	int num_candidates = 10;
	BallotsInfo ballots_info;
	map<int, BallotList> expected_ballots_by_first_choice {
		{10, {{10, 1, 2, 3, 4, 5, 6, 7, 8, 9}}}
	};

	voting_read_ballots(in_stream, num_candidates, ballots_info);

	ASSERT_EQ(1, ballots_info.total_num_ballots);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

// read_single_ballot

TEST(VotingReadSingleBallotTest, SingleCandidate) {
	istringstream in_stream("1\n");
	int num_candidates = 1;
	Ballot ballot;
	int first_choice;
	Ballot expected_ballot {1};

	voting_read_single_ballot(in_stream, num_candidates, ballot, first_choice);

	ASSERT_EQ(expected_ballot, ballot);
	ASSERT_EQ(1, first_choice);
}

TEST(VotingReadSingleBallotTest, MultipleCandidates) {
	istringstream in_stream("2 1\n");
	Ballot ballot;
	int num_candidates = 2;
	int first_choice;
	Ballot expected_ballot {2, 1};

	voting_read_single_ballot(in_stream, num_candidates, ballot, first_choice);

	ASSERT_EQ(expected_ballot, ballot);
	ASSERT_EQ(2, first_choice);
}

// determine_outcome

void run_determine_outcome_test(istringstream& in_stream, string& winner) {
	CandidateList candidates;
	voting_read_candidates(in_stream, candidates);

	BallotsInfo ballots_info;
	voting_read_ballots(in_stream, candidates.size(), ballots_info);

	voting_determine_outcome(candidates, ballots_info, winner);
}

TEST(VotingDetermineOutcomeTest, SingleCandidate) {
	istringstream in_stream(string() +
		"1\n" +
		"A\n" +
		"1\n" +
		"1\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, NoRunoff) {
	istringstream in_stream(string() +
		"2\n" +
		"A\n" +
		"B\n" +
		"1 2\n" +
		"2 1\n" +
		"2 1\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("B", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, OneRunoffOneLoser) {
	istringstream in_stream(string() +
		"3\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"1 2 3\n" +
		"1 2 3\n" +
		"2 1 3\n" +
		"2 1 3\n" +
		"3 2 1\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("B", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, OneRunoffMultipleLosers) {
	istringstream in_stream(string() +
		"4\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"2 1 3 4\n" +
		"2 1 3 4\n" +
		"3 2 1 4\n" +
		"4 2 1 3\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("B", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, MultipleRunoffs) {
	istringstream in_stream(string() +
		"6\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"E\n" +
		"F\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" + // cands 1 and 2 have 3 votes
		"3 2 1 4 5 6\n" +
		"3 2 1 4 5 6\n" +
		"4 2 1 3 5 6\n" +
		"4 2 1 3 5 6\n" + // cands 3 and 4 have 2 votes
		"5 1 2 3 4 6\n" +
		"6 2 1 3 4 5\n"   // cands 5 and 6 have 1 vote
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("B", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, SecondChoiceCandidateIsLoser) {
	istringstream in_stream(string() +
		"6\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"E\n" +
		"F\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"3 5 1 4 2 6\n" +
		"3 5 1 4 2 6\n" +
		"4 6 1 3 5 2\n" +
		"4 6 1 3 5 2\n" + // cands 3 and 4 have 1st-round losers as 2nd choices
		"5 1 2 3 4 6\n" +
		"6 2 1 3 4 5\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, LaterChoiceCandidateAlsoLoser) {
	istringstream in_stream(string() +
		"6\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"E\n" +
		"F\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"1 2 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"2 1 3 4 5 6\n" +
		"3 5 6 4 1 2\n" +
		"3 5 6 4 1 2\n" +
		"4 6 5 3 1 2\n" +
		"4 6 5 3 1 2\n" + // cands 3 and 4 have 1st-round losers as 2nd and 3rd choices
		"5 1 2 3 4 6\n" +
		"6 2 1 3 4 5\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, TwoWayTie) {
	istringstream in_stream(string() +
		"2\n" +
		"A\n" +
		"B\n" +
		"1 2\n" +
		"2 1\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A\nB", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, MultiWayTie) {
	istringstream in_stream(string() +
		"4\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"2 3 1 4\n" +
		"2 3 1 4\n" +
		"2 3 1 4\n" +
		"3 1 2 4\n" +
		"3 1 2 4\n" +
		"4 3 1 2\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A\nB\nC", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, TieFromRunoff) {
	istringstream in_stream(string() +
		"4\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"2 1 3 4\n" +
		"2 1 3 4\n" +
		"3 1 2 4\n" +
		"4 2 1 3\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A\nB", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, GuyWithNoVotes) {
	istringstream in_stream(string() +
		"2\n" +
		"A\n" +
		"B\n" +
		"1 2\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, TieAndGuyWithNoVotes) {
	istringstream in_stream(string() +
		"3\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"1 2 3\n" +
		"2 1 3\n"
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A\nB", winner.c_str());
}

TEST(VotingDetermineOutcomeTest, LoserEventuallyBreaksTie) {
	istringstream in_stream(string() +
		"4\n" +
		"A\n" +
		"B\n" +
		"C\n" +
		"D\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"1 2 3 4\n" +
		"2 1 3 4\n" +
		"2 1 3 4\n" +
		"2 1 3 4\n" +
		"2 1 3 4\n" + // 1 and 2 tied
		"3 1 2 4\n" +
		"3 2 1 4\n" + // 3 split on 1 and 2
		"4 3 1 2\n"   // 4 will sway 3 towards 1
	);
	string winner;

	run_determine_outcome_test(in_stream, winner);

	ASSERT_STREQ("A", winner.c_str());
}

// ----------------------
// decide_simple_majority
// ----------------------

TEST(VotingDecideSimpleMajorityTest, AllVotes) {
	CandidateList candidates {"A", "B"};
	set<int> contender_set {1};
	map<int, int> votes_by_cand {{1, 2}};
	int total_num_ballots = 2;
	string winner;

	bool decided = voting_decide_simple_majority(candidates, contender_set, votes_by_cand, total_num_ballots, winner);

	ASSERT_TRUE(decided);
	ASSERT_STREQ("A", winner.c_str());
}

TEST(VotingDecideSimpleMajorityTest, MostVotes) {
	CandidateList candidates {"A", "B"};
	set<int> contender_set {1, 2};
	map<int, int> votes_by_cand {{1, 1}, {2, 2}};
	int total_num_ballots = 3;
	string winner;

	bool decided = voting_decide_simple_majority(candidates, contender_set, votes_by_cand, total_num_ballots, winner);

	ASSERT_TRUE(decided);
	ASSERT_STREQ("B", winner.c_str());
}

TEST(VotingDecideSimpleMajorityTest, HalfVotes) {
	CandidateList candidates {"A", "B"};
	set<int> contender_set {1, 2};
	map<int, int> votes_by_cand {{1, 1}, {2, 1}};
	int total_num_ballots = 2;
	string winner;

	bool decided = voting_decide_simple_majority(candidates, contender_set, votes_by_cand, total_num_ballots, winner);

	ASSERT_FALSE(decided);
}

TEST(VotingDecideSimpleMajorityTest, FewVotes) {
	CandidateList candidates {"A", "B", "C"};
	set<int> contender_set {1, 2, 3};
	map<int, int> votes_by_cand {{1, 1}, {2, 1}, {3, 1}};
	int total_num_ballots = 3;
	string winner;

	bool decided = voting_decide_simple_majority(candidates, contender_set, votes_by_cand, total_num_ballots, winner);

	ASSERT_FALSE(decided);
}

// ----------------------------------
// find_min_max_votes_from_contenders
// ----------------------------------

TEST(VotingFindMinMaxVotesTest, NoZero) {
	set<int> contender_set {1, 2};
	map<int, int> votes_by_cand {{1, 2}, {2, 1}};
	int total_num_ballots = 3;
	int min_votes;
	int max_votes;

	voting_find_min_max_votes_from_contenders(contender_set, votes_by_cand, total_num_ballots, min_votes, max_votes);

	ASSERT_EQ(1, min_votes);
	ASSERT_EQ(2, max_votes);
}

TEST(VotingFindMinMaxVotesTest, WithZero) {
	set<int> contender_set {1, 2, 3};
	map<int, int> votes_by_cand {{1, 0}, {2, 1}, {3, 2}};
	int total_num_ballots = 3;
	int min_votes;
	int max_votes;

	voting_find_min_max_votes_from_contenders(contender_set, votes_by_cand, total_num_ballots, min_votes, max_votes);

	ASSERT_EQ(1, min_votes);
	ASSERT_EQ(2, max_votes);
}

TEST(VotingFindMinMaxVotesTest, MinMaxSame) {
	set<int> contender_set {1, 2};
	map<int, int> votes_by_cand {{1, 1}, {2, 1}};
	int total_num_ballots = 2;
	int min_votes;
	int max_votes;

	voting_find_min_max_votes_from_contenders(contender_set, votes_by_cand, total_num_ballots, min_votes, max_votes);

	ASSERT_EQ(1, min_votes);
	ASSERT_EQ(1, max_votes);
}

// ---------------------
// determine_tie_winners
// ---------------------

TEST(VotingDetermineTieWinnersTest, TwoWayTie) {
	CandidateList candidates {"A", "B"};
	set<int> contender_set {1, 2};
	string winner;

	voting_determine_tie_winners(candidates, contender_set, winner);

	ASSERT_STREQ("A\nB", winner.c_str());
}

TEST(VotingDetermineTieWinnersTest, MultiWayTie) {
	CandidateList candidates {"A", "B", "C", "D"};
	set<int> contender_set {2, 3, 4};
	string winner;

	voting_determine_tie_winners(candidates, contender_set, winner);

	ASSERT_STREQ("B\nC\nD", winner.c_str());
}

// --------------------------------------
// demote_contenders_and_reassign_ballots
// --------------------------------------

// there must be at least 3 contenders,
// else we had a simple majority or a tie earlier

TEST(VotingDemoteContendersTest, DemoteOne) {
	set<int> contender_set {1, 2, 3};
	map<int, int> votes_by_cand {{1, 2}, {2, 2}, {3, 1}};
	int min_votes = 1;
	set<int> loser_set;
	int total_num_ballots = 5;
	map<int, BallotList> ballots_by_first_choice {
		{1, {{1, 2, 3}, {1, 3, 2}}},
		{2, {{2, 1, 3}, {2, 3, 1}}},
		{3, {{3, 1, 2}}}
	};
	BallotsInfo ballots_info(total_num_ballots, ballots_by_first_choice);

	set<int> expected_contenders {1, 2};

	voting_demote_contenders_and_reassign_ballots(contender_set, votes_by_cand, min_votes, loser_set, ballots_info);

	ASSERT_EQ(expected_contenders, contender_set);
}

TEST(VotingDemoteContendersTest, DemoteMultiple) {
	set<int> contender_set {1, 2, 3, 4};
	map<int, int> votes_by_cand {{1, 2}, {2, 2}, {3, 1}, {4, 1}};
	int min_votes = 1;
	set<int> loser_set;
	int total_num_ballots = 6;
	map<int, BallotList> ballots_by_first_choice {
		{1, {{1, 2, 3, 4}, {1, 4, 3, 2}}},
		{2, {{2, 1, 3, 4}, {2, 4, 3, 1}}},
		{3, {{3, 1, 2, 4}}},
		{4, {{4, 1, 2, 3}}},
	};
	BallotsInfo ballots_info(total_num_ballots, ballots_by_first_choice);

	set<int> expected_contenders {1, 2};

	voting_demote_contenders_and_reassign_ballots(contender_set, votes_by_cand, min_votes, loser_set, ballots_info);

	ASSERT_EQ(expected_contenders, contender_set);
}

TEST(VotingDemoteContendersTest, DemoteMultipleVotingForEachOther) {
	set<int> contender_set {1, 2, 3, 4};
	map<int, int> votes_by_cand {{1, 2}, {2, 2}, {3, 1}, {4, 1}};
	int min_votes = 1;
	set<int> loser_set;
	int total_num_ballots = 6;
	map<int, BallotList> ballots_by_first_choice {
		{1, {{1, 2, 3, 4}, {1, 4, 3, 2}}},
		{2, {{2, 1, 3, 4}, {2, 4, 3, 1}}},
		{3, {{3, 4, 2, 1}}},
		{4, {{4, 3, 2, 1}}},
	};
	BallotsInfo ballots_info(total_num_ballots, ballots_by_first_choice);

	set<int> expected_contenders {1, 2};

	voting_demote_contenders_and_reassign_ballots(contender_set, votes_by_cand, min_votes, loser_set, ballots_info);

	ASSERT_EQ(expected_contenders, contender_set);
}

// ----------------------
// reassign_loser_ballots
// ----------------------

// first candidate in ballot is necessarily a loser

TEST(VotingReassignLoserBallotsTest, NoLosers) {
	BallotList loser_ballots {
		{1, 2, 3},
		{1, 2, 3},
		{1, 3, 2}
	};
	set<int> loser_set {1};
	// these aren't valid numbers, but for these tests it doesn't matter
	map<int, int> votes_by_cand {{2, 0}, {3, 0}};
	int total_num_ballots = 3;
	map<int, BallotList> ballots_by_first_choice {
		{2, {}},
		{3, {}}
	};
	BallotsInfo ballots_info(total_num_ballots, ballots_by_first_choice);
	map<int, BallotList> expected_ballots_by_first_choice {
		{2, {{1, 2, 3}, {1, 2, 3}}},
		{3, {{1, 3, 2}}}
	};

	ASSERT_EQ(0, votes_by_cand[2]);
	ASSERT_EQ(0, votes_by_cand[3]);

	voting_reassign_loser_ballots(loser_ballots, loser_set, votes_by_cand, ballots_info);

	ASSERT_EQ(2, votes_by_cand[2]);
	ASSERT_EQ(1, votes_by_cand[3]);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

TEST(VotingReassignLoserBallotsTest, SomeLosers) {
	BallotList loser_ballots {
		{1, 2, 3, 4, 5},
		{1, 4, 5, 2, 3},
		{1, 5, 3, 4, 2}
	};
	set<int> loser_set {1, 4, 5};
	map<int, int> votes_by_cand {{2, 0}, {3, 0}};
	int total_num_ballots = 3;
	map<int, BallotList> ballots_by_first_choice {
		{2, {}},
		{3, {}}
	};
	BallotsInfo ballots_info(total_num_ballots, ballots_by_first_choice);
	map<int, BallotList> expected_ballots_by_first_choice {
		{2, {{1, 2, 3, 4, 5}, {1, 4, 5, 2, 3}}},
		{3, {{1, 5, 3, 4, 2}}}
	};

	ASSERT_EQ(0, votes_by_cand[2]);
	ASSERT_EQ(0, votes_by_cand[3]);

	voting_reassign_loser_ballots(loser_ballots, loser_set, votes_by_cand, ballots_info);

	ASSERT_EQ(2, votes_by_cand[2]);
	ASSERT_EQ(1, votes_by_cand[3]);
	ASSERT_EQ(expected_ballots_by_first_choice, ballots_info.ballots_by_first_choice);
}

// -----------------------
// who_should_inherit_vote
// -----------------------

// first candidate in the ballot is always a loser,
// so we start looking at second

TEST(VotingWhoShouldInheritVoteTest, HeirSecond) {
	Ballot loser_ballot {1, 2, 3, 4};
	set<int> loser_set {1};

	int heir_index = voting_who_should_inherit_vote(loser_ballot, loser_set);

	ASSERT_EQ(2, heir_index);
}

TEST(VotingWhoShouldInheritVoteTest, HeirInMiddle) {
	Ballot loser_ballot {1, 2, 3, 4};
	set<int> loser_set {1, 2};

	int heir_index = voting_who_should_inherit_vote(loser_ballot, loser_set);

	ASSERT_EQ(3, heir_index);
}

TEST(VotingWhoShouldInheritVoteTest, HeirLast) {
	Ballot loser_ballot {1, 2, 3, 4};
	set<int> loser_set {1, 2, 3};

	int heir_index = voting_who_should_inherit_vote(loser_ballot, loser_set);

	ASSERT_EQ(4, heir_index);
}

// -------------
// print_outcome
// -------------

TEST(VotingPrintOutcomeTest, Basic) {
	ostringstream out_stream;
	string winner = "A";

	voting_print_outcome(out_stream, winner);

	ASSERT_TRUE(out_stream.str() == "A\n");
}

