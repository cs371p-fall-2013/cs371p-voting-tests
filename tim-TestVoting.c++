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

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

TEST(Voting, voting_read_number_of_candidates1) {
	istringstream r("\n1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}
TEST(Voting, voting_read_number_of_candidates2) {
	istringstream r("\n2\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 2);
}TEST(Voting, voting_read_number_of_candidates3) {
	istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 3);
}TEST(Voting, voting_read_number_of_candidates4) {
	istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 4);
}TEST(Voting, voting_read_number_of_candidates5) {
	istringstream r("\n5\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 5);
}TEST(Voting, voting_read_number_of_candidates6) {
	istringstream r("\n6\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 6);
}TEST(Voting, voting_read_number_of_candidates7) {
	istringstream r("\n7\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 7);
}TEST(Voting, voting_read_number_of_candidates8) {
	istringstream r("\n8\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 8);
}TEST(Voting, voting_read_number_of_candidates9) {
	istringstream r("\n9\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 9);
}TEST(Voting, voting_read_number_of_candidates10) {
	istringstream r("\n10\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 10);
}TEST(Voting, voting_read_number_of_candidates11) {
	istringstream r("\n11\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 11);
}TEST(Voting, voting_read_number_of_candidates12) {
	istringstream r("\n12\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 12);
}TEST(Voting, voting_read_number_of_candidates13) {
	istringstream r("\n13\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 13);
}TEST(Voting, voting_read_number_of_candidates14) {
	istringstream r("\n14\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 14);
}TEST(Voting, voting_read_number_of_candidates15) {
	istringstream r("\n15\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 15);
}TEST(Voting, voting_read_number_of_candidates16) {
	istringstream r("\n16\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 16);
}TEST(Voting, voting_read_number_of_candidates17) {
	istringstream r("\n17\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 17);
}TEST(Voting, voting_read_number_of_candidates18) {
	istringstream r("\n18\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 18);
}TEST(Voting, voting_read_number_of_candidates19) {
	istringstream r("\n19\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 19);
}TEST(Voting, voting_read_number_of_candidates20) {
	istringstream r("\n\n1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}TEST(Voting, voting_read_number_of_candidates21) {
	istringstream r("\n\n\n\n1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}TEST(Voting, voting_read_number_of_candidates22) {
	istringstream r("\n\n\n\n\n\n\n\n\n\n\n1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}TEST(Voting, voting_read_number_of_candidates23) {
	istringstream r("\n\n\n\n\n\n\n\n\n\n\n\n\n1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}TEST(Voting, voting_read_number_of_candidates24) {
	istringstream r("1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 1);
}TEST(Voting, voting_read_number_of_candidates25) {
	istringstream r("\n\n\n2\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 2);
}TEST(Voting, voting_read_number_of_candidates26) {
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b = voting_read_number_of_candidates(r);
	ASSERT_TRUE(b == 3);
}