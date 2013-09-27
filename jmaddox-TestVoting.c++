/*
To test the program:

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

using namespace std;

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read) {
    std::istringstream r("1\nA\n1\n\n");
    int numCand;
		std::string names[MAX_CAND];
		struct ballot ballots[MAX_BALLOTS];
    const bool b = voting_read(r, numCand, names, ballots);
    ASSERT_TRUE(b == true);

    ASSERT_TRUE(numCand == 1);

    ASSERT_TRUE(names[0] == "A");

		ASSERT_TRUE(ballots[0].pref[0] == 1);}

TEST(Voting, read_1) {
		std::istringstream r("3\nA\nB\nC\n1 2 3\n 2 3 1\n 2 1 3\n\n");
		int numCand;
		std::string names[MAX_CAND];
		struct ballot ballots[MAX_BALLOTS];
    const bool b = voting_read(r, numCand, names, ballots);
    ASSERT_TRUE(b == true);

    ASSERT_TRUE(numCand == 3);

    ASSERT_TRUE(names[0] == "A");
		ASSERT_TRUE(names[1] == "B");
		ASSERT_TRUE(names[2] == "C");		

		ASSERT_TRUE(ballots[0].pref[0] == 1);
		ASSERT_TRUE(ballots[0].pref[1] == 2);
		ASSERT_TRUE(ballots[0].pref[2] == 3);

		ASSERT_TRUE(ballots[1].pref[0] == 2);
		ASSERT_TRUE(ballots[1].pref[1] == 3);
		ASSERT_TRUE(ballots[1].pref[2] == 1);

		ASSERT_TRUE(ballots[2].pref[0] == 2);
		ASSERT_TRUE(ballots[2].pref[1] == 1);
		ASSERT_TRUE(ballots[2].pref[2] == 3);
}

TEST(Voting, read_2) {
		std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n  			1 2 3 4 5\n 2 4 1 5 3\n 5 4 3 1 2\n\n");
		int numCand;
		std::string names[MAX_CAND];
		struct ballot ballots[MAX_BALLOTS];
    const bool b = voting_read(r, numCand, names, ballots);
    ASSERT_TRUE(b == true);

    ASSERT_TRUE(numCand == 5);

    ASSERT_TRUE(names[0] == "Bob Saget");
		ASSERT_TRUE(names[1] == "Bill Marr");
		ASSERT_TRUE(names[2] == "Catnis Everdeen");
		ASSERT_TRUE(names[3] == "Dick Chaney");		

		ASSERT_TRUE(ballots[0].pref[0] == 1);
		ASSERT_TRUE(ballots[0].pref[1] == 2);
		ASSERT_TRUE(ballots[0].pref[2] == 3);
		ASSERT_TRUE(ballots[0].pref[3] == 4);
		ASSERT_TRUE(ballots[0].pref[4] == 5);

		ASSERT_TRUE(ballots[1].pref[0] == 2);
		ASSERT_TRUE(ballots[1].pref[1] == 4);
		ASSERT_TRUE(ballots[1].pref[2] == 1);
		ASSERT_TRUE(ballots[1].pref[3] == 5);
		ASSERT_TRUE(ballots[1].pref[4] == 3);

		ASSERT_TRUE(ballots[2].pref[0] == 5);
		ASSERT_TRUE(ballots[2].pref[1] == 4);
		ASSERT_TRUE(ballots[2].pref[2] == 3);
		ASSERT_TRUE(ballots[2].pref[3] == 1);
		ASSERT_TRUE(ballots[2].pref[4] == 2);
}

// -----------
// num_ballots
// -----------

TEST(Voting, num_ballots) {
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++)
		ballots[i].pref[0] = 0;
	for(int i = 0; i < 10; i++){
		ballots[i].pref[0] = i+1;
	}
	ASSERT_TRUE(num_ballots(ballots) == 10);
}

TEST(Voting, num_ballots_1) {
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++) //clear array
		ballots[i].pref[0] = 0;
	for(int i = 0; i < 4; i++){
		ballots[i].pref[0] = i+1;
	}
	ballots[17].pref[0] = 55;
	ASSERT_TRUE(num_ballots(ballots) == 4);
}

TEST(Voting, num_ballots_2) {
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++) //clear array
		ballots[i].pref[0] = 0;
	for(int i = 0; i < 16; i++){
		ballots[i].pref[0] = i+1;
	}
	ballots[18].pref[0] = 77;
	ASSERT_TRUE(num_ballots(ballots) == 16);
}

// -----------
// majority
// -----------

TEST(Voting, majority) {
	int votes[MAX_CAND];
	for(int i = 0; i < MAX_CAND; i++) //clear array
		votes[i] = 0;
	votes[2] = 1;
	int numBallots = 1;
	int numCand = MAX_CAND;
	ASSERT_TRUE(majority(votes, numBallots, numCand) == 2);
}

TEST(Voting, majority_1) {
	int votes[MAX_CAND];
	for(int i = 0; i < MAX_CAND; i++) //clear array
		votes[i] = 0;
	votes[4] = 17;
	int numBallots = 1;
	int numCand = MAX_CAND;
	ASSERT_TRUE(majority(votes, numBallots, numCand) == 4);
}

TEST(Voting, majority_2) {
	int votes[MAX_CAND];
	for(int i = 0; i < MAX_CAND; i++) //clear array
		votes[i] = 0;
	votes[8] = 12;
	int numBallots = 1;
	int numCand = MAX_CAND;
	ASSERT_TRUE(majority(votes, numBallots, numCand) == 8);
}

// --------
// num_cand
// --------

TEST(Voting, num_cand) {
	string names[MAX_CAND];
	names[0] = "A";
	names[1] = "B";
	names[2] = "C";
	names[3] = "D";
	ASSERT_TRUE(num_cand(names)==4);
}

TEST(Voting, num_cand1) {
	string names[MAX_CAND];
	names[0] = "A";
	names[1] = "B";
	names[2] = "C";
	names[3] = "D";
	names[4] = "D";
	names[5] = "D";
	names[6] = "D";
	ASSERT_TRUE(num_cand(names)==7);
}

TEST(Voting, num_cand2) {
	string names[MAX_CAND];
	names[0] = "A";
	names[1] = "B";
	names[2] = "C";
	names[3] = "D";
	names[4] = "D";
	names[5] = "D";
	names[6] = "D";
	names[7] = "D";
	names[8] = "D";
	names[9] = "D";
	names[10] = "D";
	ASSERT_TRUE(num_cand(names)==11);
}

// --------
// is_tied
// --------

TEST(Voting, is_tied) {
	int votes[4] = {3, 0, 2, 1};
	ASSERT_TRUE(is_tied(votes, 4)==false);
}

TEST(Voting, is_tied_1) {
	int votes[7] = {3, 3, 0, 3, 585858, 4444, -2};
	ASSERT_TRUE(is_tied(votes, 4)==false);
}

TEST(Voting, is_tied_2) {
	int votes[7] = {3, -1, -1, -1, -1, -1, 3};
	ASSERT_TRUE(is_tied(votes, 7)==true);
}

// ------
// find_lowest
// ------

TEST(Voting, find_lowest){
	int votes[6] = {3, 4, 2, 1, 1, 2};
	ASSERT_TRUE(find_lowest(votes,6) == 1);
}

TEST(Voting, find_lowest1){
	int votes[6] = {3, -1, -1, 2, 0, -1};
	ASSERT_TRUE(find_lowest(votes,6) == 0);
}

TEST(Voting, find_lowest2){
	int votes[7] = {3, -1, -1, -1, -1, -1, 3};
	ASSERT_TRUE(find_lowest(votes,7) == 3);
}

// -----
// voting_eval
// -----

TEST(Voting, voting_eval){
 	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n\n");
	int numCand;
	string names[MAX_CAND];
	string winners[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}

  voting_read(r, numCand, names, ballots);
	voting_eval(names, ballots, winners, numCand);
	ASSERT_TRUE(winners[0] == "Bill Marr");
}

TEST(Voting, voting_eval1){
 	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n1 3 2 5 4\n4 3 2 1 5\n5 3 1 2 4\n3 4 5 2 1\n3 1 2 4 5\n\n");
	int numCand;
	string names[MAX_CAND];
	string winners[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}

  voting_read(r, numCand, names, ballots);
	voting_eval(names, ballots, winners, numCand);
	ASSERT_TRUE(winners[0] == "Catnis Everdeen");
}

TEST(Voting, voting_eval2){
 	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n1 3 2 5 4\n2 3 4 1 5\n2 3 1 5 4\n1 4 5 2 3\n1 3 2 4 5\n\n");
	int numCand;
	string names[MAX_CAND];
	string winners[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}

  voting_read(r, numCand, names, ballots);
	voting_eval(names, ballots, winners, numCand);
	ASSERT_TRUE(winners[0] == "Bob Saget" && winners[1] == "Bill Marr");
}

// -------
// reassign_losers
// -------

TEST(Voting, reassign_losers){
	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n\n");
	int numCand;
	string names[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}
	voting_read(r, numCand, names, ballots);
	
	int numBallots = num_ballots(ballots);
	struct ballot buckets[MAX_CAND][MAX_BALLOTS];
	int votes[MAX_CAND];
	for(int i = 0; i < numCand; i++) votes[i]=0;

	for(int i = 0; i < numBallots; i++){
		int cand = ballots[i].pref[0];
		buckets[cand-1][votes[cand-1]++] = ballots[i];
	}

	assert(votes[0] == 1);
	assert(votes[1] == 2);
	assert(votes[2] == 0);
	assert(votes[3] == 0);
	assert(votes[4] == 0);
	int low_vote = find_lowest(votes, numCand);
	assert(low_vote==0);
	reassign_losers(votes, buckets,low_vote, numCand);

	assert(votes[0] == 1);
	assert(votes[1] == 2);
	assert(votes[2] == -1);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
	low_vote = find_lowest(votes, numCand);
	assert(low_vote==1);
	
	reassign_losers(votes, buckets,low_vote, numCand);
	
	assert(votes[0] == -1);
	assert(votes[1] == 3);
	assert(votes[2] == -1);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
}

TEST(Voting, reassign_losers1){
	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n1 3 2 5 4\n4 3 2 1 5\n5 3 1 2 4\n3 4 5 2 1\n3 1 2 4 5\n\n");
	int numCand;
	string names[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}
	voting_read(r, numCand, names, ballots);
	
	int numBallots = num_ballots(ballots);
	struct ballot buckets[MAX_CAND][MAX_BALLOTS];
	int votes[MAX_CAND];
	for(int i = 0; i < numCand; i++) votes[i]=0;

	for(int i = 0; i < numBallots; i++){
		int cand = ballots[i].pref[0];
		buckets[cand-1][votes[cand-1]++] = ballots[i];
	}

	assert(votes[0] == 2);
	assert(votes[1] == 2);
	assert(votes[2] == 2);
	assert(votes[3] == 1);
	assert(votes[4] == 1);
	int low_vote = find_lowest(votes, numCand);
	assert(low_vote==1);
	reassign_losers(votes, buckets,low_vote, numCand);

	assert(votes[0] == 2);
	assert(votes[1] == 2);
	assert(votes[2] == 4);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
	low_vote = find_lowest(votes, numCand);
	assert(low_vote==2);
	
	reassign_losers(votes, buckets,low_vote, numCand);
	
	assert(votes[0] == -1);
	assert(votes[1] == -1);
	assert(votes[2] == 8);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
}

TEST(Voting, reassign_losers2){
	std::istringstream r("5\nBob Saget\nBill Marr\nCatnis Everdeen\nDick Chaney\nEarl Cambell\n1 2 3 4 5\n2 4 1 5 3\n2 4 3 1 5\n1 3 2 5 4\n2 3 4 1 5\n2 3 1 5 4\n1 4 5 2 3\n3 1 2 4 5\n\n");
	int numCand;
	string names[MAX_CAND];
	struct ballot ballots[MAX_BALLOTS];
	for(int i = 0; i < MAX_BALLOTS; i++){

		for(int j = 0; j < MAX_CAND; j++){
			ballots[i].pref[j] = 0;
		}
		ballots[i].index = 0;
	}
	voting_read(r, numCand, names, ballots);
	
	int numBallots = num_ballots(ballots);
	struct ballot buckets[MAX_CAND][MAX_BALLOTS];
	int votes[MAX_CAND];
	for(int i = 0; i < numCand; i++) votes[i]=0;

	for(int i = 0; i < numBallots; i++){
		int cand = ballots[i].pref[0];
		buckets[cand-1][votes[cand-1]++] = ballots[i];
	}

	assert(votes[0] == 3);
	assert(votes[1] == 4);
	assert(votes[2] == 1);
	assert(votes[3] == 0);
	assert(votes[4] == 0);
	int low_vote = find_lowest(votes, numCand);
	assert(low_vote==0);
	reassign_losers(votes, buckets,low_vote, numCand);

	assert(votes[0] == 3);
	assert(votes[1] == 4);
	assert(votes[2] == 1);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
	low_vote = find_lowest(votes, numCand);
	assert(low_vote==1);
	
	reassign_losers(votes, buckets,low_vote, numCand);
	
	assert(votes[0] == 4);
	assert(votes[1] == 4);
	assert(votes[2] == -1);
	assert(votes[3] == -1);
	assert(votes[4] == -1);
}

// -----
// print
// -----

TEST(Voting, print) {
    std::ostringstream w;
	std::string winners[MAX_CAND];
		winners[0] = "A";
    voting_print(w,winners,1);
    ASSERT_TRUE(w.str() == "A");}

TEST(Voting, print1) {
    std::ostringstream w;
	std::string winners[MAX_CAND];
		winners[0] = "A";
		winners[1] = "B";
    voting_print(w,winners,2);
    ASSERT_TRUE(w.str() == "A\nB");}


TEST(Voting, print2) {
    std::ostringstream w;
	std::string winners[MAX_CAND];
		winners[0] = "A";
		winners[1] = "B";
		winners[2] = "C";
    voting_print(w,winners,3);
    ASSERT_TRUE(w.str() == "A\nB\nC");}




