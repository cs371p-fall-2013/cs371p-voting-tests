
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
// eval
// ----

TEST(Voting, eval_1) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    string v = voting_eval(r);
    ASSERT_TRUE(v == "John Doe\n");
}
TEST(Voting, eval_2) {
	std::istringstream r("1\nJon\n1\n");
    string v = voting_eval(r);
    ASSERT_TRUE(v == "Jon\n");
}

TEST(Voting, eval_3) {
	std::istringstream r("3\nJoe\nPhil\na\n3 2 1\n3 1 2\n");
    string v = voting_eval(r);
    ASSERT_TRUE(v == "a\n");
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
