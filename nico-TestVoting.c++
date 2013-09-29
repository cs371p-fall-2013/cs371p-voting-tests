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

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------
#include "gtest/gtest.h"
#include "Voting.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

#define MAX_CANDIDATES 20
#define MAX_BALLOTS 1000
#define FIRST 1
#define SECOND 2
#define THIRD 3 
#define FOURTH 4

// -----------
// TestVoting
// -----------

// ----
// reassign_ballots
// ----

TEST(voting, reassign_ballots) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int lowestBallotCount = 1;
	int numCandidates = 3;
	int totalBallots = 4;
	
	candidateBags[0].push_back("1 2 3");
	candidateBags[0].push_back("1 3 2");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 1 2");
	reassign_ballots(candidateBags, lowestBallotCount, numCandidates, valid, totalBallots);
	assert(candidateBags[0].size() == 4);}
	
TEST(voting, reassign_ballots_2) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int lowestBallotCount = 1;
	int numCandidates = 3;
	int totalBallots = 4;
	
	candidateBags[0].push_back("1 2 3");
	candidateBags[2].push_back("3 1 2");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 1 2");
	reassign_ballots(candidateBags, lowestBallotCount, numCandidates, valid, totalBallots);
	assert(candidateBags[2].size() == 4);}
	
TEST(voting, reassign_ballots_3) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int lowestBallotCount = 1;
	int numCandidates = 3;
	int totalBallots = 4;
	
	candidateBags[0].push_back("1 2 3");
	candidateBags[1].push_back("2 1 2");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 1 2");
	reassign_ballots(candidateBags, lowestBallotCount, numCandidates, valid, totalBallots);
	assert(candidateBags[1].size() == 4);}
	
//--------
//bag_size
//--------
TEST(voting, bag_size) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[0].push_back("0");
	candidateBags[0].push_back("1");
	
	int size = bag_size(0, candidateBags, valid);
	assert(size == 3);}
	
TEST(voting, bag_size_2) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[0].push_back("0");
	candidateBags[0].push_back("1");
	
	int size = bag_size(1, candidateBags, valid);
	assert(size == 0);}

TEST(voting, bag_size_3) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	valid[0] = false;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[0].push_back("0");
	candidateBags[0].push_back("1");
	
	int size = bag_size(0, candidateBags, valid);
	assert(size == 0);}
	
	
//--------
//all_tied
//--------

TEST(voting, all_tied) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[1].push_back("1");
	candidateBags[2].push_back("1");
	int numCandidates = 3;
	
	bool ret = all_tied(candidateBags, valid, numCandidates);
	assert(ret == true);}

TEST(voting, all_tied_2) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	valid[1] = false;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[2].push_back("1");
	int numCandidates = 3;
	
	bool ret = all_tied(candidateBags, valid, numCandidates);
	assert(ret == true);}
	
TEST(voting, all_tied_3) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	candidateBags[0].push_back("1");
	candidateBags[2].push_back("1");
	int numCandidates = 3;
	
	bool ret = all_tied(candidateBags, valid, numCandidates);
	assert(ret == false);}
	
	
//------------
//find_winner
//------------

TEST(voting, find_winner) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int numCandidates = 3;
	int totalBallots = 3;
	candidateBags[0].push_back("1 2 3");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 2 1");
	int winner = find_winner(candidateBags, valid, numCandidates, totalBallots);
	
	assert(winner == -1);}
	
TEST(voting, find_winner_1) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int numCandidates = 3;
	int totalBallots = 5;
	candidateBags[0].push_back("1 2 3");
	candidateBags[0].push_back("1 2 3");
	candidateBags[0].push_back("1 2 3");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 2 1");
	int winner = find_winner(candidateBags, valid, numCandidates, totalBallots);
	
	assert(winner == 0);}
	
TEST(voting, find_winner_2) {
using namespace std;
	bool valid[MAX_CANDIDATES];
	for(int i = 0; i < MAX_CANDIDATES; i++)
		valid[i] = true;
	vector<string> candidateBags[20];
	int numCandidates = 3;
	int totalBallots = 9;
	candidateBags[0].push_back("1 2 3");
	candidateBags[0].push_back("1 2 3");
	candidateBags[0].push_back("1 2 3");
	candidateBags[1].push_back("2 1 3");
	candidateBags[2].push_back("3 2 1");
	candidateBags[2].push_back("3 2 1");
	candidateBags[2].push_back("3 2 1");
	candidateBags[2].push_back("3 2 1");
	candidateBags[2].push_back("3 2 1");
	
	int winner = find_winner(candidateBags, valid, numCandidates, totalBallots);
	
	assert(winner == 2);}
	
	
//-------------
//get_vote
//-------------

TEST(voting, get_vote) {
using namespace std;
	int rank =get_vote("1 2 3 4", 0);
	assert(rank == 1);}
	
TEST(voting, get_vote_1) {
using namespace std;
	int rank = get_vote("99 2 3", 0);
	assert(rank == 99);}
	
TEST(voting, get_vote_2) {
using namespace std;
	int rank = get_vote("99 2 3", 2);
	assert(rank == 3);}

//------------
//read_ballots
//------------
TEST(voting, read_ballots) {
using namespace std;
	vector<string> candidateBags[20];
	istringstream input("1 2 3\n2 3 1\n");
	ostringstream output;
	int numCandidates = 2;
	
	int num = read_ballots(candidateBags, input, output, numCandidates);
	assert(num == 2);
	assert(candidateBags[0].size() == 1);
	assert(candidateBags[1].size() == 1);}
	
TEST(voting, read_ballots_2) {
using namespace std;
	vector<string> candidateBags[20];
	istringstream input("1 2 3\n2 3 1\n1 2 3\n2 3 1\n");
	ostringstream output;
	int numCandidates = 2;
	
	int num = read_ballots(candidateBags, input, output, numCandidates);
	assert(num == 4);
	assert(candidateBags[0].size() == 2);
	assert(candidateBags[1].size() == 2);}

TEST(voting, read_ballots_3) {
using namespace std;
	vector<string> candidateBags[20];
	istringstream input("\n");
	ostringstream output;
	int numCandidates = 2;
	
	int num = read_ballots(candidateBags, input, output, numCandidates);
	assert(num == 0);
	assert(candidateBags[0].size() == 0);
	assert(candidateBags[1].size() == 0);}
	
TEST(voting, read_names) {
using namespace std;
	vector<string> names;
	istringstream input("mando\nnico\nzach\n");
	int numCandidates = 3;
	read_names(names, input, numCandidates);
	assert(names.size() == 3);}

TEST(voting, read_names_2) {
using namespace std;
	vector<string> names;
	istringstream input("mando\n");
	int numCandidates = 1;
	read_names(names, input, numCandidates);
	assert(names.size() == 1);}
	
TEST(voting, read_names_3) {
using namespace std;
	vector<string> names;
	istringstream input("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n");
	int numCandidates = 20;
	read_names(names, input, numCandidates);
	assert(names.size() == 20);}

	
	
