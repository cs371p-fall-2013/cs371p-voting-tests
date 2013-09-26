
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

% valgrind TestVoting > TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

//voting_read_numcandidates
TEST(voting_read_numcandidates, readnum1) {
    std::istringstream r("5\n");
    int i;
    const bool b = voting_read_numcandidates(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5);
}
TEST(voting_read_numcandidates, readnum2) {
    std::istringstream r("19\n");
    int i;
    const bool b = voting_read_numcandidates(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 19);
}

TEST(voting_read_numcandidates, readnum3) {
    std::istringstream r("1\n");
    int i;
    const bool b = voting_read_numcandidates(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
}
TEST(voting_read_numcandidates, readnum4) {
    std::istringstream r("4\n");
    int i;
    const bool b = voting_read_numcandidates(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 4);
}

TEST(voting_read_names, readnames1) {
    std::istringstream r("Dave\njffff\nguy\n");
    int num= 3;
    char testread [3][MAX_NAME_LENGTH];
    const bool b = voting_read_names(r,testread,num);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(strcmp(testread[0],"Dave")==0);
    ASSERT_TRUE(strcmp(testread[1],"jffff")==0);
    ASSERT_TRUE(strcmp(testread[2],"guy")==0);
}

TEST(voting_read_names, readnames2) {
    std::istringstream r("HIII\n");
    int num= 1;
    char testread [1][MAX_NAME_LENGTH];
    const bool b = voting_read_names(r,testread,num);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(strcmp(testread[0],"HIII")==0);
}


TEST(voting_read_names, readnames3) {
    std::istringstream r("a\nb\nc\nd\nABCD\n");
    int num= 5;
    char testread [5][MAX_NAME_LENGTH];
    const bool b = voting_read_names(r,testread,num);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(strcmp(testread[0],"a")==0);
    ASSERT_TRUE(strcmp(testread[1],"b")==0);
    ASSERT_TRUE(strcmp(testread[2],"c")==0);
    ASSERT_TRUE(strcmp(testread[3],"d")==0);
    ASSERT_TRUE(strcmp(testread[4],"ABCD")==0);
}

// voting_solve
TEST(voting_solve, solve1) {
    std::istringstream r("1\n\n2\njohn\njane\n1 2\n1 2\n");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_TRUE(w.str()=="john\n");
}

TEST(voting_solve, solve2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_TRUE(w.str()=="John Doe\n");
}

TEST(voting_solve, solve3) {
    std::istringstream r("1\n\n2\nBob\nBill\n");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_TRUE(w.str()=="Bob\nBill\n");
}

//check_winner_tie
//(int ballots[MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES], vector<int> candidate_bucket_[MAX_NUM_CANDIDATES],int candidate_lost_[MAX_NUM_CANDIDATES], int numcandidates, int numballots)
TEST(check_winner_tie, cwt1)
{
  int ballots [MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES] ={{1,2,3}, 
                                                      {1,2,3}, 
                                                      {1,2,3}};
  vector<int> candidate_bucket_[MAX_NUM_CANDIDATES];
  candidate_bucket_[0].push_back(0);
  candidate_bucket_[0].push_back(1);
  candidate_bucket_[0].push_back(2);
  int candidate_lost_[MAX_NUM_CANDIDATES]={0};
  int numcandidates= 3;
  int numballots = 3;
  vector<int> winners = check_winner_tie(ballots,candidate_bucket_,candidate_lost_,numcandidates,numballots);
  ASSERT_TRUE((int)winners.size()==1);
  ASSERT_TRUE(winners.at(0)==0);
  
}
TEST(check_winner_tie, cwt2)
{
  int ballots [MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES] ={{1,2,3}, 
                                                      {2,1,3}, 
                                                      };
  vector<int> candidate_bucket_[MAX_NUM_CANDIDATES];
  candidate_bucket_[0].push_back(0);
  candidate_bucket_[1].push_back(1);
  int candidate_lost_[MAX_NUM_CANDIDATES]={0};
  int numcandidates= 3;
  int numballots = 2;
  vector<int> winners = check_winner_tie(ballots,candidate_bucket_,candidate_lost_,numcandidates,numballots);
  ASSERT_TRUE((int)winners.size()==2);
  ASSERT_TRUE(winners.at(0)==0);
  ASSERT_TRUE(winners.at(1)==1);
  
}
TEST(check_winner_tie, cwt3)
{
  int ballots [MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES] ={{2,1,3},  
                                                      };
  vector<int> candidate_bucket_[MAX_NUM_CANDIDATES];
  candidate_bucket_[1].push_back(0);
  int candidate_lost_[MAX_NUM_CANDIDATES]={0};
  int numcandidates= 3;
  int numballots = 1;
  vector<int> winners = check_winner_tie(ballots,candidate_bucket_,candidate_lost_,numcandidates,numballots);
  ASSERT_TRUE((int)winners.size()==1);
  ASSERT_TRUE(winners.at(0)==1);
  
}

TEST(run_election, election1) {
    std::istringstream r("2\njohn\njane\n1 2\n1 2\n");
    std::ostringstream w;
    run_election(r,w);
    ASSERT_TRUE(w.str()=="john\n");
}

TEST(run_election, election2) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    std::ostringstream w;
    run_election(r,w);
    ASSERT_TRUE(w.str()=="John Doe\n");
}

TEST(run_election, election3) {
    std::istringstream r("2\nBob\nBill\n");
    std::ostringstream w;
    run_election(r,w);
    ASSERT_TRUE(w.str()=="Bob\nBill\n");
}

//vector<int> run_iteration(int ballots[MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES], vector<int> candidate_bucket_[MAX_NUM_CANDIDATES], int candidate_lost_[MAX_NUM_CANDIDATES], int numcandidates, int numballots)
TEST(run_iteration, runiteration1)
{
  int ballots [MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES] ={{1,2,3}, 
                                                      {1,2,3}, 
                                                      {1,2,3}};
  vector<int> candidate_bucket_[MAX_NUM_CANDIDATES];
  candidate_bucket_[0].push_back(0);
  candidate_bucket_[0].push_back(1);
  candidate_bucket_[0].push_back(2);
  int candidate_lost_[MAX_NUM_CANDIDATES]={0};
  int numcandidates= 3;
  int numballots = 3;
  vector<int> winners = run_iteration(ballots,candidate_bucket_,candidate_lost_,numcandidates,numballots);
  ASSERT_TRUE((int)winners.size()==1);
  ASSERT_TRUE(winners.at(0)==0);
  
}

TEST(run_iteration, runiteration2)
{
  int ballots [MAX_NUM_BALLOTS][MAX_NUM_CANDIDATES] ={{1,2,3}, 
                                                      {2,1,3}, 
                                                      {3,2,1},
                                                      {1,2,3}};
  vector<int> candidate_bucket_[MAX_NUM_CANDIDATES];
  candidate_bucket_[0].push_back(0);
  candidate_bucket_[0].push_back(3);
  candidate_bucket_[1].push_back(1);
  candidate_bucket_[2].push_back(2);
  int candidate_lost_[MAX_NUM_CANDIDATES]={0};
  int numcandidates= 3;
  int numballots = 4;
  vector<int> winners = run_iteration(ballots,candidate_bucket_,candidate_lost_,numcandidates,numballots);
  ASSERT_TRUE((int)winners.size()==0); 
}

TEST(voting_read_ballots, readballots_noballots) {
    std::istringstream r("\n");
    int ballots[1000][20] = {{0}};
    int compareBallots[1000][20] = {{0}};
    int numCandidates = 3;
    int numballots = 0;
    

    bool response = voting_read_ballots(r, ballots, numCandidates, numballots);
    ASSERT_TRUE(response==true);
    ASSERT_TRUE(numballots==0);
    ASSERT_TRUE(ballots[0][0]==compareBallots[0][0]);
}

TEST(voting_read_ballots, readballots_1) {
    std::istringstream r("1 2 3\n1 3 2\n");
    int ballotChecker[1000][20] =
    {
       {0,1,2},
       {0,2,1}
    };
    int ballots[1000][20] = 
    {
       {0}
    };
    int numCandidates = 3;
    int numballots = 0;
    

    bool response = voting_read_ballots(r, ballots, numCandidates, numballots);
    ASSERT_TRUE(response==true);

    ASSERT_TRUE( ballotChecker[0][0]==ballots[0][0] && 
                 ballotChecker[0][1]==ballots[0][1] &&
                 ballotChecker[0][2]==ballots[0][2] &&

                 ballotChecker[0][0]==ballots[0][0] &&
                 ballotChecker[0][1]==ballots[0][1] &&
                 ballotChecker[0][2]==ballots[0][2]);
    
}

TEST(voting_read_ballots, readballots_2) {
    std::istringstream r("1\n");
    int ballotsCompare[1000][20] =
    {
       {0}
    };
    int ballots[1000][20] =
    {
       {0}
    };
    int numCandidates = 1;
    int numballots = 1;
    

    bool response = voting_read_ballots(r, ballots, numCandidates, numballots);
    ASSERT_TRUE(response==true);
    ASSERT_TRUE(ballotsCompare[0][0]==ballots[0][0]);
}


TEST(find_winners, findwinners_winner){
   int ballot[1000][20] =
    {
       {0,1,2},
       {0,2,1}
    };
   int numcandidates = 3;
   int numballots = 2;

   vector<int> answer = find_winners(ballot, numcandidates, numballots);
   ASSERT_TRUE( (int)answer.size()==1);
   ASSERT_TRUE( answer.at(0) == 0 );
}

TEST(find_winners, findwinners_tie){
   int ballot[1000][20] =
    {
       {0,1,2},
       {0,2,1},
       {2,0,1},
       {2,0,1}
    };
   int numcandidates = 3;
   int numballots = 4;

   vector<int> answer = find_winners(ballot, numcandidates, numballots);
   ASSERT_TRUE( (int)answer.size()==2);
   ASSERT_TRUE( answer.at(0) == 0 && answer.at(1) == 2 );
}

TEST(find_winners, findwinners_none){
   int ballot[1000][20] =
    {
       {0,1,2},
       {2,1,0},
       {1,2,0},
       {1,0,2}
    };
   int numcandidates = 3;
   int numballots = 4;

   vector<int> answer = find_winners(ballot, numcandidates, numballots);
   ASSERT_TRUE( (int)answer.size()==1 );
   ASSERT_TRUE( answer.at(0)==1 );
}


/*

// ----
// eval
// ----

TEST(CollatzEval, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(CollatzEval, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(CollatzEval, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(CollatzEval, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}
    
TEST(CollatzEval, eval_5) {
    const int v = collatz_eval(1000, 900);
    ASSERT_TRUE(v == 174);}  
    
TEST(CollatzEval, eval_6) {
    const int v = collatz_eval(999999, 999990);
    ASSERT_TRUE(v == 259);}   
    
TEST(CollatzEval, eval_7) {
    const int v = collatz_eval(10, 25);
    ASSERT_TRUE(v == 21);}  

// -----
// print
// -----

TEST(Collatzprint, defaultprint) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatzprint, simpleprint) {
    std::ostringstream w;
    collatz_print(w, 1, 2, 3);
    ASSERT_TRUE(w.str() == "1 2 3\n");}
    
TEST(Collatzprint, reversedSimpleprint) {
    std::ostringstream w;
    collatz_print(w, 3, 2, 1);
    ASSERT_TRUE(w.str() == "3 2 1\n");}
    
TEST(Collatzprint, bigNumbers) {
    std::ostringstream w;
    collatz_print(w, 12345, 98765, 43210);
    ASSERT_TRUE(w.str() == "12345 98765 43210\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
 TEST(Collatz, solve2) {
    std::istringstream r("3 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "3 10 20\n");}

TEST(Collatz, solve3) {
    std::istringstream r("8239 2971\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8239 2971 262\n");}
    
TEST(Collatz, solve4) {
    std::istringstream r("7639 11696\n3427 1280\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "7639 11696 268\n3427 1280 217\n");}
    */
