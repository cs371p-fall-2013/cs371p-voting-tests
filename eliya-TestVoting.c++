
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "gtest/gtest.h"
#include "Voting.h"


//------
//read
//------
TEST(Voting, read) {
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
    voting_read(r);
    ASSERT_TRUE(numCand == 3);
}

TEST(Voting, read_2) {
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2");
    voting_read(r);
    ASSERT_TRUE(candidates.at(1) == "John Doe");
}

TEST(Voting, read_3) {
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n1 2 3 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n4 2 3 1");
    voting_read(r);
    ASSERT_TRUE(ballotsPerCand[1].size() == 2);
}


//----------
//calcMaxMin
//----------
TEST(Voting, calcMaxMin) {
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n1 2 3 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n4 2 3 1");
    voting_read(r);
    ASSERT_TRUE(minVotes = 1);
}

TEST(Voting, calcMaxMin_2) {
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n1 2 3 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n4 2 3 1");
    voting_read(r);
    ASSERT_TRUE(maxVotes = 2);
}

TEST(Voting, calcMaxMin_3) {
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
    voting_read(r);
    ASSERT_TRUE(maxVotes = 3);
}
TEST(Voting, calcMaxMin_4) {
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
    voting_read(r);
    ASSERT_TRUE(minVotes = 2);
}

TEST(Voting, calcMaxMin_5) {
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2");
    voting_read(r);
    ASSERT_TRUE(maxVotes = 3);  
}

//------------
//winnerExists
//------------
TEST(Voting, winnerExists) {
     std::istringstream r("");
    voting_read(r);

    numCand = 2; 
    tempWinners.clear();
    tempWinners.push_back(1);
    tempWinners.push_back(2);
    bool winner = winnerExists();
    ASSERT_TRUE(winner);
}

TEST(Voting, winnerExists_2) {
     std::istringstream r("");
    voting_read(r);

    numCand = 4;
    eliminated.clear();
    tempWinners.clear();
    eliminated.push_back(2);
    eliminated.push_back(4);
    tempWinners.push_back(1);    
    tempWinners.push_back(3);
    bool winner = winnerExists();
    ASSERT_TRUE(winner);
}

TEST(Voting, winnerExists_3) {
     std::istringstream r("");
    voting_read(r);
    majorVotes = 5;
    voteCount[1] = 5;
    bool winner = winnerExists();
    ASSERT_TRUE(winner);
}

//-----------
//voting_eval
//-----------
TEST(Voting, eval) {
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n1 2 3 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n4 2 3 1");
    voting_read(r);
    std::vector<string> winners = voting_eval();
    ASSERT_TRUE(winners.at(0) == "Jane Smith");
}

TEST(Voting, eval_2) {
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n3 1 2 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n3 2 3 1\n1 3 4 2");
    voting_read(r); 
    std::vector<string> winners = voting_eval();
    ASSERT_TRUE(winners.size() == 3);
}

TEST(Voting, eval_3) { 
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n4 1 2 3\n2 4 1 3\n2 3 4 1\n1 2 3 4\n3 2 3 1\n1 3 4 2");
    voting_read(r);
    std::vector<string> winners = voting_eval();
    ASSERT_TRUE(winners.size() == 2);
}

//--------------
//sortCandidates
//--------------
TEST(Voting, sortCandidates) {    
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n4 1 2 3\n2 4 1 3\n2 3 4 1\n1 2 3 4\n3 2 3 1\n1 3 4 2");
    voting_read(r);
    sortCandidates();
    ASSERT_TRUE(losers.size() == 2);
}

TEST(Voting, sortCandidates_2) {    
    std::istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n4 1 2 3\n2 4 1 3\n2 3 4 1\n1 2 3 4\n3 2 3 1\n1 3 4 2");
    voting_read(r);
    sortCandidates();
    ASSERT_TRUE(tempWinners.size() == 2);
}

TEST(Voting, sortCandidates_3) {        
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1\n1 3 2");  
    voting_read(r);   
    sortCandidates(); 
    ASSERT_TRUE(nonWinners.size() == 1);
}

//--------------
//vectorContains
//--------------
TEST(Voting, vectorContains) {    
    vector<int> temp;
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    ASSERT_TRUE(vectorContains(temp, 1) == 0);
}

TEST(Voting, vectorContains_2) {      
    vector<int> temp;
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    ASSERT_TRUE(vectorContains(temp, 4) == -1);
}

TEST(Voting, vectorContains_3) {      
    vector<int> temp;
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    ASSERT_TRUE(vectorContains(temp, 3) == 2);
}

//------------
//voting_print
//------------
TEST(Voting, print) {      
    std::ostringstream w;
    vector<string> temp;
    temp.push_back("John Doe");
    voting_print(w, temp);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, print_2) {
    std::ostringstream w;
    vector<string> temp;    
    temp.push_back("John Doe");
    temp.push_back("Jane Smith");
    voting_print(w, temp);
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\n");
}

TEST(Voting, print_3) {
    std::ostringstream w;
    vector<string> temp;    
    temp.push_back("John Doe");
    temp.push_back("Jane Smith");
    temp.push_back("Sirhan Sirhan");
    voting_print(w, temp);
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}

//------------
//voting_solve
//------------
TEST(Voting, solve) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, solve_2) {   
     std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n4 3 2 1\n2 4 1 3\n2 3 4 1\n1 2 3 4\n3 2 3 1\n1 3 4 2");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Jane Smith\n");
}

TEST(Voting, solve_3) {    
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBen Smith\n1 2 3 4\n2 4 1 3\n2 3 4 1\n1 2 3 4\n4 2 3 1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Jane Smith\n");
}

