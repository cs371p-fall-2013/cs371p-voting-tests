
/*
 * TestVoting.c++
 * 
 */

/*
To Test the program:
% g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main
% valgrind TestVoting > TestVoting.out
*/

// includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;


// read
TEST(Voting, read_0) {
	//string ex = "1\n\n2\nRene Trevino\nEnam\n1 2\n1 2\n2 1\n";
    //!! Above line breaks, because voting_read cannot handle election count (unlike voting_solve)
	
    string ex = "2\nRene Trevino\nEnam\n1 2\n1 2\n2 1\n";
    std::istringstream r(ex);

	string names [20];
    vector<deque<int>> vect(5);

	//int tcnt = 0;  as above, cannot measure elections_counts with voting_read :)
	int ccnt = 0;
    int vcnt = 0;
	bool v = voting_read(r, vcnt, ccnt, names, vect);
	ASSERT_TRUE(v == true);
	ASSERT_TRUE(vcnt == 3);
	ASSERT_TRUE(ccnt == 2);
	

}

TEST(Voting, read_1) {

    string ex = "3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n"; 

    std::istringstream r(ex);

    string names [20];
    vector<deque<int>> vect(30);

    int ccnt = 0;
    int vcnt = 0;
    
    bool v = voting_read(r, vcnt, ccnt, names, vect);
    
    ASSERT_TRUE(v == true);
    ASSERT_TRUE(ccnt == 3);
    ASSERT_TRUE(vcnt == 5);
}

TEST(Voting, read_2) {

    string ex = "3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    std::istringstream r2(ex);

    string s [20];
    vector<deque<int>> vect(5);   

    int ccnt = 7;
    int vcnt = 9;

    bool v1 = voting_read(r2, vcnt, ccnt, s, vect);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(vcnt == 5);
    ASSERT_TRUE(ccnt == 3);
}


TEST(Voting, read_3) {

    string ex = "4\nJohn Doe\nJane Smith\nAizhuldyz G\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    std::istringstream r2(ex);

    string s [20];
    vector<deque<int>> vect(5);   

    int ccnt = 17;
    int vcnt = 99;

    bool v1 = voting_read(r2, vcnt, ccnt, s, vect);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(vcnt == 5);
    ASSERT_TRUE(ccnt == 4);
}


TEST(Voting, read_4) {

    string ex = "3\nGlenn Downing\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    std::istringstream r2(ex);

    string s [20];
    vector<deque<int>> vect(5);   

    int ccnt = -2;
    int vcnt = -8;

    bool v1 = voting_read(r2, vcnt, ccnt, s, vect);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(vcnt == 5);
    ASSERT_TRUE(ccnt == 3);
}


TEST(Voting, read_5) {

    string ex = "3\nMiley Cirus\nWill Smith\nRobin Thicke\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    std::istringstream r2(ex);

    string s [20];
    vector<deque<int>> vect(5);   

    int ccnt = 7;
    int vcnt = 9;

    bool v1 = voting_read(r2, vcnt, ccnt, s, vect);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(vcnt == 5);
    ASSERT_TRUE(ccnt == 3);
}

TEST(Voting, solve_0) {
    istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    ostringstream w;

    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Smith\n");  
}

TEST(Voting, solve_1) {
    istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n2 1 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    ostringstream w;

    voting_solve(r,w);

ASSERT_TRUE(w.str() == "John Smith\n");  
}
TEST(Voting, solve_2) {
    istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    ostringstream w;
    voting_solve(r,w);
    ASSERT_TRUE(w.str() == "John Smith\n");  
}

TEST(Voting, solve_3)
{
    istringstream r("1\n\n1\na\n1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\n");
}


TEST(Voting, solve_4)
{
    istringstream r("1\n\n2\na\nb\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\nb\n");
}

TEST(Voting, solve_multiple_elections)       
{
    istringstream r("2\n\n1\na\n1\n\n2\na\nb\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "a\n\na\nb\n");
}

TEST(Voting, voting_solve_normal) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}


TEST(Voting, voting_solve_recount) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}


TEST(Voting, voting_solve_tie) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n3 2 1\n");
    ostringstream w;
    voting_solve(r, w);
    // cout << w.str();
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
}


TEST(Voting, voting_solve_two_vote) {
    istringstream r("1\n\n7\nBarack Obama\nyou\nJim Carey\nJake Gellenhall\nMariah Carey\nJim\ngucci\n2 6 1 5 3 7 4\n6 7 2 4 5 3 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "you\nJim\n");
}


TEST(Voting, voting_solve_long_case) {
    istringstream r("1\n\n10\nyou\nJim\ngucci\nHillary Clinton\nGlenn Downing\nMadonna\nMariah Carey\ncandidate0\nJim Carey\nJake Gellenhall\n4 6 9 1 7 5 3 2 8 10\n3 4 9 5 1 10 7 6 2 8\n9 4 8 1 3 2 7 6 5 10\n9 2 4 3 1 5 6 7 8 10\n2 8 4 5 10 9 7 6 1 3\n8 2 4 9 3 10 7 6 1 5\n1 6 5 9 4 8 7 2 3 10\n7 6 4 8 1 3 10 9 5 2\n5 1 8 9 4 7 10 2 6 3\n6 10 8 4 1 3 2 9 5 7\n7 10 1 3 6 4 8 5 2 9\n6 10 5 1 3 2 7 8 9 4\n7 4 9 10 8 5 1 2 3 6\n10 9 2 7 8 5 3 6 1 4\n9 6 4 2 3 10 8 1 5 7\n2 10 4 8 6 3 9 5 1 7\n1 6 5 4 3 10 7 2 8 9\n1 7 6 3 4 9 8 10 5 2\n");
    ostringstream w;
    voting_solve(r, w);
    //   cout << w.str();
    ASSERT_TRUE(w.str() == "Jim Carey\n");
}


TEST(Voting, voting_solve_another_long_case) {
    istringstream r("1\n\n8\nyou\nGlenn Downing\nJim Carey\ncandidate0\ngucci\nJake Gellenhall\nHillary Clinton\nBarack Obama\n3 2 8 7 6 4 5 1\n7 2 1 3 4 5 6 8\n5 3 2 8 1 7 4 6\n4 2 8 5 7 6 1 3\n3 8 5 4 7 6 1 2\n8 6 2 7 5 3 4 1\n7 4 8 2 3 1 6 5\n8 1 3 7 5 4 2 6\n1 8 2 3 6 7 5 4\n6 5 2 8 4 3 7 1\n4 8 7 3 1 6 5 2\n2 3 5 1 7 4 8 6\n8 6 1 5 7 4 2 3\n7 8 5 2 3 4 1 6\n7 8 5 3 2 6 4 1\n");
    ostringstream w;
    voting_solve(r, w);
    //   cout << w.str();
    ASSERT_TRUE(w.str() == "Barack Obama\n");
}
