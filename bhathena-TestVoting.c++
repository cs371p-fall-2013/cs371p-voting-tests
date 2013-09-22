
using namespace std;
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"
// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read_1) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n");
    int i;
	string j;
    string k;
	string test_j = "John Doe\nJane Smith\nSirhan Sirhan\n";
	string test_k = "1\n2\n3\n";
    const bool b = voting_read(r, i, j,k);
	cout << "K STRING " << k << "\n";
	ASSERT_TRUE(b == 1);
    ASSERT_TRUE(i == 3);
    ASSERT_TRUE(j.compare(test_j) == 0);
	ASSERT_TRUE(k.compare(test_k) == 0);
}

TEST(Voting, read_2) {
    std::istringstream r("1\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n");
    int i;
    string j;
    string k;
    string test_j = "John Doe\nJane Smith\nSirhan Sirhan\n";
    const bool b = voting_read(r, i, j,k);
    ASSERT_TRUE(b != 0);
}

TEST(Voting, read_3) {
    std::istringstream r("1\nJonny Boy Joe\n1\n");
    int i;
    string j;
    string k;
    string test_j = "Jonny Boy Joe\n";
	string test_k = "1\n";
    const bool b = voting_read(r, i, j,k);
    ASSERT_TRUE(b == 1);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j.compare(test_j) == 0 );
	ASSERT_TRUE(k.compare(test_k) == 0);
}

// ----
// eval
// ----

TEST(Voting, eval_1) {
    const string v = voting_eval(1, "Joe\n", "1\n");
	string test_v = "Joe\n";
	cout << v << "\n";
    ASSERT_TRUE(v.compare(test_v) == 0);
}

TEST(Voting, eval_2) {
    const string v = voting_eval(2, "Joe\n\n","1\n2\n");
	cout << v <<"\n";
    string test_v = "Joe\n";
    ASSERT_TRUE(v.compare(test_v) == 0);
}

TEST(Voting, eval_3) {
    const string v = voting_eval(1, "Joe", "1\n1\n1\n1\n1\n1\n1\n1\n1\n");
    string test_v = "Joe\n";
    ASSERT_TRUE(v.compare(test_v) == 0);
}

// -----
// print
// -----

TEST(Voting, print_1) {
    std::ostringstream w;
    voting_print(w, "Joe");
    ASSERT_TRUE(w.str() == "Joe");
}

TEST(Voting, print_2) {
    std::ostringstream w;
    voting_print(w, "Joe Phil Bob\nJerry\n");
    ASSERT_TRUE(w.str() == "Joe Phil Bob\nJerry\n");
}

TEST(Voting, print_3) {
    std::ostringstream w;
    voting_print(w, "Joeseph Joe");
    ASSERT_TRUE(w.str() == "Joeseph Joe");
}


// -----
// solve
// -----

TEST(Voting, solve_1) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, solve_2) {
    std::istringstream r("2\n\n1\nJon\n1\n\n1\n\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    cout<< "START" << w.str() << "END\n";
	ASSERT_TRUE(w.str() == "Jon\n\n");
}

TEST(Voting, solve_3) {
    std::istringstream r("1\n\n3\nJoe\nPhil\na\n3 2 1\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
	
    ASSERT_TRUE(w.str() == "a\n");
}
