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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Voting.h"



//TEST READCASES
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/

TEST(Voting, readCases_1) {
  std::istringstream iStream("1\n");
  int numCases;
  const bool b = voting_readCases(iStream, numCases);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCases == 1);
}

TEST(Voting, readCases_2) {
  std::istringstream iStream("100\n");
  int numCases;
  const bool b = voting_readCases(iStream, numCases);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCases == 100);
}

TEST(Voting, readCases_3) {
  std::istringstream iStream("5\n");
  int numCases;
  const bool b = voting_readCases(iStream, numCases);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCases == 5);
}

//TEST READCANDIDATE NAMES
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/

TEST(Voting, readCandidates_1) {
  std::string candidateNames[21] = {};  
  std::istringstream iStream("2\nTom Cat\nJerry Mouse\n");
  int numCandidates;
  const bool b = voting_readCandidates(iStream, numCandidates, candidateNames);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCandidates == 2);
  ASSERT_TRUE(candidateNames[1] == ("Tom Cat"));
  ASSERT_TRUE(candidateNames[2] == ("Jerry Mouse"));
}


TEST(Voting, readCandidates_2) {
  std::string candidateNames[21] = {}; 
  std::istringstream iStream("5\nTom Cat\nJerry Mouse\nTest Hi\nJohn Smith\nJane Doe");
  int numCandidates;
  const bool b = voting_readCandidates(iStream, numCandidates, candidateNames);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCandidates == 5);
  ASSERT_TRUE(candidateNames[1] == ("Tom Cat"));
  ASSERT_TRUE(candidateNames[2] == ("Jerry Mouse"));
  ASSERT_TRUE(candidateNames[3] == ("Test Hi"));
  ASSERT_TRUE(candidateNames[4] == ("John Smith"));
  ASSERT_TRUE(candidateNames[5] == ("Jane Doe"));
}

TEST(Voting, readCandidates_3) {
  std::string candidateNames[21] = {}; 
  std::istringstream iStream("1\nTom Cat\n");
  int numCandidates;
  const bool b = voting_readCandidates(iStream, numCandidates, candidateNames);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCandidates == 1);
  ASSERT_TRUE(candidateNames[1] == ("Tom Cat"));
}

TEST(Voting, readCandidates_4) {
  std::string candidateNames[21] = {}; 
  std::istringstream iStream("20\nA 1\nA 2\nA 3\nA 4\nA 5\nA 6\nA 7\nA 8\nA 9\nA 10\nA 11\nA 12\nA 13\nA 14\nA 15\nA 16\nA 17\nA 18\nA 19\nA 20\n");
  int numCandidates;
  const bool b = voting_readCandidates(iStream, numCandidates, candidateNames);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(numCandidates == 20);
  ASSERT_TRUE(candidateNames[1] == ("A 1"));
  ASSERT_TRUE(candidateNames[2] == ("A 2"));
  ASSERT_TRUE(candidateNames[3] == ("A 3"));
  ASSERT_TRUE(candidateNames[4] == ("A 4"));
  ASSERT_TRUE(candidateNames[5] == ("A 5"));
  ASSERT_TRUE(candidateNames[6] == ("A 6"));
  ASSERT_TRUE(candidateNames[7] == ("A 7"));
  ASSERT_TRUE(candidateNames[8] == ("A 8"));
  ASSERT_TRUE(candidateNames[9] == ("A 9"));
  ASSERT_TRUE(candidateNames[10] == ("A 10"));
  ASSERT_TRUE(candidateNames[11] == ("A 11"));
  ASSERT_TRUE(candidateNames[12] == ("A 12"));
  ASSERT_TRUE(candidateNames[13] == ("A 13"));
  ASSERT_TRUE(candidateNames[14] == ("A 14"));
  ASSERT_TRUE(candidateNames[15] == ("A 15"));
  ASSERT_TRUE(candidateNames[16] == ("A 16"));
  ASSERT_TRUE(candidateNames[17] == ("A 17"));
  ASSERT_TRUE(candidateNames[18] == ("A 18"));
  ASSERT_TRUE(candidateNames[19] == ("A 19"));
  ASSERT_TRUE(candidateNames[20] == ("A 20"));
}


//TEST READBALLOTS
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/
TEST(Voting, readBallots_1) {
  int buckets[21][1000][20] = {{{0}}}; // 2 = numCandidates
  std::istringstream iStream("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
  int numCandidates = 3;
  int numBallots;
  int bucketSizes[21] = {0};
  const bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(buckets[1][0][1] == 2);
  ASSERT_TRUE(buckets[1][0][2] == 3);
  
  ASSERT_TRUE(buckets[2][0][1] == 1);
  ASSERT_TRUE(buckets[2][0][2] == 3);
  
  ASSERT_TRUE(buckets[2][1][1] == 3);
  ASSERT_TRUE(buckets[2][1][2] == 1);
  
  ASSERT_TRUE(buckets[1][1][1] == 2);
  ASSERT_TRUE(buckets[1][1][2] == 3);
  
  ASSERT_TRUE(buckets[3][0][1] == 1);
  ASSERT_TRUE(buckets[3][0][2] == 2);
  ASSERT_TRUE(numBallots == 5);
  
  ASSERT_TRUE(b);
  ASSERT_TRUE(bucketSizes[1] == 2);
  ASSERT_TRUE(bucketSizes[2] == 2);
  ASSERT_TRUE(bucketSizes[3] == 1);
}

TEST(Voting, readBallots_2) {
  int buckets[21][1000][20] = {{{0}}};
  std::istringstream iStream("1 2 3 4\n4 3 2 1\n1 2 4 3\n3 2 4 1\n1 3 4 2\n\n");
  int numCandidates = 4;
  int numBallots;
  int bucketSizes[21] = {0};
  const bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(buckets[1][0][1] == 2);
  ASSERT_TRUE(buckets[1][0][2] == 3);
  ASSERT_TRUE(buckets[1][0][3] == 4);

  ASSERT_TRUE(buckets[4][0][1] == 3);
  ASSERT_TRUE(buckets[4][0][2] == 2);
  ASSERT_TRUE(buckets[4][0][3] == 1);

  ASSERT_TRUE(buckets[1][1][1] == 2);
  ASSERT_TRUE(buckets[1][1][2] == 4);
  ASSERT_TRUE(buckets[1][1][3] == 3);

  ASSERT_TRUE(buckets[3][0][1] == 2);
  ASSERT_TRUE(buckets[3][0][2] == 4);
  ASSERT_TRUE(buckets[3][0][3] == 1);

  ASSERT_TRUE(buckets[1][2][1] == 3);
  ASSERT_TRUE(buckets[1][2][2] == 4);
  ASSERT_TRUE(buckets[1][2][3] == 2);
     
  ASSERT_TRUE(b);
  ASSERT_TRUE(bucketSizes[1] == 3);
  ASSERT_TRUE(bucketSizes[2] == 0);
  ASSERT_TRUE(bucketSizes[3] == 1);
}

TEST(Voting, readBallots_3) {
  int buckets[21][1000][20] = {{{0}}};
  std::istringstream iStream("1 2 3 4 5 6 7 8 9 10 11 12\n12 11 10 9 8 7 6 5 4 3 2 1\n\n");
  int numCandidates = 12;
  int numBallots;
  int bucketSizes[21] = {0};
  const bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(buckets[1][0][1] == 2);
  ASSERT_TRUE(buckets[1][0][2] == 3);
  ASSERT_TRUE(buckets[1][0][3] == 4);
  ASSERT_TRUE(buckets[1][0][4] == 5);
  ASSERT_TRUE(buckets[1][0][5] == 6);
  ASSERT_TRUE(buckets[1][0][6] == 7);
  ASSERT_TRUE(buckets[1][0][7] == 8);
  ASSERT_TRUE(buckets[1][0][8] == 9);
  ASSERT_TRUE(buckets[1][0][9] == 10);
  ASSERT_TRUE(buckets[1][0][10] == 11);
  ASSERT_TRUE(buckets[1][0][11] == 12);
  
  ASSERT_TRUE(buckets[12][0][1] == 11);
  ASSERT_TRUE(buckets[12][0][2] == 10);
  ASSERT_TRUE(buckets[12][0][3] == 9);
  ASSERT_TRUE(buckets[12][0][4] == 8);
  ASSERT_TRUE(buckets[12][0][5] == 7);
  ASSERT_TRUE(buckets[12][0][6] == 6);
  ASSERT_TRUE(buckets[12][0][7] == 5);
  ASSERT_TRUE(buckets[12][0][8] == 4);
  ASSERT_TRUE(buckets[12][0][9] == 3);
  ASSERT_TRUE(buckets[12][0][10] == 2);
  ASSERT_TRUE(buckets[12][0][11] == 1);
  
  ASSERT_TRUE(b);
  ASSERT_TRUE(bucketSizes[1] == 1);
  ASSERT_TRUE(bucketSizes[12] == 1);
}


//TEST VOTING_EVAL
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/

TEST(Voting,  voting_eval_1){  
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int numCandidates = 3;
  int numBallots = 5;
  int results[21] = {0};
  int indxResults = 0;

    buckets[1][0][1] = 2;
    buckets[1][0][2] = 3;
  
    buckets[2][0][1] = 1;
    buckets[2][0][2] = 3;
  
    buckets[2][1][1] = 3;
    buckets[2][1][2] = 1;
  
    buckets[1][1][1] = 2;
    buckets[1][1][2] = 3;
  
    buckets[3][0][1] = 1;
    buckets[3][0][2] = 2;
  bool b = voting_eval(buckets, numCandidates, numBallots, results, bucketSizes, indxResults);
  
  ASSERT_TRUE(b);
  ASSERT_TRUE(results[0] == 1);
}

TEST(Voting,  voting_eval_2){
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int numCandidates = 12;
  int numBallots = 2;
  int results[21] = {0};
  int indxResults = 0;
  buckets[1][0][1] = 2;
  buckets[1][0][2] = 3;
  buckets[1][0][3] = 4;
  buckets[1][0][4] = 5;
  buckets[1][0][5] = 6;
  buckets[1][0][6] = 7;
  buckets[1][0][7] = 8;
  buckets[1][0][8] = 9;
  buckets[1][0][9] = 10;
  buckets[1][0][10] = 11;
  buckets[1][0][11] = 12;
  
  buckets[12][0][1] = 12;
  buckets[12][0][2] = 11;
  buckets[12][0][3] = 10;
  buckets[12][0][4] = 9;
  buckets[12][0][5] = 8;
  buckets[12][0][6] = 7;
  buckets[12][0][7] = 6;
  buckets[12][0][8] = 5;
  buckets[12][0][9] = 4;
  buckets[12][0][10] = 3;
  buckets[12][0][11] = 2;

  bool b = voting_eval(buckets, numCandidates, numBallots, results, bucketSizes, indxResults);
  
  ASSERT_TRUE(b);
  ASSERT_TRUE(results[0] == 1);
  ASSERT_TRUE(results[1] == 2);
}


TEST(Voting,  voting_eval_3){  //Tie Test 2
  
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int numCandidates = 4;
  int numBallots = 5;
  int results[21] = {0};
  int indxResults = 0;

  buckets[1][0][1] = 2;
  buckets[1][0][2] = 3;
  buckets[1][0][3] = 4;

  buckets[4][0][1] = 3;
  buckets[4][0][2] = 2;
  buckets[4][0][3] = 1;

  buckets[1][1][1] = 2;
  buckets[1][1][2] = 4;
  buckets[1][1][3] = 3;

  buckets[3][0][1] = 2;
  buckets[3][0][2] = 4;
  buckets[3][0][3] = 1;

  buckets[1][2][1] = 3;
  buckets[1][2][2] = 4;
  buckets[1][2][3] = 2;

  bool b = voting_eval(buckets, numCandidates, numBallots, results, bucketSizes, indxResults);
  
  ASSERT_TRUE(b);
  ASSERT_TRUE(results[0] == 1);
  ASSERT_TRUE(results[1] == 2);
}

//TEST VOTING_PRINT
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/
TEST(Voting,  voting_print_1){
    std::ostringstream oStream;
    int results[21] = {0};
    int indxResults = 1;
    results[0] = 1;
    std::string candidateNames[] = {"", "Tom Cat", "Jerry Mouse", "Lola Bunny", "Bugs Bunny"};
    voting_print(oStream, results, candidateNames, indxResults);
//    std::cout << oStream.str() << std::endl;
    ASSERT_TRUE(oStream.str() == "Tom Cat\n");
}


TEST(Voting,  voting_print_2){
    std::ostringstream oStream;
    int results[21] = {0};
    int indxResults = 3;
    results[0] = 1;
    results[1] = 2;
    results[2] = 4;
    std::string candidateNames[] = {"", "Tom Cat", "Jerry Mouse", "Lola Bunny", "Bugs Bunny"};
    voting_print(oStream, results, candidateNames, indxResults);
//    std::cout << oStream.str() << std::endl;
    ASSERT_TRUE(oStream.str() == "Tom Cat\nJerry Mouse\nBugs Bunny\n");
}

TEST(Voting,  voting_print_3){  
     std::ostringstream oStream;
    int results[21] = {0};
    int indxResults = 3;
    results[0] = 2;
    results[1] = 3;
    results[2] = 4;
    //int results[1] = ;
    std::string candidateNames[] = {"", "Tom Cat", "Jerry Mouse", "Lola Bunny", "Bugs Bunny"};
    voting_print(oStream, results, candidateNames, indxResults);
//    std::cout << oStream.str() << std::endl;
    ASSERT_TRUE(oStream.str() == "Jerry Mouse\nLola Bunny\nBugs Bunny\n");
}

//TEST FINDWINNERSANDLOSERS
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/
TEST(Voting,  findWinnersAndLosers_1){ 
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  int min = 1;
  std::istringstream iStream("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
  int numCandidates = 3;
  int numBallots = 5;
  int winning_amount = 2;
  int indxResults = 0;
  int numOfPref = 3;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
        ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 0);
	ASSERT_TRUE(losers[3] == 0);
  bool b2 = findWinnersAndLosers(bucketSizes, losers, results, min, winning_amount, indxResults, numOfPref);
  ASSERT_TRUE(!b2);//No winner should have been found yet
        ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 0);
	ASSERT_TRUE(losers[3] == 1);
  
}

TEST(Voting,  findWinnersAndLosers_2){ 
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  int min = 0;
  std::istringstream iStream("1 2 3 4\n4 3 2 1\n1 2 4 3\n2 3 4 1\n1 3 4 2\n\n");
  int numCandidates = 4;
  int numBallots = 5;
  int winning_amount = 2;
  int indxResults = 0;
  int numOfPref = 4;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
        ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 0);
	ASSERT_TRUE(losers[3] == 0);
	ASSERT_TRUE(losers[4] == 0);
  bool b2 = findWinnersAndLosers(bucketSizes, losers, results, min, winning_amount, indxResults, numOfPref);
  ASSERT_TRUE(b2);
        ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 0);
	ASSERT_TRUE(losers[3] == 1);
	ASSERT_TRUE(losers[4] == 0);
}

TEST(Voting,  findWinnersAndLosers_3){ 
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  int min = 0;
  std::istringstream iStream("1 2 3 4 5 6 7 8 9 10 11 12\n12 11 10 9 8 7 6 5 4 3 2 1\n\n");
  int numCandidates = 12;
  int numBallots = 2;
  int winning_amount = 6;
  int indxResults = 0;
  int numOfPref = 12;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
        ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 0);
	ASSERT_TRUE(losers[3] == 0);
	ASSERT_TRUE(losers[4] == 0);
	ASSERT_TRUE(losers[5] == 0);
	ASSERT_TRUE(losers[6] == 0);
	ASSERT_TRUE(losers[7] == 0);
	ASSERT_TRUE(losers[8] == 0);
	ASSERT_TRUE(losers[9] == 0);
	ASSERT_TRUE(losers[10] == 0);
	ASSERT_TRUE(losers[11] == 0);
	ASSERT_TRUE(losers[12] == 0);
  bool b2 = findWinnersAndLosers(bucketSizes, losers, results, min, winning_amount, indxResults, numOfPref);
  	ASSERT_TRUE(!b2);//No winner should have been found this round
  	ASSERT_TRUE(losers[1] == 0);
  	ASSERT_TRUE(losers[2] == 1);
	ASSERT_TRUE(losers[3] == 1);
	ASSERT_TRUE(losers[4] == 1);
	ASSERT_TRUE(losers[5] == 1);
	ASSERT_TRUE(losers[6] == 1);
	ASSERT_TRUE(losers[7] == 1);
	ASSERT_TRUE(losers[8] == 1);
	ASSERT_TRUE(losers[9] == 1);
	ASSERT_TRUE(losers[10] == 1);
	ASSERT_TRUE(losers[11] == 1);
	ASSERT_TRUE(losers[12] == 0);
}

//TEST REASSIGNTALLIES
/***********************************************************/
/*							   */
/*							   */
/***********************************************************/
TEST(Voting,  reassignTallies_1){  //General Reaasignment
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  std::istringstream iStream("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
  int numCandidates = 3;
  int numBallots = 5;
  int winning_amount = 2;
  int indxResults = 0;
  int numOfPref = 3;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
  losers[3] = 1;
  ASSERT_TRUE(bucketSizes[1] == 2);
  ASSERT_TRUE(bucketSizes[3] == 1);
  reassignTallies(buckets, bucketSizes, losers, results, winning_amount, indxResults, numBallots, numOfPref);
  ASSERT_TRUE(bucketSizes[1] == 3);
  ASSERT_TRUE(bucketSizes[3] == 0);
}

TEST(Voting,  reassignTallies_2){  //Don't Reassign when at 0 votes
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  std::istringstream iStream("1 2 3 4\n4 3 2 1\n1 2 4 3\n2 3 4 1\n1 3 4 2\n\n");
  int numCandidates = 4;
  int numBallots = 5;
  int winning_amount = 2;
  int indxResults = 0;
  int numOfPref = 4;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
  losers[3] = 1;
  ASSERT_TRUE(bucketSizes[1] == 3);
  ASSERT_TRUE(bucketSizes[2] == 1);
  ASSERT_TRUE(bucketSizes[3] == 0);
  ASSERT_TRUE(bucketSizes[4] == 1);
  reassignTallies(buckets, bucketSizes, losers, results, winning_amount, indxResults, numBallots, numOfPref);
  ASSERT_TRUE(bucketSizes[1] == 3);
  ASSERT_TRUE(bucketSizes[2] == 1);
  ASSERT_TRUE(bucketSizes[3] == 0);
  ASSERT_TRUE(bucketSizes[4] == 1);
}

TEST(Voting,  reassignTallies_3){  
  int buckets[21][1000][20] ={{{0}}};
  int bucketSizes[21] = {0};
  int results[21] = {0};
  int losers[21] = {0};
  std::istringstream iStream("1 2 3 4 5 6 7 8 9 10 11 12\n12 11 10 9 8 7 6 5 4 3 2 1\n\n");
  int numCandidates = 12;
  int numBallots = 2;
  int winning_amount = 6;
  int indxResults = 0;
  int numOfPref = 12;
  bool b = voting_readBallots(iStream, buckets, numCandidates, numBallots, bucketSizes);
  ASSERT_TRUE(b);
  
  losers[2] = 1;
  losers[3] = 1;
  losers[4] = 1;
  losers[5] = 1;
  losers[6] = 1;
  losers[7] = 1;
  losers[8] = 1;
  losers[9] = 1;
  losers[10] = 1;
  losers[11] = 1;
  ASSERT_TRUE(bucketSizes[1] == 1);
  ASSERT_TRUE(bucketSizes[2] == 0);
  ASSERT_TRUE(bucketSizes[3] == 0);
  ASSERT_TRUE(bucketSizes[4] == 0);
  ASSERT_TRUE(bucketSizes[5] == 0);
  ASSERT_TRUE(bucketSizes[6] == 0);
  ASSERT_TRUE(bucketSizes[7] == 0);
  ASSERT_TRUE(bucketSizes[8] == 0);
  ASSERT_TRUE(bucketSizes[9] == 0);
  ASSERT_TRUE(bucketSizes[10] == 0);
  ASSERT_TRUE(bucketSizes[11] == 0);
  ASSERT_TRUE(bucketSizes[12] == 1);

  reassignTallies(buckets, bucketSizes, losers, results, winning_amount, indxResults, numBallots, numOfPref);
  ASSERT_TRUE(bucketSizes[1] == 1);
  ASSERT_TRUE(bucketSizes[2] == 0);
  ASSERT_TRUE(bucketSizes[3] == 0);
  ASSERT_TRUE(bucketSizes[4] == 0);
  ASSERT_TRUE(bucketSizes[5] == 0);
  ASSERT_TRUE(bucketSizes[6] == 0);
  ASSERT_TRUE(bucketSizes[7] == 0);
  ASSERT_TRUE(bucketSizes[8] == 0);
  ASSERT_TRUE(bucketSizes[9] == 0);
  ASSERT_TRUE(bucketSizes[10] == 0);
  ASSERT_TRUE(bucketSizes[11] == 0);
  ASSERT_TRUE(bucketSizes[12] == 1);
    
  ASSERT_TRUE(true);
}











