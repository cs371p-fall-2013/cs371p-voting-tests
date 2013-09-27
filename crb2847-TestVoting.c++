#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"

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

// ----
// read
// ----
TEST(Voting, read_1) {
    std::istringstream r("1\n");
    int i;
    const bool b = voting_read(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);}

TEST(Voting, read_2) {
    std::istringstream r("2\n");
    int i;
    const bool b = voting_read(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    2);}

TEST(Voting, read_3) {
    std::istringstream r("3\n");
    int i;
    const bool b = voting_read(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    3);}


TEST(Voting, readBallots_1) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 3;
    std::string r = "1 2 3";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}

TEST(Voting, readBallots_2) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 3;
    std::string r = "2 1 3";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}

TEST(Voting, readBallots_3) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 3;
    std::string r = "3 2 1";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}

TEST(Voting, readBallots_4) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 5;
    std::string r = "1 2 3 4 5";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}

TEST(Voting, readBallots_5) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 6;
    std::string r = "1 2 3 4 5 6";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}

TEST(Voting, readBallots_6) {
    //std::istringstream r("3 2 1\n");
    int numCandidates = 7;
    std::string r = "1 2 3 4 5 6 7";
    //for(int x=0; x<1000; x++)for(int j=0; j<21; j++){{ballots[x][j] = 0;}}
    const bool b = voting_read(r, numCandidates, 0);
    ASSERT_TRUE(b == true);}





TEST(Voting, readStrings){
    std::istringstream r("John Doe\n");
    std::string s;
    const bool b = voting_read(r, s);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(s =="John Doe");}

TEST(Voting, readStrings_2){
    std::istringstream r("Chris Bentson\n");
    std::string s;
    const bool b = voting_read(r, s);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(s =="Chris Bentson");}

TEST(Voting, readStrings_3){
    std::istringstream r("Calvin Lau\n");
    std::string s;
    const bool b = voting_read(r, s);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(s =="Calvin Lau");}

TEST(Voting, readStrings_4){
    std::istringstream r("Rick James\n");
    std::string s;
    const bool b = voting_read(r, s);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(s =="Rick James");}

TEST(Voting, readStrings_5){
    std::istringstream r("Clark Kent\n");
    std::string s;
    const bool b = voting_read(r, s);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(s =="Clark Kent");}

TEST(Voting, readStrings_6){
    std::istringstream r("Clark\nBen\n");
    std::string s;
    const bool b = voting_read(r, s);
    std::string n;
    
    const bool c = voting_read(r, n);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(c == true);
    ASSERT_TRUE(s =="Clark");
    ASSERT_TRUE(n =="Ben");}









