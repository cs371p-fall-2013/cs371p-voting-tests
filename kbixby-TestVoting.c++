#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// voting_printWinners
TEST(Voting, printOneWinner) {
    std::ostringstream str;
    int candidateNum = 6;
    int votes[] = {1, 2, 5, 7, 12, 11};
    string names[] = {"A", "B", "C", "D", "E", "F"};
    voting_printWinners(str, votes, candidateNum, names);
    ASSERT_TRUE(str.str() == "E\n");
}

TEST(Voting, printThreeWinner) {
    std::ostringstream str;
    int candidateNum = 7;
    int votes[] = {0, 7, 0, 7, 0, 7, 0};
    string names[] = {"A", "B", "C", "D", "E", "F", "G"};
    voting_printWinners(str, votes, candidateNum, names);
    ASSERT_TRUE(str.str() == "B\nD\nF\n");
}

TEST(Voting, printAllWinner) {
    std::ostringstream str;
    int candidateNum = 3;
    int votes[] = {1, 1, 1};
    string names[] = {"A", "B", "C"};
    voting_printWinners(str, votes, candidateNum, names);
    ASSERT_TRUE(str.str() == "A\nB\nC\n");
}

// voting_hasWinner
TEST(Voting, hasNoWinner) {
    int candidateNum = 5;
    int votes[] = {1, 2, 7, 2, 5};
    bool b = voting_hasWinner(votes, candidateNum);
    ASSERT_TRUE(b == false);
}

TEST(Voting, hasNoWinner50) {
    int candidateNum = 3;
    int votes[] = {7, 2, 5};
    bool b = voting_hasWinner(votes, candidateNum);
    ASSERT_TRUE(b == false);
}

TEST(Voting, hasWinner) {
    int candidateNum = 4;
    int votes[] = {1, 2, 7, 2};
    bool b = voting_hasWinner(votes, candidateNum);
    ASSERT_TRUE(b == true);
}

// voting_allTied
TEST(Voting, notAllTied) {
    int candidateNum = 5;
    int votes[] = {1, 2, 7, 2, 5};
    bool b = voting_allTied(votes, candidateNum);
    ASSERT_TRUE(b == false);
}

TEST(Voting, allTied) {
    int candidateNum = 5;
    int votes[] = {2, 2, 2, 2, 2};
    bool b = voting_allTied(votes, candidateNum);
    ASSERT_TRUE(b == true);
}

TEST(Voting, remainingTied) {
    int candidateNum = 5;
    int votes[] = {7, 7, 7, 0, 7};
    bool b = voting_allTied(votes, candidateNum);
    ASSERT_TRUE(b == true);
}

// voting_redistribute
TEST(Voting, RedistTest1) {
    int votes[] = {2, 2, 1, 1};
    int buckets[20][1000][20] = { { { 1, 2, 3, 4 }, { 1, 2, 3, 4 } },
                             { { 2, 1, 3, 4 }, { 2, 3, 1, 4 } },
                             { { 3, 4, 1, 2 } },
                             { { 4, 3, 2, 1 } } };
    int losers[20] = {};
    int numLosers = 0;
    int candidateNum = 4;
    voting_redistribute(votes, buckets, losers, numLosers, candidateNum);
    ASSERT_TRUE(buckets[0][2][0] == 0);
    ASSERT_TRUE(buckets[0][2][1] == 0);
    ASSERT_TRUE(buckets[0][2][2] == 1);
    ASSERT_TRUE(buckets[1][2][0] == 0);
    ASSERT_TRUE(buckets[1][2][1] == 0);
    ASSERT_TRUE(buckets[1][2][2] == 2);
    ASSERT_TRUE(votes[0] == 3);
    ASSERT_TRUE(votes[1] == 3);
    ASSERT_TRUE(votes[2] == 0);
    ASSERT_TRUE(votes[3] == 0);
}

TEST(Voting, RedistTest2) {
    int votes[] = {1, 0, 2, 1};
    int losers[20] = {2};
    int numLosers = 1;
    int candidateNum = 4;
    int buckets[20][1000][20] = { { { 1, 2, 4, 3 } },
                                  { { 0, 0, 0, 0 } },
                                  { { 3, 4, 1, 2 }, { 3, 1, 4, 2 } },
                                  { { 4, 2, 3, 1 } } };
    voting_redistribute(votes, buckets, losers, numLosers, candidateNum);
    cerr << numLosers << " " << losers[0] << " " << losers[1] << " " << losers[2] << " " << losers[3] << " " << endl;
    ASSERT_TRUE(losers[0] == 2);
    ASSERT_TRUE(losers[1] == 1);
    ASSERT_TRUE(losers[2] == 4);
    ASSERT_TRUE(votes[0] == 0);
    ASSERT_TRUE(votes[1] == 0);
    ASSERT_TRUE(votes[2] == 4);
    ASSERT_TRUE(votes[3] == 0);
    ASSERT_TRUE(buckets[2][2][0] == 0);
    ASSERT_TRUE(buckets[2][2][1] == 0);
    ASSERT_TRUE(buckets[2][2][2] == 0);
    ASSERT_TRUE(buckets[2][2][3] == 3);
    ASSERT_TRUE(buckets[2][3][0] == 0);
    ASSERT_TRUE(buckets[2][3][1] == 0);
    ASSERT_TRUE(buckets[2][3][2] == 3);
    ASSERT_TRUE(buckets[2][3][3] == 1);
}

// This was a test that violated assertions
// TEST(Voting, RedistTest3) {
//     int votes[] = {1, , 0};
//     int losers[20] = {};
//     int numLosers = 0;
//     int candidateNum = 3;
//     int buckets[20][1000][20] = { { { 1, 2, 3} },
//                                   { { 2, 1, 3} }, 
//                                   { { 0, 0, 0} } };
//     voting_redistribute(votes, buckets, losers, numLosers, candidateNum);
//     ASSERT_TRUE(votes[0] == 1);
//     ASSERT_TRUE(votes[1] == 1);
//     ASSERT_TRUE(votes[2] == 0);
//     cerr << buckets[0][0][0] << endl;
//     cerr << buckets[0][0][1] << endl;
//     cerr << buckets[0][0][2] << endl;
//     ASSERT_TRUE(buckets[0][0][0] == 1);
//     ASSERT_TRUE(buckets[0][0][1] == 2);
//     ASSERT_TRUE(buckets[0][0][2] == 3);
//     ASSERT_TRUE(buckets[1][0][0] == 2);
//     ASSERT_TRUE(buckets[1][0][1] == 1);
//     ASSERT_TRUE(buckets[1][0][2] == 3);
// }

// voting_isLoser
TEST(Voting, isWinner) {
    int numLosers = 2;
    int losers[] = {3, 4};
    int vote = 1;
    bool b = voting_isLoser(numLosers, losers, vote);
    ASSERT_TRUE(b == false);
}

TEST(Voting, isLoser) {
    int numLosers = 2;
    int losers[] = {3, 4};
    int vote = 3;
    bool b = voting_isLoser(numLosers, losers, vote);
    ASSERT_TRUE(b == true);
}

TEST(Voting, isWinnerOneLoser) {
    int numLosers = 1;
    int losers[] = {3};
    int vote = 1;
    bool b = voting_isLoser(numLosers, losers, vote);
    ASSERT_TRUE(b == false);
}

// voting_electionRun
TEST(Voting, electionRun1) {
    std::ostringstream w;
    int candidateNum = 4;
    int votes[] = {2, 2, 1, 1};
    string names[] = {"red", "green", "blue", "orange"};
    int buckets[20][1000][20] = { { { 1, 2, 3, 4 }, { 1, 2, 3, 4 } },
                             { { 2, 1, 3, 4 }, { 2, 3, 1, 4 } },
                             { { 3, 4, 1, 2 } },
                             { { 4, 3, 2, 1 } } };
    voting_electionRun(w, candidateNum, names, votes, buckets);
    ASSERT_TRUE(w.str() == "red\ngreen\n");
}

TEST(Voting, electionRun2) {
    std::ostringstream w;
    int candidateNum = 4;
    string names[] = {"A", "B", "C", "D"};
    int votes[] = {1, 0, 2, 1};
    int buckets[20][1000][20] = { { { 1, 2, 4, 3 } },
                                  { { 0, 0, 0, 0 } },
                                  { { 3, 4, 1, 2 }, { 3, 1, 4, 2 } },
                                  { { 4, 2, 3, 1 } } };
    voting_electionRun(w, candidateNum, names, votes, buckets);
    ASSERT_TRUE(w.str() == "C\n");
}

TEST(Voting, electionRun3) {
    std::ostringstream w;
    int candidateNum = 3;
    int votes[] = {1, 1, 0};
    string names[] = {"A", "B", "C"};
    int buckets[20][1000][20] = { { { 1, 2, 3} },
                                      { { 2, 1, 3} }, 
                                      {            } };
    voting_electionRun(w, candidateNum, names, votes, buckets);
    ASSERT_TRUE(w.str() == "A\nB\n");
}

// voting_setupNames
TEST(Voting, setupNames1) {
    int candidateNum = 4;
    std::istringstream r("Red\nGreen\nBlue\nOrange\n1 2 3 4\n");
    string names[4];
    voting_setupNames(r, names, candidateNum);
    ASSERT_TRUE(names[0] == "Red");
    ASSERT_TRUE(names[1] == "Green");
    ASSERT_TRUE(names[2] == "Blue");
    ASSERT_TRUE(names[3] == "Orange");
}

TEST(Voting, setupNames2) {
    int candidateNum = 1;
    std::istringstream r("Red\n1 2 3 4\n");
    string names[1];
    voting_setupNames(r, names, candidateNum);
    ASSERT_TRUE(names[0] == "Red");
}

TEST(Voting, setupNames3) {
    int candidateNum = 4;
    std::istringstream r("a\naa\naaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n1 2 3 4\n");
    string names[4];
    voting_setupNames(r, names, candidateNum);
    ASSERT_TRUE(names[0] == "a");
    ASSERT_TRUE(names[1] == "aa");
    ASSERT_TRUE(names[2] == "aaa");
    ASSERT_TRUE(names[3] == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

//void voting_setupBallots (std::istream& r, vector< vector<int> >& buckets, int candidateNum);
TEST(Voting, setupBallotsOneCandidate) {
    int candidateNum = 1;
    std::istringstream r("1\n1\n1\n1\n1\n1\n1\n");
    int votes[20] = {};
    int buckets[20][1000][20] = {};
    voting_setupBallots(r, votes, buckets, candidateNum);
    ASSERT_TRUE(votes[0] == 7);
    ASSERT_TRUE(buckets[0][0][0] == 1);
    ASSERT_TRUE(buckets[0][1][0] == 1);
    ASSERT_TRUE(buckets[0][2][0] == 1);
    ASSERT_TRUE(buckets[0][3][0] == 1);
    ASSERT_TRUE(buckets[0][4][0] == 1);
    ASSERT_TRUE(buckets[0][5][0] == 1);
    ASSERT_TRUE(buckets[0][6][0] == 1);
}

TEST(Voting, setupBallotsOneBallot) {
    int candidateNum = 4;
    std::istringstream r("1 2 3 4\n");
    int votes[20] = {};
    int buckets[20][1000][20] = {};
    voting_setupBallots(r, votes, buckets, candidateNum);
    ASSERT_TRUE(votes[0] == 1);
    ASSERT_TRUE(buckets[0][0][0] == 1);
    ASSERT_TRUE(buckets[0][0][1] == 2);
    ASSERT_TRUE(buckets[0][0][2] == 3);
    ASSERT_TRUE(buckets[0][0][3] == 4);
}

TEST(Voting, setupBallotsOneVote) {
    int candidateNum = 1;
    std::istringstream r("1\n");
    int buckets[20][1000][20] = {};
    int votes[20] = {};
    voting_setupBallots(r, votes, buckets, candidateNum);
    ASSERT_TRUE(votes[0] == 1);
    ASSERT_TRUE(buckets[0][0][0] == 1);
}

TEST(Voting, setupBallotsGeneral) {
    int candidateNum = 3;
    std::istringstream r("1 3 2\n3 1 2\n2 3 1\n2 1 3\n");
    int buckets[20][1000][20] = {};
    int votes[20] = {};
    voting_setupBallots(r, votes, buckets, candidateNum);
    ASSERT_TRUE(votes[0] == 1);
    ASSERT_TRUE(votes[1] == 2);
    ASSERT_TRUE(votes[2] == 1);
    ASSERT_TRUE(buckets[0][0][0] == 1);
    ASSERT_TRUE(buckets[0][0][1] == 3);
    ASSERT_TRUE(buckets[0][0][2] == 2);
    ASSERT_TRUE(buckets[1][0][0] == 2);
    ASSERT_TRUE(buckets[1][0][1] == 3);
    ASSERT_TRUE(buckets[1][0][2] == 1);
    ASSERT_TRUE(buckets[1][1][0] == 2);
    ASSERT_TRUE(buckets[1][1][1] == 1);
    ASSERT_TRUE(buckets[1][1][2] == 3);
    ASSERT_TRUE(buckets[2][0][0] == 3);
    ASSERT_TRUE(buckets[2][0][1] == 1);
    ASSERT_TRUE(buckets[2][0][2] == 2);
}

//void voting_electionSetup (std::istream& r, std::ostream& w, int candidateNum);
TEST(Voting, electionSetupGeneral) {
    std::ostringstream w;
    std::istringstream r("red\ngreen\nblue\norange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    int candidateNum = 4;
    voting_electionSetup(r, w, candidateNum);
    ASSERT_TRUE(w.str() == "red\ngreen\n");
}

TEST(Voting, electionSetupOneCandidate) {
    std::ostringstream w;
    std::istringstream r("green\n1\n1\n1\n1\n1\n1");
    int candidateNum = 1;
    voting_electionSetup(r, w, candidateNum);
    ASSERT_TRUE(w.str() == "green\n");
}

TEST(Voting, electionSetupOneBallot) {
    std::ostringstream w;
    std::istringstream r("red\ngreen\nblue\norange\n3 4 1 2\n");
    int candidateNum = 4;
    voting_electionSetup(r, w, candidateNum);
    ASSERT_TRUE(w.str() == "blue\n");
}

//void voting_sessionSetup (std::istream& r, std::ostream& w);
TEST(Voting, sessionSetupOneElectionGeneral) {
    std::ostringstream w;
    std::istringstream r("1\n\n4\nred\ngreen\nblue\norange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    voting_sessionSetup(r, w);
    ASSERT_TRUE(w.str() == "red\ngreen\n");
}

TEST(Voting, sessionSetupOneElectionOneCandidate) {
    std::ostringstream w;
    std::istringstream r("1\n\n1\ngreen\n1\n1\n1\n1\n1\n1");
    voting_sessionSetup(r, w);
    ASSERT_TRUE(w.str() == "green\n");
}

TEST(Voting, sessionSetupOneElectionOneBallot) {
    std::ostringstream w;
    std::istringstream r("1\n\n4\nred\ngreen\nblue\norange\n3 4 1 2\n");
    voting_sessionSetup(r, w);
    ASSERT_TRUE(w.str() == "blue\n");
}

TEST(Voting, sessionSetupElectionGeneral) {
    std::ostringstream w;
    std::istringstream r("3\n\n4\nred\ngreen\nblue\norange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n1\ngreen\n1\n1\n1\n1\n1\n1\n\n4\nred\ngreen\nblue\norange\n3 4 1 2\n");
    voting_sessionSetup(r, w);
    ASSERT_TRUE(w.str() == "red\ngreen\n\ngreen\n\nblue\n");
}
