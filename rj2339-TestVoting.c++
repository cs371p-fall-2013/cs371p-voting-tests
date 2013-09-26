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


TEST(Candidate, initialize) {
  Candidate c;
  
  c.initialize();
  ASSERT_TRUE(c.name == "");
  ASSERT_TRUE(c.votes == 0);

}

TEST(Voting, initialize_ballots_1) {
  Candidate ballot_list[20];
  int num_candidates = 3;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[1].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[2].ballot_list.size() == 0);
}

TEST(Voting, initialize_ballots_2) {
  Candidate ballot_list[20];
  int num_candidates = 5;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[1].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[2].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[3].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[4].ballot_list.size() == 0);  
}

TEST(Voting, initialize_ballots_3) {
  Candidate ballot_list[20];
  int num_candidates = 10;
  
  initialize_ballots(ballot_list, num_candidates);
  ASSERT_TRUE(ballot_list[0].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[1].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[2].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[3].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[4].ballot_list.size() == 0);  
  ASSERT_TRUE(ballot_list[5].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[6].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[7].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[8].ballot_list.size() == 0);
  ASSERT_TRUE(ballot_list[9].ballot_list.size() == 0);  
}

TEST(Voting, find_winners_none) {
  //int candidates[] = {2, 1, 2};
  Candidate candidates[20];
  
  initialize_ballots(candidates, 3);
  candidates[0].votes = 2;
  candidates[1].votes = 1;
  candidates[2].votes = 2;
  
  bool won = find_winners(candidates, 3, 5);
  
  ASSERT_TRUE(won == false);
}

TEST(Voting, find_winners_tie_1) {
  //int candidates[] = {2, 2, 2, 0};
  Candidate candidates[20];
  initialize_ballots(candidates, 4);
  
  candidates[0].votes = 2;
  candidates[1].votes = 2;
  candidates[2].votes = 2;
  candidates[3].votes = 0;
  
  bool won = find_winners(candidates, 4, 6);
  
  
  ASSERT_TRUE(won == true);
 
  ASSERT_TRUE(candidates[0].winner == true); 
  ASSERT_TRUE(candidates[1].winner == true);
  ASSERT_TRUE(candidates[2].winner == true);
  ASSERT_TRUE(candidates[3].winner == false);


}

TEST(Voting, find_winners_tie_2) {
  //int candidates[] = {0, 2, 2, 2};
  Candidate candidates[20];
  initialize_ballots(candidates, 4);
  
  candidates[0].votes = 0;
  candidates[1].votes = 2;
  candidates[2].votes = 2;
  candidates[3].votes = 2;  
  
  bool won = find_winners( candidates, 4, 6);
  
  ASSERT_TRUE(won == true);
  
  ASSERT_TRUE(candidates[0].winner == false); 
  ASSERT_TRUE(candidates[1].winner == true);
  ASSERT_TRUE(candidates[2].winner == true);
  ASSERT_TRUE(candidates[3].winner == true);

}

TEST(Voting, find_winners_one) { 
  //int candidates[] = {2, 5, 2, 0};
  
  Candidate candidates[20];
  initialize_ballots(candidates, 4);
  
  candidates[0].votes = 2;
  candidates[1].votes = 5;
  candidates[2].votes = 2;
  candidates[3].votes = 0;  
  
  bool won = find_winners(candidates, 4, 9);
  
  ASSERT_TRUE(won == true);
  ASSERT_TRUE(candidates[0].winner == false); 
  ASSERT_TRUE(candidates[1].winner == true);
  ASSERT_TRUE(candidates[2].winner == false);
  ASSERT_TRUE(candidates[3].winner == false);
  
}
  

TEST(Voting, find_losers_1) {
  //int candidates[] = {2, 1, 2};
  
  Candidate losers[20];
  initialize_ballots(losers, 3);
  
  losers[0].votes = 2;
  losers[1].votes = 1;
  losers[2].votes = 2;
  
  
  
  find_losers(losers, 3);
  
  
  ASSERT_TRUE(losers[0].loser == 0); 
  ASSERT_TRUE(losers[1].loser == 1); 
  ASSERT_TRUE(losers[2].loser == 0); 
  
}

TEST(Voting, find_losers_2) {
  //int candidates[] = {1, 1, 3, 3};
  
  Candidate losers[20];
  initialize_ballots(losers, 4);

  losers[0].votes = 1;
  losers[1].votes = 1;
  losers[2].votes = 3;
  losers[3].votes = 3;

  find_losers(losers, 4);
  
  
  ASSERT_TRUE(losers[0].loser == true); 
  ASSERT_TRUE(losers[1].loser == true); 
  ASSERT_TRUE(losers[2].loser == false); 
  ASSERT_TRUE(losers[3].loser == false); 
  

  
}

TEST(Voting, find_losers_additional) {
  //int candidates[] = {2, 1, 2, 0};
  
  Candidate losers[20];
  initialize_ballots(losers, 4);
  
  losers[0].votes = 2;
  losers[1].votes = 1;
  losers[2].votes = 2;
  losers[3].votes = 0;  
  
  
  find_losers(losers, 4);
  

  ASSERT_TRUE(losers[0].loser == false); 
  ASSERT_TRUE(losers[1].loser == true); 
  ASSERT_TRUE(losers[2].loser == false); 
  ASSERT_TRUE(losers[3].loser == true); 
  
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
  
    int num_candidates;
    int num_ballots;
    Candidate ballot_list[20];
    
  
    read_info(r, num_candidates, ballot_list, num_ballots);
    ASSERT_TRUE(num_candidates == 3);
    ASSERT_TRUE(ballot_list[0].name == "John Doe");
    ASSERT_TRUE(ballot_list[2].name == "Sirhan Sirhan");  
    
    ASSERT_TRUE(ballot_list[0].ballot_list.size() == 2);
}

TEST(Voting, read_info_2) {
  std::istringstream r("2\nJean-Luc Picard\nJames T. Kirk\n1 2\n2 1\n2 1\n");
  int num_candidates;
  int num_ballots;
  Candidate ballot_list[20];  
  
  read_info(r, num_candidates, ballot_list, num_ballots);
  ASSERT_TRUE(num_candidates == 2);
  ASSERT_TRUE(num_ballots == 3);
  ASSERT_TRUE(ballot_list[0].name == "Jean-Luc Picard");
  ASSERT_TRUE(ballot_list[1].votes == 2);
  
}

TEST(Voting, determine_winner_1) {
    std::ostringstream w;
    std::queue<int> ballots[3];     // TODO keep this but lower constant
    int num_candidates = 3;
    int num_ballots = 3; 
    Candidate ballot_list[20];
    
    initialize_ballots(ballot_list, 3);
    
    ballot_list[0].name = "John Doe";
    ballot_list[1].name = "Jane Smith";
    ballot_list[2].name = "Sirhan Sirhan";
    
    ballots[0].push(1);
    ballots[0].push(2);
    ballots[0].push(3);
    
    ballots[1].push(2);
    ballots[1].push(1);
    ballots[1].push(3);
    
    ballots[2].push(2);
    ballots[2].push(3);
    ballots[2].push(1);
    

    ballot_list[0].push_front(ballots[0]);
    ballot_list[1].push_front(ballots[1]);
    ballot_list[1].push_front(ballots[1]);
    
    ballot_list[0].votes = 1;
    ballot_list[1].votes = 2;
    
    determine_winner(w, num_candidates, ballot_list, num_ballots);

    ASSERT_TRUE(w.str() == "Jane Smith");
} 


TEST(Voting, determine_winner_tie) {
    std::ostringstream w;

    std::queue<int> ballots[6];    
    int num_candidates = 4;
    int num_ballots = 6; 
    Candidate ballot_list[20];
    
    initialize_ballots(ballot_list, 4);
    
    ballot_list[0].name = "Red";
    ballot_list[1].name = "Green";
    ballot_list[2].name = "Blue";
    ballot_list[3].name = "Orange";

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
    
    ballot_list[0].push_front(ballots[0]);
    ballot_list[1].push_front(ballots[1]);
    ballot_list[1].push_front(ballots[2]);
    ballot_list[0].push_front(ballots[3]);
    ballot_list[2].push_front(ballots[4]);
    ballot_list[3].push_front(ballots[5]);
    
    ballot_list[0].votes = 2;
    ballot_list[1].votes = 2;
    ballot_list[2].votes = 1;
    ballot_list[3].votes = 1;
    

    determine_winner(w, num_candidates, ballot_list, num_ballots);

    ASSERT_TRUE(w.str() == "Red\nGreen");

}

TEST(Voting, solve_1) {
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


TEST(Voting, solve_3) {
	std::istringstream r("3\n\n1\nJean-Luc Picard\n1\n1\n1\n\n2\nJean-Luc Picard\nJames T. Kirk\n1 2\n2 1\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Jean-Luc Picard\n\nJean-Luc Picard\nJames T. Kirk\n\nJohn\n");
}

TEST(Voting, solve_4) {
	std::istringstream r("2\n\n3\nJohn\nTed\nWill\n3 1 2\n2 1 3\n1 2 3\n3 2 1\n2 3 1\n1 3 2\n\n2\nIshmael\nAhab\n1 2\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "John\nTed\nWill\n\nIshmael\nAhab\n");
}

TEST(Voting, solve_5) {
	std::istringstream r("2\n\n3\nTed\nPete\nTodd\n2 1 3\n1 2 3\n1 3 2\n1 1 2\n\n2\nJim\nRobin\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1\n2 1");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Ted\n\nRobin\n");
}

TEST(Voting, solve_6) {
	std::istringstream r("1\n\n1\nJean-Luc Picard\n1\n1\n1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Jean-Luc Picard\n");
}

TEST(Voting, solve_7) {
	std::istringstream r("2\n\n1\nJean-Luc Picard\n1\n1\n1\n\n2\nJean-Luc Picard\nJames T. Kirk\n1 2\n2 1\n2 1\n");
	std::ostringstream w;

	voting_solve (r, w);

    ASSERT_TRUE(w.str() == "Jean-Luc Picard\n\nJames T. Kirk\n");
}

TEST(Voting, print_winners_1) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;

  Candidate candidates[20];
  int num_candidates = 3;
  
  initialize_ballots(candidates, num_candidates);
  
  candidates[0].name = "Bob";
  candidates[1].name = "Alice";
  candidates[2].name = "Joe";
  
  candidates[1].winner = true;
  
  print_winners(w, candidates, num_candidates);
  ASSERT_TRUE(w.str() == "Alice");
}

TEST(Voting, print_winners_2) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;

  Candidate candidate_names[20];
  int num_candidates = 3;
  
  initialize_ballots(candidate_names, num_candidates);
  
  candidate_names[0].name = "Bob";
  candidate_names[1].name = "Alice";
  candidate_names[2].name = "Joe";
  
  candidate_names[0].winner = true;
  candidate_names[1].winner = true;
  
  print_winners(w, candidate_names, num_candidates);
  ASSERT_TRUE(w.str() == "Bob\nAlice");
}

TEST(Voting, print_winners_3) {
  //void print_winners(std::ostream& w, int winners[], std::string candidate_names[], int num_candidates) {
  std::ostringstream w;

  Candidate candidate_names[20];
  int num_candidates = 3;
  
  initialize_ballots(candidate_names, num_candidates);
  
  candidate_names[0].name = "Bob";
  candidate_names[1].name = "Alice";
  candidate_names[2].name = "Joe";
  
  candidate_names[0].winner = true;
  candidate_names[1].winner = true;
  candidate_names[2].winner = true;
   
  print_winners(w, candidate_names, num_candidates);
  ASSERT_TRUE(w.str() == "Bob\nAlice\nJoe");
}


TEST(Voting, update_votes_1) {
    std::ostringstream w;

    std::queue<int> ballots[6];    
    int num_candidates = 4;
    
    Candidate ballot_list[20];
    
    initialize_ballots(ballot_list, num_candidates);
    
    ballot_list[0].name = "Red";
    ballot_list[1].name = "Green";
    ballot_list[2].name = "Blue";
    ballot_list[3].name = "Orange";

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
    
    ballot_list[0].push_front(ballots[0]);
    ballot_list[1].push_front(ballots[1]);
    ballot_list[1].push_front(ballots[2]);
    ballot_list[0].push_front(ballots[3]);
    ballot_list[2].push_front(ballots[4]);
    ballot_list[3].push_front(ballots[5]);
    
    ballot_list[0].votes = 2;
    ballot_list[1].votes = 2;
    ballot_list[2].votes = 1;
    ballot_list[3].votes = 1;
    
    ballot_list[2].update_votes(ballot_list, num_candidates);
    
    ASSERT_TRUE(ballot_list[2].votes == 0);
    
}

TEST(Candidate, push_front_1) {
  Candidate c;
  c.initialize();

  std::queue<int> ballot;
  
  c.push_front(ballot);
  ASSERT_TRUE(c.ballot_list.size() == 1);
}

TEST(Candidate, push_front_2) {
  Candidate c;
  c.initialize();

  std::queue<int> ballot1;
  std::queue<int> ballot2;

  
  c.push_front(ballot1);
  c.push_front(ballot2);
  ASSERT_TRUE(c.ballot_list.size() == 2);
}
TEST(Candidate, push_front_3) {
  Candidate c;
  c.initialize();

  std::queue<int> ballot1;
  std::queue<int> ballot2;
  std::queue<int> ballot3;
  
  c.push_front(ballot1);
  c.push_front(ballot2);
  c.push_front(ballot3);
  ASSERT_TRUE(c.ballot_list.size() == 3);
}

TEST(Candidate, clear_ballots_1) {
  Candidate c;
  std::queue<int> ballot;
  c.initialize();
  
  
  c.push_front(ballot);
  ASSERT_TRUE(c.ballot_list.size() == 1);
  c.clear_ballots();
  ASSERT_TRUE(c.ballot_list.size() == 0);
}

TEST(Candidate, clear_ballots_2) {
  Candidate c;
  c.initialize();

  c.votes = 5;
  ASSERT_TRUE(c.votes == 5);
  c.clear_ballots();
  ASSERT_TRUE(c.votes == 0);
}

TEST(Candidate, clear_ballots_3) {
  Candidate c;
  c.initialize();


  ASSERT_TRUE(c.votes == 0);
  ASSERT_TRUE(c.ballot_list.size() == 0);
  c.clear_ballots();
  ASSERT_TRUE(c.votes == 0);
  ASSERT_TRUE(c.ballot_list.size() == 0);
}





   


    
