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

% valgrind TestVoting > TestVoting.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Voting.h"
// -----------
// TestVoting
// -----------

// ----
// nextPref
// ----

TEST(Voting_Ballot, nextPref_1) {
    Ballot x(20);
    string l = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
//    x.printPreferenceArray();
    int v = x.currPref();
  //  cout << endl << "CURRPREF: " <<  x.currPref() << endl;
    //cout << "NEXTPREF: " << x.nextPref() << endl;
    ASSERT_TRUE(v == 1);}

TEST(Voting_Ballot, toString_1) {
	Ballot x(20);
    	string l = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    	x.initBallot(l);
    	string s = x.toString();
	ASSERT_TRUE(s == l);}

TEST(Voting_Candidate, isLoser_1) {
	Candidate c(string("Billy"), 2);
	ASSERT_TRUE(c.isLoser() == false);
}

TEST(Voting_Candidate, getCandBallots_1) {
	Candidate c(string("Billy"), 2);
	Ballot b(5);
	b.initBallot("1 2 3 4 5");
	c.addBallot(&b);
	ASSERT_TRUE(c.getCandBallots() == 1);
}

TEST(Voting_Candidate, getVotes_1) {
	Candidate c(string("Billy"), 2);
        Ballot b(5);
        b.initBallot("1 2 3 4 5");
        c.addBallot(&b);
        ASSERT_TRUE(c.getVotes() == 1);
}

TEST(Voting_Candidate, getBallot_1) {
	Candidate c(string("Billy"), 2);
        Ballot b(5);
        b.initBallot("1 2 3 4 5");
        c.addBallot(&b);
        ASSERT_TRUE(c.getBallot(0) == &b);
}

TEST(Voting_Election, getCandidate_1) {
	Election e;
	istringstream s("\n2\nBilly\nBob\n1 2\n1 2\n2 1");
	e.initElection(s, true);
	ASSERT_TRUE((e.getCandidate(1)).toString() == "Billy");
}

TEST(Voting_Election, findNextValidVote_1) {
	Election e;
	istringstream s("\n2\nBilly\nBob\n1 2\n1 2\n2 1");
        e.initElection(s, true);
	Candidate c = e.getCandidate(1);
	Ballot *b1 = c.getBallot(0);
	ASSERT_TRUE(e.findNextValidVote(b1) == 1);
	
}

TEST(Voting_Election, checkInitialWinner_1) {
	Election e;
        istringstream s("\n2\nBilly\nBob\n1 2\n1 2\n2 1");
        e.initElection(s, true);
        ASSERT_TRUE(e.checkInitialWinner() == true);
}

TEST(Voting_Election, checkAllWayTie_1) {
	Election e;
        istringstream s("\n2\nBilly\nBob\n1 2\n2 1");
        e.initElection(s, true);
        ASSERT_TRUE(e.checkAllWayTie() == true);
}


TEST(Voting_Ballot, curPref_1) {
    Ballot x(20);
    string l = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    int v = x.currPref();
    ASSERT_TRUE(v == 1);}

TEST(Voting_Ballot, curPref_2) {
    Ballot x(20);
    string l = "20 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    int v = x.currPref();
    ASSERT_TRUE(v == 20);}

TEST(Voting_Ballot, curPref_3) {
    Ballot x(1);
    string l = "7";
    x.initBallot(l);
    int v = x.currPref();
    ASSERT_TRUE(v == 7);}

TEST(Voting_Ballot, nextPref_2) {
    Ballot x(6);
    string l = "15 16 17 18 19 20";
    x.initBallot(l);
    int v = x.nextPref();
    ASSERT_TRUE(v == 16);}

TEST(Voting_Ballot, nextPref_3) {
    Ballot x(20);
    string l = "20 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    int v = x.nextPref();
    ASSERT_TRUE(v == 2);}

TEST(Voting_Ballot, nextPref_4) {
    Ballot x(2);
    string l = "7 100";
    x.initBallot(l);
    int v = x.nextPref();}

TEST(Voting_Candidate, isLoserANDgetID_1) {
    string name = "person1";
    Candidate cand(name, 0);
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int id = cand.getID();
    ASSERT_TRUE(id == 0);}

TEST(Voting_Candidate, isLoserANDgetID_2) {
    string name = "person2";
    Candidate cand(name, 1);
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int id = cand.getID();
    ASSERT_TRUE(id == 1);}

TEST(Voting_Candidate, isLoserANDgetID_3) {
    string name = "person3";
    Candidate cand(name, 3);
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int id = cand.getID();
    ASSERT_TRUE(id == 3);}

TEST(Voting_Candidate, setLoserANDgetVotes_1) {
    string name = "person1";
    Candidate cand(name, 0);
    cand.addVote();
    int vote = cand.getVotes();
    ASSERT_TRUE(vote == 1);
    cand.setLoser();
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int i = cand.getVotes();
    ASSERT_TRUE(i == 0);}

TEST(Voting_Candidate, setLoserANDgetVotes_2) {
    string name = "person2";
    Candidate cand(name, 1);
    cand.addVote();
    int vote = cand.getVotes();
    ASSERT_TRUE(vote == 1);
    cand.setLoser();
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int i = cand.getVotes();
    ASSERT_TRUE(i == 0);}

TEST(Voting_Candidate, setLoserANDgetVotes_3) {
    string name = "person3";
    Candidate cand(name, 2);
    cand.setLoser();
    bool v = cand.isLoser();
    ASSERT_TRUE(v == false);
    int i = cand.getVotes();
    ASSERT_TRUE(i == 0);}

TEST(Voting_Candidate, addBallotANDgetCandBallots_1) {
    string name = "person1";
    Candidate cand(name, 1);
    Ballot x(20);
    string l = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    cand.addBallot(&x);
    int a = cand.getCandBallots();
    ASSERT_TRUE(a == 1);
    string nm = cand.toString();
    ASSERT_TRUE(name == nm);}

TEST(Voting_Candidate, addBallotANDgetCandBallots_2) {
    string name = "person2";
    Candidate cand(name, 2);
    Ballot x(20);
    string l = "2 1 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    cand.addBallot(&x);
    int a = cand.getCandBallots();
    ASSERT_TRUE(a == 1);
    string nm = cand.toString();
    ASSERT_TRUE(name == nm);}

TEST(Voting_Candidate, addBallotANDgetCandBallots_3) {
    string name = "person3";
    Candidate cand(name, 3);
    Ballot x(20);
    string l = "3 2 1 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    x.initBallot(l);
    cand.addBallot(&x);
    int a = cand.getCandBallots();
    ASSERT_TRUE(a == 1);
    string nm = cand.toString();
    ASSERT_TRUE(name == nm);}


