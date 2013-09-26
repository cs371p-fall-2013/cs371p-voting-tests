// --------------------------------
// projects/voting/TestVoting.c++
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

    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

    % valgrind TestVoting > TestVoting.out
*/

// --------
// includes
// --------

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

TEST(Voting, read_basic) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Sirhan Sirhan") == 0);
}

TEST(Voting, read_basic_long_name) {
    std::istringstream r("1\n\n4\nbillybobbobbobbobobobobobobobobobboboobobobobobobob\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("billybobbobbobbobobobobobobobobobboboobobobobobobob") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[3].getName().compare("Sirhan Sirhan") == 0);
   
}

TEST(Voting, read_basic_multispace) {
    std::istringstream r("1\n\n4\nbilly bob bob bob bob obo bobo bobobo bo bbob oob obob ob o bobob\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("billy bob bob bob bob obo bobo bobobo bo bbob oob obob ob o bobob") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[3].getName().compare("Sirhan Sirhan") == 0);
   
}

TEST(Voting, read_votes_basic) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 1);
    ASSERT_TRUE(i.onTheBallot[0].voters.front().peek() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.front().peek() == 1);
    ASSERT_TRUE(i.onTheBallot[2].voters.front().peek() == 2);
    }

TEST(Voting, read_votes_basic_zero) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[0].voters.front().peek() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.front().peek() == 1);
    }

TEST(Voting, read_votes_basic_zero2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    }

TEST(Voting, read_votes_basic_allforOne) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n 1 2 3\n 1 2 3\n 1 2 3 \n 1 2 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 5);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    }

TEST(Voting, read_votes_basic_so_many_spaces) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1     2   3\n    1 2   3\n 1    2 3\n 1    2     3 \n 1     2        3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 5);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    }

TEST(Voting, read_votes_combined) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Sirhan Sirhan") == 0);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 3);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 3);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[0].voters.front().peek() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.front().peek() == 1);
    ASSERT_TRUE(i.onTheBallot[2].voters.front().peek() == 2);
    }

TEST(Voting, read_votes_combined2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n1 2 3\n 2 1 3\n 1 2 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Sirhan Sirhan") == 0);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 5);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[0].voters.front().peek() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.front().peek() == 1);
    ASSERT_TRUE(i.onTheBallot[2].voters.front().peek() == 2);
    }

TEST(Voting, read_votes_eof) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n1 2 3\n 2 1 3\n 1 2 3");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.onTheBallot[0].getName().compare("John Doe") == 0);
    ASSERT_TRUE(i.onTheBallot[1].getName().compare("Jane Smith") == 0);
    ASSERT_TRUE(i.onTheBallot[2].getName().compare("Sirhan Sirhan") == 0);
    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 5);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[0].voters.front().peek() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.front().peek() == 1);
    ASSERT_TRUE(i.onTheBallot[2].voters.front().peek() == 2);
    }


// ----
// solve
// ----
TEST(Voting, solve_one_votes) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n");

  //int total;
  //r >> total;
  std::ostringstream w;
  voting_solve(r,w);
   ASSERT_TRUE(w.str() == "John Doe\n");
	
}
TEST(Voting, solve_one_votes3) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n");

  //int total;
  //r >> total;
  std::ostringstream w;
  voting_solve(r,w);
   ASSERT_TRUE(w.str() == "Jane Smith\n");
	
}
TEST(Voting, solve_one_votes2) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n3 1 2\n");

  //int total;
  //r >> total;
  std::ostringstream w;
  voting_solve(r,w);
   ASSERT_TRUE(w.str() == "Sirhan Sirhan\n");
	
}
TEST(Voting, solve_zero_votes) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");

  //int total;
  //r >> total;
  std::ostringstream w;
  voting_solve(r,w);
   ASSERT_TRUE(w.str() == "");
	
}

TEST(Voting, solve_tied_loser) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 3 1\n1 2 3\n3 1 2");

   //int total;
   //r >> total;
   std::ostringstream w;
   voting_solve(r,w);
   ASSERT_TRUE(w.str() == "Jane Smith\n");

}

TEST(Voting, solve_tied_winner) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 3 1\n1 2 3\n1 3 2");

   //int total;
   //r >> total;
   std::ostringstream w;
   voting_solve(r,w);
   ASSERT_TRUE(w.str() == "John Doe\nJane Smith\n");

}

TEST(Voting, solve_tied_winner2) {
   std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n3 2 1\n 3 2 1\n");

   //int total;
   //r >> total;
   std::ostringstream w;
   voting_solve(r,w);
   ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");

}

// ----
// Check for winner
// ----
TEST(Voting, Election_winnecheck) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(!i.checkForWinners());
}

TEST(Voting, Election_winnecheck2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnecheck3) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_majority) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_majority2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n2 1 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_majority3) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n2 1 3\n1 2 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_majority4) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n2 1 3\n2 1 3\n1 2 3\n3 2 1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);

    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_one_canidate) {
    std::istringstream r("1\n\n1\nJohn Doe\n1\n1\n1\n1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_one_canidate_one_vote) {
    std::istringstream r("1\n\n1\nJohn Doe\n1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_tied) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 1 2 3");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_tied2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 1 2 3\n 3 2 1");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_tied3) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_tied4) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n3 2 1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();
    ASSERT_TRUE(i.checkForWinners());
}

TEST(Voting, Election_winnercheck_tied5) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 1 2 3\n3 2 1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();
    ASSERT_TRUE(i.checkForWinners());
}


/// ------
/// Election::RemoveLeastPopular
/// ------
TEST(Voting, Election_RemoveLeastPopular) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n1 2 3\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 5);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_tied) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 7);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_tied2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n2 3 1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 8);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_tied3) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 1 2 3 \n 1 2 3\n 1 2 3\n 1 2 3\n 2 1 3\n 2 1 3\n 3 2 1 \n 3 2 1\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 8);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_Switchtied) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 1 2 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[3].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_Switchtied2) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 2 1 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 3);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 3);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[3].voters.size() == 0);
}

TEST(Voting, Election_RemoveLeastPopular_Switchtied3) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 2 1 \n 4 3 2 1");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].voters.size() == 2);
    ASSERT_TRUE(i.onTheBallot[1].voters.size() == 4);
    ASSERT_TRUE(i.onTheBallot[2].voters.size() == 0);
    ASSERT_TRUE(i.onTheBallot[3].voters.size() == 0);
}

/// ------
/// Voter constructor
/// ------
TEST(Voting, Voter_constructor) {

  std::string in = "1 2 3 4";
  Voter test(in);

  ASSERT_TRUE(test.pref.front() == 1);
  ASSERT_TRUE(test.pref.back() == 4);

}

TEST(Voting, Voter_constructorLong) {

  std::string in = "1 2 3 4 5 6 7 8 9 10 12 13 14 15 16 17 18 19 20";
  Voter test(in);

  ASSERT_TRUE(test.pref.front() == 1);
  ASSERT_TRUE(test.pref.back() == 20);

}

TEST(Voting, Voter_constructorShort) {

  std::string in = "3 10";
  Voter test(in);

  ASSERT_TRUE(test.pref.front() == 3);
  ASSERT_TRUE(test.pref.back() == 10);

}


/// ------
/// Voter:peek
/// ------
TEST(Voting, Voter_peek) {

  std::string in = "1 2 3 4";
  Voter test(in);

  ASSERT_TRUE(test.peek() == 0);
}

TEST(Voting, Voter_peek2) {

  std::string in = "4 1 2 5 3";
  Voter test(in);

  ASSERT_TRUE(test.peek() == 3);

}

TEST(Voting, Voter_peek3) {

  std::string in = "10 20 30 40";
  Voter test(in);

  ASSERT_TRUE(test.peek() == 9);

}


/// ------
/// Voter:pop
/// ------
TEST(Voting, Voter_pop) {

  std::string in = "1 2 3 4";
  Voter test(in);

  ASSERT_TRUE(test.pop() == 0);
  ASSERT_TRUE(test.pref.front() == 2);

}

TEST(Voting, Voter_pop2) {

  std::string in = "6 5 1 2 3 4";
  Voter test(in);

  ASSERT_TRUE(test.pop() == 5);
  ASSERT_TRUE(test.pref.front() == 5);

}

TEST(Voting, Voter_pop3) {

  std::string in = "7 11 4 67 1 2 3 4";
  Voter test(in);

  ASSERT_TRUE(test.pop() == 6);
  ASSERT_TRUE(test.pref.front() == 11);

}


/// --------------
/// Candidate::lost()
/// --------------
TEST(Voting, Candidate_lost) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[2].lost());
}

TEST(Voting, Candidate_lostTie) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 1 2 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[2].lost());
    ASSERT_TRUE(i.onTheBallot[3].lost());
}

TEST(Voting, Candidate_lostCompliment) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 1 2 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(!i.onTheBallot[0].lost());
    ASSERT_TRUE(!i.onTheBallot[1].lost());
}


/// --------------
/// Candidate::getVotesFor()
/// --------------
TEST(Voting, Candidate_getVotesFor) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n 2 1 3\n 3 2 1\n 1 3 2\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].getVotesFor() == 4);
    ASSERT_TRUE(i.onTheBallot[1].getVotesFor() == 4);
    ASSERT_TRUE(i.onTheBallot[2].getVotesFor() == -1);
}

TEST(Voting, Candidate_TieGetVotes) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 1 2 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].getVotesFor() == 4);
    ASSERT_TRUE(i.onTheBallot[1].getVotesFor() == 2);
    ASSERT_TRUE(i.onTheBallot[2].getVotesFor() == -1);
    ASSERT_TRUE(i.onTheBallot[3].getVotesFor() == -1);
}

TEST(Voting, Candidate_getVotesFor3) {
    std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\n billy bob\n 1 2 3 4\n 2 1 3 4 \n 1 3 2 4\n 2 3 1 4 \n 3 4 1 2 \n 4 3 1 2");

    int total;
    r >> total;

    Election i;
    voting_read(r, i);
    i.checkForWinners();
    i.removeLeastPopular();

    ASSERT_TRUE(i.onTheBallot[0].getVotesFor() == 4);
    ASSERT_TRUE(i.onTheBallot[1].getVotesFor() == 2);
    ASSERT_TRUE(i.onTheBallot[2].getVotesFor() == -1);
    ASSERT_TRUE(i.onTheBallot[3].getVotesFor() == -1);
}
