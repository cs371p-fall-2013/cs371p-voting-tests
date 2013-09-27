// --------------------------------
// TestVoting.c++
// Copyright (C) 2013
// Vivek Karuturi Qunvar Arora
// --------------------------------

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

using namespace std;

// -----------
// TestVoting
// -----------

//TestRead

TEST(Voting, voting_read) {
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 3);
}

TEST(Voting, voting_read2) {
	istringstream r("2\nAllen Iverson\nKevin Durant\n1 2\n2 1\n2 1\n1 2\n1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 2);
}

TEST(Voting, voting_read3) {
	istringstream r("3\nRobert Griffin\nBill Cosby\nJames Brown\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 3);
}

TEST(Voting, voting_read4) {
	istringstream r("2\n50 cent\nKanye West\n1 2 \n2 1 \n2 1\n1 2\n1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 2);
}

TEST(Voting, voting_read5) {
	istringstream r("3\nMack Brown\nNick Saban\nUrban Meyer\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 3);
}

TEST(Voting, voting_bob) {
	istringstream r("2\nChance TheRapper\nChief Keef\n1 2\n2 1\n2 1\n1 2\n1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 2);
}

TEST(Voting, voting_bob2) {
	istringstream r("3\nFamous Amos\nMike nIke\nMike Tyson\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 3);
}

TEST(Voting, voting_bob3) {
	istringstream r("2\nVivek Karutur\nQunvar Arora\n1 2\n2 1\n2 1\n1 2\n1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 2);
}

TEST(Voting, voting_bob4) {
	istringstream r("3\nJohnny Manziel\nJameis Winston\nAuntie Ann\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int b;
	r >> b;
	ASSERT_TRUE(b == 3);
}

/*TEST(Voting, voting_read){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	ostringstream w;
	int num_cases = 1;
	int num_candidates = 3;
	const bool b = voting_read(r, w)
	const bool b = voting_read(r, w)
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(num_cases == 1);
}

TEST(Voting, voting_read){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	ostringstream w;
	int num_cases = 1;
	int num_candidates = 3;
	const bool b = voting_read(r, w)
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(num_candidates == 3);
}*/

/*TEST(Voting, voting_read){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_cases = 1;
	int num_candidates = 3;
	const bool b = voting_read(r, w)
	ASSERT_TRUE(b == true);
}

TEST(Voting, voting_read){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_cases = 1;
	int num_candidates = 3;
	const bool b = voting_read(r, w)
	const bool b = voting_read(r, w)
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(num_cases == 1);
}

TEST(Voting, voting_read){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_cases = 1;
	int num_candidates = 3;
	const bool b = voting_read(r, w)
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(num_candidates == 3);
}
*/

/*TEST(Voting, voting_extract){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_candidates = 3;
	string str1 = "John Doe";
	Election election = voting_extract(r, 3);
	ASSERT_TRUE(election.can[0].name.compare(str1)==0);

}

TEST(Voting, voting_extract){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_candidates = 3;
	string str1 = "Jane Smith";
	Election election = voting_extract(r, 3);
	ASSERT_TRUE(election.can[1].name.compare(str1)==0);

}*/

/*TEST(Voting, voting_extract){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	int num_candidates = 3;
	string str1 = "Sirhan Sirhan";
	Election election = voting_extract(r, 3);
	ASSERT_TRUE(election.can[2].vsize == 2);

}*/





