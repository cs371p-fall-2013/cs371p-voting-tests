///Project 2: TestVoting.c++
///Tyler Pixley and Alyssa Williams
///Lack of copyright 2013CE

///--------
///includes
///--------

#include <iostream>		// cout, endl
#include <sstream>		// istringstream, ostringstream

#include "gtest/gtest.h"
#include "Voting.h"

///----------
///TestVoting
///----------

///-----------------
///Election Num Read
///-----------------

TEST(Voting, election_num_read_1)
{
	std::istringstream r("1\n\n2\nAlyssa Williams\nTyler Pixley\n2 1\n1 2");
	int i;
	const bool b = voting_election_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 1);
}

TEST(Voting, election_num_read_2)
{
	std::istringstream r("1\n\n3\nThe Doctor\nRose Tyler\nCaptain Jack\n2 3 1\n3 2 1\n2 1 3");
	int i;
	const bool b = voting_candidate_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 1);
}

TEST(Voting, election_num_read_3)
{
	std::istringstream r("1\n\n5\nPikachu\nBulbasaur\nCharmander\nDragonite\nTyphlosion\n2 3 1 5 4\n5 1 3 4 2\n1 4 2 3 5\n5 4 3 2 1");
	int i;
	const bool b = voting_candidate_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 1);
}

///------------------
///Candidate Num Read
///------------------

TEST(Voting, candidate_num_read_1)
{
	std::istringstream r("2\nAlyssa Williams\nTyler Pixley\n2 1\n1 2\n");
	int i;
	const bool b = voting_candidate_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 2);
}

TEST(Voting, candidate_num_read_2)
{
	std::istringstream r("3\nThe Doctor\nRose Tyler\nCaptain Jack\n2 3 1\n3 2 1\n2 1 3");
	int i;
	const bool b = voting_candidate_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 3);
}

TEST(Voting, candidate_num_read_3)
{
	std::istringstream r("5\nPikachu\nBulbasaur\nCharmander\nDragonite\nTyphlosion\n2 3 1 5 4\n5 1 3 4 2\n1 4 2 3 5\n5 4 3 2 1");
	int i;
	const bool b = voting_candidate_num_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_TRUE(i == 5);
}

///-------------------
///Candidate Name Read
///-------------------

TEST(Voting, candidate_name_read_1)
{
	std::istringstream r("Alyssa Williams\nTyler Pixley\n2 1\n1 2\n");
	std::string names[2];
	const bool b = voting_candidate_name_read(r, names, 2);
	ASSERT_TRUE(b);
	ASSERT_TRUE(names[0] == "Alyssa Williams");
	ASSERT_TRUE(names[1] == "Tyler Pixley");
}

TEST(Voting, candidate_name_read_2)
{
	std::istringstream r("The Doctor\nRose Tyler\nCaptain Jack\n2 3 1\n3 2 1\n2 1 3");
	std::string names[3];
	const bool b = voting_candidate_name_read(r, names, 3);
	ASSERT_TRUE(b);
	ASSERT_TRUE(names[0] == "The Doctor");
	ASSERT_TRUE(names[1] == "Rose Tyler");
	ASSERT_TRUE(names[2] == "Captain Jack");
}

TEST(Voting, candidate_name_read_3)
{
	std::istringstream r("Pikachu\nBulbasaur\nCharmander\nDragonite\nTyphlosion\n2 3 1 5 4\n5 1 3 4 2\n1 4 2 3 5\n5 4 3 2 1");
	std::string names[5];
	const bool b = voting_candidate_name_read(r, names, 5);
	ASSERT_TRUE(b);
	ASSERT_TRUE(names[0] == "Pikachu");
	ASSERT_TRUE(names[1] == "Bulbasaur");
	ASSERT_TRUE(names[2] == "Charmander");
	ASSERT_TRUE(names[3] == "Dragonite");
	ASSERT_TRUE(names[4] == "Typhlosion");
}

///-----------
///Ballot Read
///-----------

TEST(Voting, ballot_read_1)
{
	std::istringstream r("2 1\n1 2\n");
	int votes[MAX_CANDIDATES] = {0};
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS] = {};
	int cand = 2;
	int nballots = 0;
	const bool b = voting_ballot_read(r, ballots, buckets, votes, nballots, cand);

	ASSERT_TRUE(b);

	ASSERT_TRUE(nballots == 2);

	ASSERT_TRUE(ballots[0][0] == 2);
	ASSERT_TRUE(ballots[0][1] == 1);
	ASSERT_TRUE(ballots[1][0] == 1);
	ASSERT_TRUE(ballots[1][1] == 2);

	ASSERT_TRUE(buckets[0][0] == &(ballots[1][0]));
	ASSERT_TRUE(buckets[0][1] == NULL);
	ASSERT_TRUE(buckets[1][0] == &(ballots[0][0]));
	ASSERT_TRUE(buckets[1][1] == NULL);

	ASSERT_TRUE(votes[0] == 1);
	ASSERT_TRUE(votes[1] == 1);
}

TEST(Voting, ballot_read_2)
{
	std::istringstream r("2 3 1\n3 2 1\n2 1 3\n");
	int votes[MAX_CANDIDATES] = {0}; 
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS] = {};
	int cand = 3;
	int nballots = 0;
	const bool b = voting_ballot_read(r, ballots, buckets, votes, nballots, cand);

	ASSERT_TRUE(b);

	ASSERT_TRUE(nballots == 3);

	ASSERT_TRUE(ballots[0][0] == 2);
	ASSERT_TRUE(ballots[0][1] == 3);
	ASSERT_TRUE(ballots[0][2] == 1);
	ASSERT_TRUE(ballots[1][0] == 3);
	ASSERT_TRUE(ballots[1][1] == 2);
	ASSERT_TRUE(ballots[1][2] == 1);
	ASSERT_TRUE(ballots[2][0] == 2);
	ASSERT_TRUE(ballots[2][1] == 1);
	ASSERT_TRUE(ballots[2][2] == 3);
	
	ASSERT_TRUE(buckets[0][0] == NULL);
	ASSERT_TRUE(buckets[0][1] == NULL);
	ASSERT_TRUE(buckets[0][2] == NULL);
	ASSERT_TRUE(buckets[1][0] == &(ballots[0][0]));
	ASSERT_TRUE(buckets[1][1] == &(ballots[2][0]));
	ASSERT_TRUE(buckets[1][2] == NULL);
	ASSERT_TRUE(buckets[2][0] == &(ballots[1][0]));
	ASSERT_TRUE(buckets[2][1] == NULL);
	ASSERT_TRUE(buckets[2][2] == NULL);

	ASSERT_TRUE(votes[0] == 0);
	ASSERT_TRUE(votes[1] == 2);
	ASSERT_TRUE(votes[2] == 1);
}

TEST(Voting, ballot_read_3)
{
	std::istringstream r("2 3 1 5 4\n5 1 3 4 2\n1 4 2 3 5\n5 4 3 2 1\n");
	int votes[MAX_CANDIDATES] = {0};
	int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS] = {};
	int cand = 5;
	int nballots = 0;
	const bool b = voting_ballot_read(r, ballots, buckets, votes, nballots, cand);

	ASSERT_TRUE(b);

	ASSERT_TRUE(nballots == 4);

	ASSERT_TRUE(ballots[0][0] == 2);
	ASSERT_TRUE(ballots[0][1] == 3);
	ASSERT_TRUE(ballots[0][2] == 1);
	ASSERT_TRUE(ballots[0][3] == 5);
	ASSERT_TRUE(ballots[0][4] == 4);
	ASSERT_TRUE(ballots[1][0] == 5);
	ASSERT_TRUE(ballots[1][1] == 1);
	ASSERT_TRUE(ballots[1][2] == 3);
	ASSERT_TRUE(ballots[1][3] == 4);
	ASSERT_TRUE(ballots[1][4] == 2);
	ASSERT_TRUE(ballots[2][0] == 1);
	ASSERT_TRUE(ballots[2][1] == 4);
	ASSERT_TRUE(ballots[2][2] == 2);
	ASSERT_TRUE(ballots[2][3] == 3);
	ASSERT_TRUE(ballots[2][4] == 5);
	ASSERT_TRUE(ballots[3][0] == 5);
	ASSERT_TRUE(ballots[3][1] == 4);
	ASSERT_TRUE(ballots[3][2] == 3);
	ASSERT_TRUE(ballots[3][3] == 2);
	ASSERT_TRUE(ballots[3][4] == 1);

	ASSERT_TRUE(buckets[0][0] == &(ballots[2][0]));
	ASSERT_TRUE(buckets[0][1] == NULL);
	ASSERT_TRUE(buckets[0][2] == NULL);
	ASSERT_TRUE(buckets[0][3] == NULL);
	ASSERT_TRUE(buckets[1][0] == &(ballots[0][0]));
	ASSERT_TRUE(buckets[1][1] == NULL);
	ASSERT_TRUE(buckets[1][2] == NULL);
	ASSERT_TRUE(buckets[1][3] == NULL);
	ASSERT_TRUE(buckets[2][0] == NULL);
	ASSERT_TRUE(buckets[2][1] == NULL);
	ASSERT_TRUE(buckets[2][2] == NULL);
	ASSERT_TRUE(buckets[2][3] == NULL);
	ASSERT_TRUE(buckets[3][0] == NULL);
	ASSERT_TRUE(buckets[3][1] == NULL);
	ASSERT_TRUE(buckets[3][2] == NULL);
	ASSERT_TRUE(buckets[3][3] == NULL);
	ASSERT_TRUE(buckets[4][0] == &(ballots[1][0]));
	ASSERT_TRUE(buckets[4][1] == &(ballots[3][0]));
	ASSERT_TRUE(buckets[4][2] == NULL);
	ASSERT_TRUE(buckets[4][3] == NULL);

	ASSERT_TRUE(votes[0] == 1);
	ASSERT_TRUE(votes[1] == 1);
	ASSERT_TRUE(votes[2] == 0);
	ASSERT_TRUE(votes[3] == 0);
	ASSERT_TRUE(votes[4] == 2);
}

///--------
///Decision
///--------

TEST(Voting, decision_1)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{2, 1}, {1, 2}};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];
	int votes[MAX_CANDIDATES] = {1, 1};

	buckets[0][0] = &(ballots[1][0]);
	buckets[1][0] = &(ballots[0][0]);
	
	int i = voting_decision(ballots, buckets, votes, 2, 2);
	ASSERT_TRUE(i == 0x3); //bitmap of winners
}

TEST(Voting, decision_2)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{2, 3, 1}, {3, 2, 1}, {2, 1, 3}};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];
	int votes[MAX_CANDIDATES] = {0, 2, 1};
	
	buckets[1][0] = &(ballots[0][0]);
	buckets[1][1] = &(ballots[2][0]);
	buckets[2][0] = &(ballots[1][0]);
	
	int i = voting_decision(ballots, buckets, votes, 3, 3);
	ASSERT_TRUE(i == 0x2); //bitmap of winners
}

TEST(Voting, decision_3)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{2, 3, 1, 5, 4}, {5, 1, 3, 4, 2}, {1, 4, 2, 3, 5}, {5, 4, 3, 2, 1}};
	int votes[MAX_CANDIDATES] = {1, 1, 0, 0, 2};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];

	buckets[0][0] = &(ballots[2][0]);
	buckets[1][0] = &(ballots[0][0]);
	buckets[4][0] = &(ballots[1][0]);
	buckets[4][1] = &(ballots[3][0]);

	int i = voting_decision(ballots, buckets, votes, 4, 5);
	ASSERT_TRUE(i == 16); //bitmap of winners, (binary)10000
}

///-----------------
///Loser Elimination
///-----------------

TEST(Voting, loser_eliminator_1)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{2, 1, 3}, {1, 2, 3}, {2, 1, 3}, {3, 2, 1}, {1, 3, 2}};
	int votes[MAX_CANDIDATES] = {2, 2, 1};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];

	buckets[0][0] = &(ballots[1][0]);
	buckets[0][1] = &(ballots[4][0]);
	buckets[1][0] = &(ballots[0][0]);
	buckets[1][1] = &(ballots[2][0]);
	buckets[2][0] = &(ballots[3][0]);

	voting_loser_eliminator(ballots, buckets, votes, 0x4, 5, 3); //3 lost
	ASSERT_TRUE(ballots[3][0] == 2); //{3, 2, 1} gets changed to {2, 2, 1}
	ASSERT_TRUE(buckets[1][2] == &(ballots[3][0]));
}

TEST(Voting, loser_eliminator_2)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{2, 3, 1}, {1, 2, 3}, {2, 1, 3}, {3, 2, 1}, {3, 1, 2}};
	int votes[MAX_CANDIDATES] = {1, 2, 2};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];

	buckets[0][0] = &(ballots[1][0]);
	buckets[1][0] = &(ballots[0][0]);
	buckets[1][1] = &(ballots[2][0]);
	buckets[2][0] = &(ballots[3][0]);
	buckets[2][1] = &(ballots[4][0]);

	voting_loser_eliminator(ballots, buckets, votes, 0x1, 5, 3); //1 lost
	ASSERT_TRUE(ballots[1][0] == 2); //{1, 2, 3} gets changed to {2, 2, 3}
	ASSERT_TRUE(buckets[1][2] == &(ballots[1][0]));
}

TEST(Voting, loser_eliminator_3)
{
	int ballots[MAX_BALLOTS][MAX_CANDIDATES] = {{1, 2, 3, 4}, {1, 3, 4, 2}, {3, 4, 2, 1}, {2, 4, 1, 3}, {3, 2, 1, 4}};
	int votes[MAX_CANDIDATES] = {2, 1, 2, 0};
	int* buckets[MAX_CANDIDATES][MAX_BALLOTS];

	buckets[0][0] = &(ballots[0][0]);
	buckets[0][1] = &(ballots[1][0]);
	buckets[1][0] = &(ballots[3][0]);
	buckets[2][0] = &(ballots[2][0]);
	buckets[2][1] = &(ballots[4][0]);

	voting_loser_eliminator(ballots, buckets, votes, 0xA, 5, 4); //2 lost, but 4 also lost so (binary)1010
	ASSERT_TRUE(ballots[3][0] == 1); //{2, 4, 1, 3} gets changed to {1, 4, 1, 3}, as only first vote is changed
	ASSERT_TRUE(buckets[0][2] == &(ballots[3][0]));
}

///------
///Output
///------

TEST(Voting, output_1)
{
	std::ostringstream w;
	std::string names[MAX_CANDIDATES];
	names[0] = "Alyssa Williams";
	names[1] = "Tyler Pixley";
	voting_output(w, names, 2, false);
	ASSERT_TRUE(w.str() == "Tyler Pixley\n\n");
}

TEST(Voting, output_2)
{
	std::ostringstream w;
	std::string names[MAX_CANDIDATES];
	names[0] = "The Doctor";
	names[1] = "Rose Tyler";
	names[2] = "Captain Jack";
	voting_output(w, names, 4, false);
	ASSERT_TRUE(w.str() == "Captain Jack\n\n");
}

TEST(Voting, output_3)
{
	std::ostringstream w;
	std::string names[MAX_CANDIDATES];
	names[0] = "Pikachu";
	names[1] = "Bulbasaur";
	names[2] = "Charmander";
	names[3] = "Dragonite";
	names[4] = "Typhlosion";
	voting_output(w, names, 5, false);
	ASSERT_TRUE(w.str() == "Pikachu\nCharmander\n\n");
}