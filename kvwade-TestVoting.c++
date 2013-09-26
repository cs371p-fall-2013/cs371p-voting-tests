#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// solve
// ----

TEST(Voting, solve1) {
  std::istringstream r("1\n\n2\na\nb\n1 2\n1 2");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "a\n");
}
TEST(Voting, solve2) {
  std::istringstream r("1\n\n2\na\nb\n");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "a\nb\n");
}
TEST(Voting, solve3) {
  std::istringstream r("1\n\n3\na\nb\nc\n1 2 3\n2 1 3");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "a\nb\n");
}

TEST(Voting, solve4) {
  std::istringstream r("0\n\n3\na\nb\nc\n1 2 3\n2 1 3");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "");
}
// ----
// eval
// ----

TEST(Voting, eval1) {
  string canidates[20];
  canidates[0] = "KEVIN";
  canidates[1] = "LAUREN";
  int ballotArray[1000][20];
  ballotArray[0][0] = 1;
  ballotArray[0][1] = 2;
  ballotArray[1][0] = 1;
  ballotArray[1][1] = 2;
  std::ostringstream w;
  voting_eval(canidates, ballotArray, 2, 2, w);
  ASSERT_TRUE(w.str() == "KEVIN\n");
}
TEST(Voting, eval2) {
  string canidates[20];
  canidates[0] = "KEVIN";
  canidates[1] = "LAUREN";
  int ballotArray[1000][20];
  ballotArray[0][0] = 2;
  ballotArray[0][1] = 1;
  ballotArray[1][0] = 1;
  ballotArray[1][1] = 2;
  std::ostringstream w;
  voting_eval(canidates, ballotArray, 2, 2, w);
  ASSERT_TRUE(w.str() == "KEVIN\nLAUREN\n");
}
TEST(Voting, eval3) {
  string canidates[20];
  canidates[0] = "KEVIN";
  canidates[1] = "LAUREN";
  canidates[2] = "RYAN";
  int ballotArray[1000][20] = {{1, 2, 3},{2, 1, 3},{3, 1, 2}, {2, 3, 1}};
  std::ostringstream w;
  voting_eval(canidates, ballotArray, 3, 4, w);
  ASSERT_TRUE(w.str() == "LAUREN\n");
}

// ----
// checkForWinner
// ----

TEST(Voting, winner1) {
  string canidates[20] = {"a", "b"};
  vector<int> a = {1, 2};
  vector<int> b = {3};
  vector<int> currentVotes[20] = {a, b};
  std::ostringstream w;
  ASSERT_TRUE(voting_checkForWinner(canidates, currentVotes, 3, w));
  ASSERT_TRUE(w.str()=="a\n");
}

TEST(Voting, winner2) {
  string canidates[20] = {"a", "b"};
  vector<int> a = {1};
  vector<int> b = {3};
  vector<int> currentVotes[20] = {a, b};
  std::ostringstream w;
  ASSERT_FALSE(voting_checkForWinner(canidates, currentVotes, 2, w));
  ASSERT_TRUE(w.str()=="");
}

TEST(Voting, winner3) {
  string canidates[20] = {"a", "b", "c"};
  vector<int> a = {1,4,5};
  vector<int> b = {3};
  vector<int> c = {2};
  vector<int> currentVotes[20] = {a, b, c};
  std::ostringstream w;
  ASSERT_TRUE(voting_checkForWinner(canidates, currentVotes, 5, w));
  ASSERT_TRUE(w.str()=="a\n");
}
TEST(Voting, winner4) {
string canidates[20] = {"a", "b", "c","d"};
vector<int> currentVotes[20] = {{0 ,1, 2, 3},{4},{5}, {}};
std::ostringstream w;
ASSERT_TRUE(voting_checkForWinner(canidates, currentVotes, 6, w));
ASSERT_TRUE(w.str()=="a\n");
}

// -------------
// checkForLoser
// -------------

TEST(Voting, Loser1) {
vector<int> currentVotes[20] = {{1, 2, 3},{2, 1, 3},{3, 1, 2}, {2, 3, 1}};
ASSERT_FALSE(voting_checkForLoser(currentVotes, 4));

}

TEST(Voting, Loser2) {
vector<int> currentVotes[20] = {{1, 2},{2, 1, 3},{3, 1, 2}, {2, 3, 1}};
ASSERT_TRUE(voting_checkForLoser(currentVotes, 4));

}

TEST(Voting, Loser3) {
vector<int> currentVotes[20] = {{1, 2},{2, 1},{3, 1, 2}, {2, 3, 1}};
ASSERT_TRUE(voting_checkForLoser(currentVotes, 4));

}

// -------------
// reassignVotes
// -------------

/*TEST(Voting, Reassing1){
vector<int> currentVotes[20] = {{0, 1},{2, 3},{4}};
int ballotArray[1000][20] = {{1, 2, 3}, {1, 2, 3}, {2,1,3},{2,1,3},{3,1,2}};
//voting_checkForLoser(currentVotes,3);
voting_reassignVotes(ballotArray, currentVotes,3);
ASSERT_TRUE(true);
//ASSERT_TRUE(currentVotes[0].size()==3);
}*/

// ----------------
// choiceEliminated
// ----------------

TEST(Voting, eliminate1) {
  int ballotArray[1000][20] = {{1, 2, 3}};
  voting_choiceEliminated(ballotArray, 0);
  ASSERT_TRUE(ballotArray[0][0] == 2);
}
TEST(Voting, eliminate2) {
  int ballotArray[1000][20] = {{-1, 2, 3}};
  voting_choiceEliminated(ballotArray, 0);
  ASSERT_TRUE(ballotArray[0][0] == 2);
}
TEST(Voting, eliminate3) {
  int ballotArray[1000][20] = {{0, 2, 3}};
  voting_choiceEliminated(ballotArray, 0);
  ASSERT_TRUE(ballotArray[0][0] == 2);
}
TEST(Voting, eliminate4) {
  int ballotArray[1000][20] = {{1, 2, 3}, {4, 5, 6}};
  voting_choiceEliminated(ballotArray, 1);
  ASSERT_TRUE(ballotArray[1][0] == 5);
}
