#include "Voting.h"
#include <sstream>
#include "gtest/gtest.h"

using namespace std;

TEST(Voting, read) {
	istringstream in("3\nBob\nJoe smith\nsusan\n1 2 3\n2 1 3\n1 2 3\n3 1 2\n3 2 1\n2 3 1\n");
	candidate *candidates;
	int numCandidates = readElection(in, candidates);

	assert(numCandidates == 3);
	assert(candidates[0].numVotes == 2);
	assert(candidates[1].numVotes == 2);
	assert(candidates[2].numVotes == 2);

	assert(candidates[0].votes[0]->v[0] == 1);
	assert(candidates[0].votes[0]->v[1] == 0);
	assert(candidates[0].votes[0]->v[2] == 1);
	assert(candidates[0].votes[0]->v[3] == 2);
}

TEST(Voting, findWinnersOrLosers) {
	istringstream in("1\nBob\n1\n");
	candidate *candidates;
	readElection(in, candidates);
	vector<int> winner;
	bool ret = findWinnersOrLosers(winner);
	assert(ret);
	assert(winner.size() == 1);
	assert(winner[0] == 0);
	assert(candidates[0].name == "Bob");
}

TEST(Voting, findWinnersOrLosers_2) {
	istringstream in("2\nBob\nLarry\n1 2\n2 1\n");
	candidate *candidates;
	readElection(in, candidates);
	vector<int> winner;
	bool ret = findWinnersOrLosers(winner);
	assert(ret);
	assert(winner.size() == 2);
	assert(winner[0] == 0);
	assert(candidates[0].name == "Bob");
	assert(winner[1] == 1);
	assert(candidates[1].name == "Larry");
}

TEST(Voting, findWinnersOrLosers_3) {
	istringstream in("2\nBob\nLarry\n1 2\n2 1\n1 2\n");
	candidate *candidates;
	readElection(in, candidates);
	vector<int> winner;
	bool ret = findWinnersOrLosers(winner);
	assert(ret);
	assert(winner.size() == 1);
	assert(winner[0] == 0);
	assert(candidates[0].name == "Bob");
}

TEST(Voting, findWinnersOrLosers_4) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n2 1 3\n1 2 3\n3 1 2\n3 1 2\n");
	candidate *candidates;
	readElection(in, candidates);
	vector<int> loser;
	bool ret = findWinnersOrLosers(loser);
	assert(ret == false);
	assert(loser.size() == 1);
	assert(loser[0] == 1);
	assert(candidates[1].name == "Larry");
}

TEST(Voting, findWinnersOrLosers_5) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n1 2 3\n3 1 2\n3 1 2\n");
	candidate *candidates;
	readElection(in, candidates);
	vector<int> loser;
	bool ret = findWinnersOrLosers(loser);
	assert(ret == false);
	assert(loser.size() == 2);
	assert(loser[0] == 1);
	assert(candidates[1].name == "Larry");
	assert(loser[1] == 2);
	assert(candidates[2].name == "Joe");
}

TEST(Voting, redistributeVotes) {
	istringstream in("2\nBob\nLarry\n1 2\n2 1\n1 2\n");
	candidate *candidates;
	readElection(in, candidates);
	candidates[0].isEliminated = true;
	redistributeVotes(0);
	assert(candidates[1].numVotes == 3);
}

TEST(Voting, redistributeVotes_2) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n2 1 3\n1 2 3\n");
	candidate *candidates;
	readElection(in, candidates);
	candidates[0].isEliminated = true;
	redistributeVotes(0);
	assert(candidates[1].numVotes == 3);
	candidates[1].isEliminated = true;
	redistributeVotes(1);
	assert(candidates[2].numVotes == 3);
}

TEST(Voting, redistributeVotes_3) {
	istringstream in("3\nBob\nLarry\nJoe\n1 3 2\n2 1 3\n1 2 3\n");
	candidate *candidates;
	readElection(in, candidates);
	candidates[0].isEliminated = true;
	redistributeVotes(0);
	assert(candidates[1].numVotes == 2);
	assert(candidates[2].numVotes == 1);
	candidates[1].isEliminated = true;
	redistributeVotes(1);
	assert(candidates[2].numVotes == 3);
}

TEST(Voting, redistributeVotes_4) {
	istringstream in("3\nBob\nLarry\nJoe\n1 3 2\n2 1 3\n1 2 3\n");
	candidate *candidates;
	readElection(in, candidates);
	candidates[0].isEliminated = true;
	candidates[1].isEliminated = true;
	redistributeVotes(0);
	assert(candidates[1].numVotes == 1);
	assert(candidates[2].numVotes == 2);
	redistributeVotes(1);
	assert(candidates[2].numVotes == 3);
}

TEST(Voting, redistributeVotes_5) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n1 2 3\n3 1 2\n3 1 2\n");
	candidate *candidates;
	readElection(in, candidates);
	candidates[1].isEliminated = true;
	candidates[2].isEliminated = true;
	redistributeVotes(1);
	redistributeVotes(2);
	assert(candidates[0].numVotes == 7);
}

TEST(Voting, runElection) {
	istringstream in("3\nBob\nLarry\nJoe\n1 3 2\n2 1 3\n1 2 3\n");
	ostringstream out;
	runElection(in, out, false);
	assert(out.str() == "Bob\n\n");
}

TEST(Voting, runElection_2) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n1 2 3\n3 1 2\n3 1 2\n");
	ostringstream out;
	runElection(in, out, false);
	assert(out.str() == "Bob\n\n");
}

TEST(Voting, runElection_3) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 1 2\n3 1 3\n");
	ostringstream out;
	runElection(in, out, false);
	assert(out.str() == "Bob\nJoe\n\n");
}

TEST(Voting, runElection_4) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2\n3 1 2\n3 1 2\n2 3 1\n");
	ostringstream out;
	runElection(in, out, false);
	assert(out.str() == "Bob\n\n");
}

TEST(Voting, runElection_5) {
	istringstream in("3\nBob\nLarry\nJoe\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2\n3 1 2\n3 1 2\n3 1 2\n2 3 1\n2 3 1\n");
	ostringstream out;
	runElection(in, out, false);
	assert(out.str() == "Joe\n\n");
}
