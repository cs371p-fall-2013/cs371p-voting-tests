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
using namespace std;

class Candidate{
    
public:
    string name;
    int votes;
    bool eliminated;
    std::vector<int> voters;
    
    Candidate(std::string n){
        name = n;
        votes = 0;
        eliminated = false;
    }
    
    Candidate(){
        name = "";
        votes = 0;
        eliminated = false;
    }
    
    void addV(int index){
        votes++;
        voters.push_back(index);
    }
    
    int removeV(){
        
        int v = voters.back();
        voters.pop_back();
        votes--;
        return v;
        
    }
    
};


// ----------
// TestVoting
// ----------

// --------------------
// voting_numCandidates
// --------------------

TEST(Voting, voting_numElections){
	std::istringstream r("3\n\n");
	int i;
	const bool b = voting_numElections(r, i);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 3);
}

TEST(Voting, voting_numelections_2){
        std::istringstream r("10\n\n");
        int i;
        const bool b = voting_numElections(r, i);
        ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 10);
}

TEST(Voting, voting_numelections_3){
        std::istringstream r("100\n\n");
        int i;
        const bool b = voting_numElections(r, i);
        ASSERT_TRUE(b == true);
        ASSERT_TRUE(i == 100);
}

// ----------------
// voting_read_case
// ----------------
/*
TEST(Voting, read_election) {
    Candidate x [21];
    std::istringstream r("3\njohn doe\njane smith\nsirhan sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int i;
    const bool b = read_election(r, i, x);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    3);}

TEST(Voting, read_election_2) {
	Candidate x [21];
    std::istringstream r("1\nasad\n1\n1\n1");
    int i;
    const bool b = read_election(r, i, x);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
}

TEST(Voting, read_election_3) {
Candidate x [21]; 
   std::istringstream r("5\nasad\nrex r\nabc\ntyu\npop\n1 2 3 4 5\n2 1 3 4 5\n4 5 2 3 1\n5 4 1 2 3\n4 5 3 1 2\n2 3 4 5 1");
    int i;
    const bool b = read_election(r, i, x);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    5);
}

// --------
// majority
// -------
/*
TEST(Voting, majority_1) {
		int i, num, m;
	std::istringstream r("1\n\n");
	std::ostringstream o;
	voting_numElections(r, num);
	std::istringstream x("3\njohn doe\njane smith\nsirhan sirhan\n1 2 3\n1 2 3\n2 3 1\n1 2 3\n1 3 2");
	voting_numCandidates(x, i);
	ASSERT_TRUE(i == 3);
	majority(o, i);
	std::cout << o.str();
	ASSERT_TRUE(o.str()  == "john doe\n");
}

TEST(Voting, majority_2) {
        int i, num, m;
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    majority(o, i);
    std::cout << o.str();
    ASSERT_TRUE(o.str()  == "");
}

TEST(Voting, majority_3) {
        int i, num, m;
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 1 2");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    majority(o, i);
    std::cout << o.str();
    ASSERT_TRUE(o.str()  == "");
}

// --------
// equalVotes
// -------

TEST(Voting, equalVotes_1) {
        int i, num, m;
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\njohn doe\njane smith\nsirhan sirhan\n1 2 3\n1 2 3\n2 3 1\n1 2 3\n1 3 2");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    equalVotes(o, i);
    std::cout << o.str();
    ASSERT_TRUE(o.str()  == "");
}

TEST(Voting, equalVotes_2) {
        int i, num, m;
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    equalVotes(o, i);
    std::cout << o.str();
    ASSERT_TRUE(o.str()  == "asad\nrex\n");
}

TEST(Voting, equalVotes_3) {
        int i, num, m;
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 1 2");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    equalVotes(o, i);
    std::cout << o.str();
    ASSERT_TRUE(o.str()  == "");
}

// --------
// evaluate_Votes
// -------

TEST(Voting, evaluateVotes_1) {
        int i, num, m;
        int ballots [1000][20];
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\njohn doe\njane smith\nsirhan sirhan\n1 2 3\n1 2 3\n2 3 1\n1 2 3\n1 3 2");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    read_election(x, i, ballots);
    evaluate_Votes(o, i, ballots);
    
    int test = {{1, 2, 3}, {1, 2, 3},{2, 3, 1}, {1, 2, 3}, {1, 3, 2}};
    for (int j = 0; j <  5; ++j)
    {
        for (int k = 0; k < i; ++k)
        {
            ASSERT_TRUE(test[j][k] == ballots[j][k]);
        }
    }
}

TEST(Voting, evaluateVotes_2) {
        int i, num, m;
        int ballots [1000][20];
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    read_election(x, i, ballots);
    evaluate_Votes(o, i, ballots);
    
    int test = {{1, 2, 3}, {1, 2, 3},{2, 3, 1}, {2, 3, 1}};
    for (int j = 0; j <  4; ++j)
    {
        for (int k = 0; k < i; ++k)
        {
            ASSERT_TRUE(test[j][k] == ballots[j][k]);
        }
    }
}

TEST(Voting, evaluateVotes_3) {
        int i, num, m;
        int ballots [1000][20];
    std::istringstream r("1\n\n");
    std::ostringstream o;
    voting_numElections(r, num);
    std::istringstream x("3\nasad\nrex\nchris\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 1 2");
    voting_numCandidates(x, i);
    ASSERT_TRUE(i == 3);
    read_election(x, i, ballots);
    evaluate_Votes(o, i, ballots);

    int test = {{1, 2, 3}, {1, 2, 3},{2, 3, 1}, {2, 3, 1}, {3, 1, 2}};
    for (int j = 0; j <  5; ++j)
    {
        for (int k = 0; k < i; ++k)
        {
            ASSERT_TRUE(test[j][k] == ballots[j][k]);
        }
    }
}



*/

