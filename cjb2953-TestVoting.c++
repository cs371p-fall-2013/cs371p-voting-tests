//includes
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"


#include "Voting.h"

// -----
// print
// -----


TEST(Voting, print) {
    std::ostringstream w;
    string names [maxcandidates];
    names[0] = "Hello";
    voting_print(w, names);
    ASSERT_TRUE(w.str() == "Hello\n");}

TEST(Voting, print2) {
std::ostringstream w;
string names [maxcandidates];
names[0] = "Carl Bai";
voting_print(w, names);
ASSERT_TRUE(w.str() == "Carl Bai\n");}

TEST(Voting, print3) {
std::ostringstream w;
string names [maxcandidates];
names[0] = "";
voting_print(w, names);
ASSERT_TRUE(w.str() == "");}

TEST(Voting, print4) {
std::ostringstream w;
string names [maxcandidates];
names[0] = " ";
voting_print(w, names);
ASSERT_TRUE(w.str() == " \n");}


//isLoser
TEST(Voting, isloser)
{
	int numberofvotes[maxcandidates];
	numberofvotes[0] = 1;
	int loservote = 1;
	int losers[maxcandidates];
	losers[0] = 21;
	isloser(numberofvotes, loservote, losers);
	ASSERT_TRUE(numberofvotes[0] == 1);
}

TEST(Voting, isloser2)
{
	int numberofvotes[maxcandidates];
	numberofvotes[0] = 1;
	int loservote = 1;
	int losers[maxcandidates];
	losers[0] = 21;
	isloser(numberofvotes, loservote, losers);
	ASSERT_TRUE(loservote == 1);
}

TEST(Voting, isloser3)
{
	int numberofvotes[maxcandidates];
	numberofvotes[0] = 1;
	int loservote = 1;
	int losers[maxcandidates];
	losers[0] = 21;
	isloser(numberofvotes, loservote, losers);
	ASSERT_TRUE(losers[0] == 21);
}



TEST(Voting, solve) {
    std::istringstream r("1\n\n1\nCarl Bai");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Carl Bai\n");}

TEST(Voting, solve2) {
    std::istringstream r("1\n\n2\nCarl Bai\nNavin Ratnayake\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Carl Bai\nNavin Ratnayake\n");}

TEST(Voting, solve3) {
    std::istringstream r("1\n\n2\nCarl Bai\nNavin Ratnayake\n2 1\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "Navin Ratnayake\n");}

TEST(Voting, solve4) {
std::istringstream r("1\n\n2\nCarl Bai\nNavin Ratnayake\n1 2\n");
std::ostringstream w;
voting_solve(r, w);
ASSERT_TRUE(w.str() == "Carl Bai\n");}



TEST(Voting, read)
{
	std::istringstream r;
	string arg[maxcandidates];
	vector < vector< vector<int> > >vec;
    vec = vector<vector<vector<int> > > (20);
	int num_candidates = 10;
	int num_votes = 0;
	voting_read_candidates(r, arg, vec, num_candidates, &num_votes);
	ASSERT_TRUE(num_candidates == 10);
}

TEST(Voting, read2)
{
	std::istringstream r("Carl Bai");
	string arg[maxcandidates];
	vector < vector< vector<int> > >vec;
    vec = vector<vector<vector<int> > > (20);
	int num_candidates = 10;
	int num_votes = 5;
	voting_read_candidates(r, arg, vec, num_candidates, &num_votes);
	ASSERT_TRUE(arg[0] == ("Carl Bai"));
}

TEST(Voting, read3)
{
	std::istringstream r("Carl Bai\nNavin Ratnayake");
	string arg[maxcandidates];
	vector < vector< vector<int> > >vec;
    vec = vector<vector<vector<int> > > (20);
	int num_candidates = 10;
	int num_votes = 5;
	voting_read_candidates(r, arg, vec, num_candidates, &num_votes);
	ASSERT_TRUE(arg[0] == ("Carl Bai"));
}

TEST(Voting, read4)
{
	std::istringstream r("Carl Bai\nNavin Ratnayake");
	string arg[maxcandidates];
	vector < vector< vector<int> > >vec;
    vec = vector<vector<vector<int> > > (20);
	int num_candidates = 10;
	int num_votes = 5;
	voting_read_candidates(r, arg, vec, num_candidates, &num_votes);
	ASSERT_TRUE(arg[1] == ("Navin Ratnayake"));
}
