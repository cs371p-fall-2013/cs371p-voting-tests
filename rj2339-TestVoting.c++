// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
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

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------


#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <unordered_set>

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, initialize_candidates_1) {
  int candidates[20];
  int num_candidates = 3;
  
  initialize_candidates(candidates, num_candidates);
  ASSERT_TRUE(candidates[0] == 0);
  ASSERT_TRUE(candidates[1] == 0);
  ASSERT_TRUE(candidates[2] == 0);
}

TEST(Voting, initialize_candidates_2) {
  int candidates[20];
  int num_candidates = 5;
  
  initialize_candidates(candidates, num_candidates);
  ASSERT_TRUE(candidates[0] == 0);
  ASSERT_TRUE(candidates[1] == 0);
  ASSERT_TRUE(candidates[2] == 0);
  ASSERT_TRUE(candidates[3] == 0);
  ASSERT_TRUE(candidates[4] == 0);
  
}

TEST(Voting, initialize_candidates_3) {
  int candidates[20];
  int num_candidates = 10;
  
  initialize_candidates(candidates, num_candidates);
  ASSERT_TRUE(candidates[0] == 0);
  ASSERT_TRUE(candidates[1] == 0);
  ASSERT_TRUE(candidates[2] == 0);
  ASSERT_TRUE(candidates[3] == 0);
  ASSERT_TRUE(candidates[4] == 0);
  ASSERT_TRUE(candidates[5] == 0);
  ASSERT_TRUE(candidates[6] == 0);
  ASSERT_TRUE(candidates[7] == 0);
  ASSERT_TRUE(candidates[8] == 0);
  ASSERT_TRUE(candidates[9] == 0);
}

TEST(Voting, initialize_ballots_1) {
  std::list<std::queue<int> > ballot_list[20];
  int num_candidates = 3;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].size() == 0);
  ASSERT_TRUE(ballot_list[1].size() == 0);
  ASSERT_TRUE(ballot_list[2].size() == 0);
}

TEST(Voting, initialize_ballots_2) {
  std::list<std::queue<int> > ballot_list[20];
  int num_candidates = 5;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].size() == 0);
  ASSERT_TRUE(ballot_list[1].size() == 0);
  ASSERT_TRUE(ballot_list[2].size() == 0);
  ASSERT_TRUE(ballot_list[3].size() == 0);
  ASSERT_TRUE(ballot_list[4].size() == 0);  
}

TEST(Voting, initialize_ballots_3) {
  std::list<std::queue<int> > ballot_list[20];
  int num_candidates = 10;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].size() == 0);
  ASSERT_TRUE(ballot_list[1].size() == 0);
  ASSERT_TRUE(ballot_list[2].size() == 0);
  ASSERT_TRUE(ballot_list[3].size() == 0);
  ASSERT_TRUE(ballot_list[4].size() == 0);  
  ASSERT_TRUE(ballot_list[5].size() == 0);
  ASSERT_TRUE(ballot_list[6].size() == 0);
  ASSERT_TRUE(ballot_list[7].size() == 0);
  ASSERT_TRUE(ballot_list[8].size() == 0);
  ASSERT_TRUE(ballot_list[9].size() == 0);  
}

TEST(Voting, find_winners_none) {
  int candidates[] = {2, 1, 2};
  int winners[20];
  initialize_candidates(winners, 3);
  
  bool won = find_winners(winners, candidates, 3, 5);
  
  ASSERT_TRUE(won == false);
}

TEST(Voting, find_winners_tie_1) {
  int candidates[] = {2, 2, 2, 0};
  int winners[20];
  initialize_candidates(winners, 4);
  bool won = find_winners(winners, candidates, 4, 6);
  
  
  ASSERT_TRUE(won == true);
 
  ASSERT_TRUE(winners[0] == 1); 
  ASSERT_TRUE(winners[1] == 1);
  ASSERT_TRUE(winners[2] == 1);

  ASSERT_TRUE(winners[3] == 0);


}

TEST(Voting, find_winners_tie_2) {
  int candidates[] = {0, 2, 2, 2};
  int winners[20];
  initialize_candidates(winners, 4);
  bool won = find_winners(winners, candidates, 4, 6);
  
  ASSERT_TRUE(won == true);
  

  ASSERT_TRUE(winners[0] == 0); 
  ASSERT_TRUE(winners[1] == 1);
  ASSERT_TRUE(winners[2] == 1);
  ASSERT_TRUE(winners[3] == 1);

}

TEST(Voting, find_winners_one) { 
  int candidates[] = {2, 5, 2, 0};
  
  int winners[20];
  initialize_candidates(winners, 4);
  bool won = find_winners(winners, candidates, 4, 9);
  
  ASSERT_TRUE(won == true);
  ASSERT_TRUE(winners[0] == 0); 
  ASSERT_TRUE(winners[1] == 1);
  ASSERT_TRUE(winners[2] == 0);
  ASSERT_TRUE(winners[3] == 0);
}


TEST(Voting, find_losers_1) {
  int candidates[] = {2, 1, 2};
  
  int losers[20];
  initialize_candidates(losers, 3);
  find_losers(losers, candidates, 3);
  
  
  ASSERT_TRUE(losers[0] == 0); 
  ASSERT_TRUE(losers[1] == 1); 
  ASSERT_TRUE(losers[2] == 0); 
  
}

TEST(Voting, find_losers_2) {
  int candidates[] = {1, 1, 3, 3};
  
  int losers[20];
  initialize_candidates(losers, 4);

  find_losers(losers, candidates, 4);
  
  
  ASSERT_TRUE(losers[0] == 1); 
  ASSERT_TRUE(losers[1] == 1); 
  ASSERT_TRUE(losers[2] == 0); 
  ASSERT_TRUE(losers[3] == 0); 
  

  
}

TEST(Voting, find_losers_additional) {
  int candidates[] = {2, 1, 2, 0};
  
  int losers[20];
  initialize_candidates(losers, 4);
  find_losers(losers, candidates, 4);
  

  ASSERT_TRUE(losers[0] == 0); 
  ASSERT_TRUE(losers[1] == 1); 
  ASSERT_TRUE(losers[2] == 0); 
  ASSERT_TRUE(losers[3] == 1); 
  
}





TEST(Voting, solve) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    std::ostringstream w;

    voting_solve(r, w);

    ASSERT_TRUE(w.str() == "John Doe\n");
    }

TEST(Voting, solve_2) {
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    std::ostringstream w;

    voting_solve(r, w);

    ASSERT_TRUE(w.str() == "John Doe\n\nRed\nGreen\n");
    }


TEST(Voting, ballot_read_1) {
    std::queue<int> ballots;

    std::istringstream r("1 2 3");
     
    const bool b = ballot_read(r, ballots);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(ballots.size() == 3);
    ASSERT_TRUE(ballots.front() == 1);
    ballots.pop();
    ASSERT_TRUE(ballots.front() == 2);
    ballots.pop();
    ASSERT_TRUE(ballots.front() == 3);
}

TEST(Voting, ballot_read_2) {
    std::queue<int> ballots;

    std::istringstream r("\n");
     
    const bool b = ballot_read(r, ballots);
    ASSERT_TRUE(b == false);
}

TEST(Voting, ballot_read_3) {
    std::queue<int> ballots;

    std::istringstream r("");
     
    const bool b = ballot_read(r, ballots);
    ASSERT_TRUE(b == false);
}

TEST(Voting, ballot_read_4) {
    std::queue<int> ballots;

    std::istringstream r("EOF");
     
    const bool b = ballot_read(r, ballots);
    ASSERT_TRUE(b == false);   
}

TEST(Voting, read_info_1) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
  
    int candidates[20];
    std::string candidate_names[20];
    //std::queue<int> ballots[1000];    
    int num_candidates;
    int num_ballots;
    std::list<std::queue<int> > ballot_list[20];
    
  
    read_info(r, num_candidates, candidate_names, candidates, ballot_list, num_ballots);
    ASSERT_TRUE(num_candidates == 3);
    ASSERT_TRUE(candidate_names[0] == "John Doe");
    ASSERT_TRUE(candidate_names[2] == "Sirhan Sirhan");  
    
    ASSERT_TRUE(ballot_list[0].size() == 2);
}

TEST(Voting, determine_winner_1) {
    std::ostringstream w;
    int candidates[20];
    std::string candidate_names[20];
    std::queue<int> ballots[1000];     // TODO keep this but lower constant
    int num_candidates = 3;
    int num_ballots = 3; 
    std::list<std::queue<int> > ballot_list[20];
    
    
    candidate_names[0] = "John Doe";
    candidate_names[1] = "Jane Smith";
    candidate_names[2] = "Sirhan Sirhan";
    
    ballots[0].push(1);
    ballots[0].push(2);
    ballots[0].push(3);
    
    ballots[1].push(2);
    ballots[1].push(1);
    ballots[1].push(3);
    
    ballots[2].push(2);
    ballots[2].push(3);
    ballots[2].push(1);
    
    initialize_ballots(ballot_list, 3);

    ballot_list[0].push_front(ballots[0]);
    ballot_list[1].push_front(ballots[1]);
    ballot_list[1].push_front(ballots[1]);
    
    candidates[0] = 1;
    candidates[1] = 2;
    
    determine_winner(w, num_candidates, candidate_names, candidates, ballot_list, num_ballots);

    ASSERT_TRUE(w.str() == "Jane Smith");
} 


TEST(Voting, determine_winner_tie) {
    std::ostringstream w;
    int candidates[20];
    std::string candidate_names[20];
    std::queue<int> ballots[1000];    
    int num_candidates = 4;
    int num_ballots = 6; 
    std::list<std::queue<int> > ballot_list[20];
    
    
    candidate_names[0] = "Red";
    candidate_names[1] = "Green";
    candidate_names[2] = "Blue";
    candidate_names[3] = "Orange";

    ballots[0].push(1);
    ballots[0].push(2);
    ballots[0].push(3);
    ballots[0].push(4);

    ballots[1].push(2); 
    ballots[1].push(1); 
    ballots[1].push(3);
    ballots[1].push(4);

    ballots[2].push(2); 
    ballots[2].push(3);  
    ballots[2].push(1);  
    ballots[2].push(4);

    ballots[3].push(1); 
    ballots[3].push(2);
    ballots[3].push(3);
    ballots[3].push(4);

    ballots[4].push(3); 
    ballots[4].push(4); 
    ballots[4].push(1); 
    ballots[4].push(2);

    ballots[5].push(4);
    ballots[5].push(3);
    ballots[5].push(2); 
    ballots[5].push(1);


    initialize_ballots(ballot_list, 3);

    ballot_list[0].push_front(ballots[0]);
    ballot_list[1].push_front(ballots[1]);
    ballot_list[1].push_front(ballots[2]);
    ballot_list[0].push_front(ballots[3]);
    ballot_list[2].push_front(ballots[4]);
    ballot_list[3].push_front(ballots[5]);
    
    candidates[0] = 2;
    candidates[1] = 2;
    candidates[2] = 1;
    candidates[3] = 1;
    

    determine_winner(w, num_candidates, candidate_names, candidates, ballot_list, num_ballots);

    ASSERT_TRUE(w.str() == "Red\nGreen");

}








TEST(Voting, solve_6) {
	std::istringstream r("1\n\n1\nKyeong Park\n1\n1\n1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n");
}

TEST(Voting, solve_7) {
	std::istringstream r("2\n\n1\nKyeong Park\n1\n1\n1\n\n2\nKyeong Park\nMerrill Davis\n1 2\n2 1\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n\nMerrill Davis\n");
}

TEST(Voting, solve_3) {
	std::istringstream r("3\n\n1\nKyeong Park\n1\n1\n1\n\n2\nKyeong Park\nMerrill Davis\n1 2\n2 1\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Kyeong Park\n\nKyeong Park\nMerrill Davis\n\nJohn\n");
}

TEST(Voting, solve_4) {
	std::istringstream r("2\n\n3\nJohn\nTed\nWill\n3 1 2\n2 1 3\n1 2 3\n3 2 1\n2 3 1\n1 3 2\n\n2\nMack\nKnife\n1 2\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "John\nTed\nWill\n\nMack\nKnife\n");
}

// Tests clear majority and situation where 7/2 = 3.5 so 4 votes should be enough to win
// Also, never ends the last line with an \n
TEST(Voting, solve_5) {
	std::istringstream r("2\n\n3\nFrank\nPete\nTodd\n2 1 3\n1 2 3\n1 3 2\n1 1 2\n\n2\nJim\nCarrey\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1\n2 1");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Frank\n\nCarrey\n");
}

TEST(Voting, print_winners_1) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;
  int winners[20];
  std::string candidate_names[20];
  int num_candidates = 3;
  
  initialize_candidates(winners, num_candidates);
  
  candidate_names[0] = "Bob";
  candidate_names[1] = "Alice";
  candidate_names[2] = "Joe";
  
  winners[1] = 1;
  
  print_winners(w, winners, candidate_names, num_candidates);
  ASSERT_TRUE(w.str() == "Alice");
}

TEST(Voting, print_winners_2) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;
  int winners[20];
  std::string candidate_names[20];
  int num_candidates = 3;
  
  initialize_candidates(winners, num_candidates);
  
  candidate_names[0] = "Bob";
  candidate_names[1] = "Alice";
  candidate_names[2] = "Joe";
  
  winners[0] = 1;
  winners[1] = 1;
  
  
  print_winners(w, winners, candidate_names, num_candidates);
  std::cout << w.str();
  ASSERT_TRUE(w.str() == "Bob\nAlice");
}

TEST(Voting, print_winners_3) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;
  int winners[20];
  std::string candidate_names[20];
  int num_candidates = 3;
  
  initialize_candidates(winners, num_candidates);
  
  candidate_names[0] = "Bob";
  candidate_names[1] = "Alice";
  candidate_names[2] = "Joe";
  
  winners[0] = 1;
  winners[1] = 1;
  winners[2] = 1;
   
  print_winners(w, winners, candidate_names, num_candidates);
  std::cout << w.str();
  ASSERT_TRUE(w.str() == "Bob\nAlice\nJoe");
}





   


    
