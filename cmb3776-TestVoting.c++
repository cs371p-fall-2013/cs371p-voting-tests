// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;

// -----------
// voting_read
// -----------

TEST(Voting, read_1) {
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhann\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1");          
    int iterators[20];
    string candidates[20];
    string ballots[20][1000];
    int num_candidates;
    int num_ballots;
    voting_read(r, iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(3, num_candidates);
    ASSERT_EQ(5, num_ballots);
    ASSERT_NE(iterators[0], 0);
    ASSERT_EQ(iterators[0], 2);
    ASSERT_EQ(iterators[1], 2);
    ASSERT_EQ(iterators[2], 1);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

TEST(Voting, read_2) {
    istringstream r("1\nJohn Done\n1");          
    int iterators[20];
    string candidates[20];
    string ballots[20][1000];
    int num_candidates;
    int num_ballots;
    voting_read(r, iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(1, num_candidates);
    ASSERT_EQ(1, num_ballots);
    ASSERT_NE(iterators[0], 0);
    ASSERT_EQ(iterators[0], 1);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

TEST(Voting, read_3) {
    istringstream r("10\nOne\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nJohn\n10 1 2 3 4 5 6 7 8 9\n1 2 3 4 5 6 7 8 9 10\n10 2 3 4 5 6 7 8 9 1");          
    int iterators[20];
    string candidates[20];
    string ballots[20][1000];
    int num_candidates;
    int num_ballots;
    voting_read(r, iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(10, num_candidates);
    ASSERT_EQ(3, num_ballots);
    ASSERT_NE(iterators[0], 0);
    ASSERT_EQ(iterators[0], 1);
    ASSERT_EQ(iterators[9], 2);
    ASSERT_NE(candidates[num_candidates-1], "");
    ASSERT_EQ(candidates[num_candidates], "");
}

// -----------
// voting_eval
// -----------

TEST(Voting, eval_1) {
    int iterators[20];
    iterators[0] = 0;
    iterators[1] = 1;
    string candidates[20];
    int x = 0;
    for(char ch = 'A'; ch < 'C'; ch++){
        candidates[x] = ch;
        x++;
    }
    string ballots[20][1000];
    ballots[1][0] = string("2 1");
    int num_candidates = 2;
    int num_ballots = 1;
    string result = voting_eval(iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(result, "B");
}

TEST(Voting, eval_2) {
    int iterators[20];
    iterators[0] = 0;
    iterators[1] = 2;
    string candidates[20];
    int x = 0;
    for(char ch = 'A'; ch < 'C'; ch++){
        candidates[x] = ch;
        x++;
    }
    string ballots[20][1000];
    ballots[1][0] = string("2 1");
    ballots[1][1] = string("2 1");
    int num_candidates = 2;
    int num_ballots = 2;
    string result = voting_eval(iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(result, "B");
}

TEST(Voting, eval_3) {
    int iterators[20];
    iterators[0] = 1000;
    string candidates[20];
    candidates[0] = 'A';
    string ballots[20][1000];
    for(int i = 0; i < 1000; i++)
        ballots[0][i] = string("1");
    int num_candidates = 1;
    int num_ballots = 1000;
    string result = voting_eval(iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(result, "A");
}

TEST(Voting, eval_4) {
    int iterators[20];
    iterators[0] = 2;
    iterators[1] = 2;
    iterators[2] = 1;
    string candidates[20];
    int x = 0;
    for(char ch = 'A'; ch < 'D'; ch++){
        candidates[x] = ch;
        x++;
    }
    string ballots[20][1000];
    ballots[0][0] = string("1 2 3");
    ballots[1][0] = string("2 1 3");
    ballots[1][1] = string("2 3 1");
    ballots[0][1] = string("1 2 3");
    ballots[2][0] = string("3 1 2");
    int num_candidates = 3;
    int num_ballots = 5;
    string result = voting_eval(iterators, candidates, ballots, num_candidates, num_ballots);
    ASSERT_EQ(result, "A");
}

// ------------
// voting_solve
// ------------

TEST(Voting, solve_1) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe\n");
}

TEST(Voting, solve_2) {
    istringstream r("1\n\n1\nJohn Doe\n1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe\n");
}

TEST(Voting, solve_3) {
    istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n2 1\n1 2\n1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ(w.str(), "John Doe\n");
}

// ------------
// voting_print
// ------------
TEST(Voting, print_1) {
    ostringstream w;
    voting_print(w, "John Doe");
    ASSERT_EQ("John Doe", w.str());
}

TEST(Voting, print_2) {
    ostringstream w;
    voting_print(w, "John Doe\nJane Doe");
    ASSERT_EQ("John Doe\nJane Doe", w.str());
}
