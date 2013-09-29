// --------------------------------
// cs371p-voting/TestVoting.c++
// Copyright (C) 2013
// Justin Hust
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

// -----------
// candidates_clear()
// -----------

TEST(candidates, clear_1) {
  candidates_clear();
  
  ASSERT_TRUE( candidates_getCount() == 0);

}

// ----

TEST(candidates, clear_2) {
  candidates_clear();
  
  std::istringstream iss("Mike");
  candidates_add(iss);
  
  candidates_clear();
  
  ASSERT_TRUE( candidates_getCount() == 0);

}

// ----

TEST(candidates, clear_3) {
  candidates_clear();
  
  std::istringstream iss("Mike");
  std::istringstream iss2("Bob");
 
  candidates_add(iss);
  candidates_clear();
  candidates_add(iss2);
  
  ASSERT_TRUE( candidates_getCount() == 1);

}

// ----

TEST(candidates, clear_4) {
  std::istringstream iss("Mike");
  std::istringstream iss2("Bob");

  candidates_clear();
  
  candidates_add(iss);
  
  candidates_clear();
    
  candidates_add(iss);
  candidates_add(iss2);
  
  ASSERT_TRUE( candidates_getCount() == 2);

}

// -----------
// candidates_getCount()
// -----------

TEST(candidates, getCount_1) {
  candidates_clear();

  std::istringstream iss("Mike");
  candidates_add(iss);

  ASSERT_TRUE( candidates_getCount() == 1);

}

// ---

TEST(candidates, getCount_2) {
  candidates_clear();

  std::istringstream iss("Mike");
  std::istringstream iss2("John");
  candidates_add(iss);
  candidates_add(iss2);

  ASSERT_TRUE( candidates_getCount() == 2);

}

// ---

TEST(candidates, getCount_3) {
  candidates_clear();

  std::istringstream iss("Mike");
  std::istringstream iss2("John");
  std::istringstream iss3("Bob");
  candidates_add(iss);
  candidates_add(iss2);
  candidates_add(iss3);

  ASSERT_TRUE( candidates_getCount() == 3);

}

// ---

TEST(candidates, getCount_4) {
  candidates_clear();

  std::istringstream iss("Mike");
  std::istringstream iss2("John");
  std::istringstream iss3("Bob");
  candidates_add(iss);
  candidates_add(iss2);
  
  candidates_clear();
  candidates_add(iss3);

  ASSERT_TRUE( candidates_getCount() == 1);

}

// -----------
// candidate_add()
// -----------

TEST(candidates, add_1) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  ASSERT_TRUE( candidates_getCount() == 1);

}

// ----

TEST(candidates, add_2) {
  candidates_clear();
  
  std::istringstream iss("John");
  std::istringstream iss2("Mike");
  
  candidates_add(iss);
  candidates_add(iss2);
  
  ASSERT_TRUE( candidates_getCount() == 2);


}

// ----

TEST(candidates, add_3) {
  candidates_clear();
  
  std::istringstream iss("John");
  std::istringstream iss2("Mike");
  std::istringstream iss3("Chris");
  
  candidates_add(iss);
  candidates_add(iss2);
  candidates_add(iss3);
  
  ASSERT_TRUE( candidates_getCount() == 3);

}


// -----------
// candidates_resetVotes()
// -----------

TEST(candidates, resetVotes_1) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  candidates_resetVotes(0);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 0);

}

// ---

TEST(candidates, resetVotes_2) {
  candidates_clear();
  
  std::istringstream iss("John");
  std::istringstream iss2("Mike");
  candidates_add(iss);
  candidates_add(iss2);
  
  candidates_resetVotes(0);
  candidates_resetVotes(1);
  
  ASSERT_TRUE( candidates_getNumVotes(1) == 0);

}

// -----------
// candidates_addVotes()
// -----------

TEST(candidates, addVotes_1) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  candidates_resetVotes(0);
  candidates_addVotes(0, 1);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 1);

}

// ----

TEST(candidates, addVotes_2) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  candidates_resetVotes(0);
  candidates_addVotes(0, 1);
  candidates_addVotes(0, 3);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 4);

}

// ----

TEST(candidates, addVotes_3) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  candidates_resetVotes(0);
  candidates_addVotes(0, 5);
  candidates_resetVotes(0);
  candidates_addVotes(0, 0);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 0);

}

// ----

TEST(candidates, addVotes_4) {
  candidates_clear();
  
  std::istringstream iss("John");
  std::istringstream iss2("Mike");
  candidates_add(iss);
  candidates_add(iss2);
  
  candidates_resetVotes(0);
  candidates_resetVotes(1);
  candidates_addVotes(0, 2);
  candidates_addVotes(1, 7);
  
  ASSERT_TRUE( (candidates_getNumVotes(0) == 2) &&
               (candidates_getNumVotes(1) == 7));

}

// ----

TEST(candidates, addVotes_5) {
  candidates_clear();
  
  std::istringstream iss("John");
  std::istringstream iss2("Mike");
  candidates_add(iss);
  candidates_add(iss2);
  
  candidates_resetVotes(0);
  candidates_resetVotes(1);
  candidates_addVotes(0, 2);
  candidates_addVotes(1, 5);
  candidates_addVotes(0, 1);
    
  ASSERT_TRUE( (candidates_getNumVotes(0) == 3) &&
               (candidates_getNumVotes(1) == 5));

}

// -----------
// candidates_getNumVotes()
// -----------

TEST(candidates, getNumVotes_1) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);
  
  candidates_resetVotes(0);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 0);

}

// ---

TEST(candidates, getNumVotes_2) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);  
  
  candidates_resetVotes(0);
  candidates_addVotes(0, 1);
  candidates_addVotes(0, 1);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 2);

}

// ---

TEST(candidates, getNumVotes_3) {
  candidates_clear();
  
  std::istringstream iss("John");
  candidates_add(iss);  
  
  candidates_resetVotes(0);
  candidates_addVotes(0, 1);
  candidates_resetVotes(0);
  candidates_addVotes(0, 1);
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 1);

}

// -----------
// ballots_clear()
// -----------

TEST(ballots, clear_1) {
  candidates_clear();
  ballots_clear();
  
  ASSERT_TRUE( ballots_getCount() == 0);

}

// -----------
// ballots_getCount()
// -----------

TEST(ballots, getCount_1) {
  candidates_clear();
  ballots_clear();
  
  ASSERT_TRUE( ballots_getCount() == 0);

}


// -----------
// ballots_add()
// -----------

TEST(ballots, add_1) {
  candidates_clear(); 
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  candidates_add(isCand1);
  
  std::istringstream isBal1("1");
  ballots_add(isBal1);
  
  ASSERT_TRUE( ballots_toString(0) == "1 | 0 0");

}

// ---

TEST(ballots, add_2) {
  candidates_clear(); 
  ballots_clear();
        
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  std::istringstream isBal2("2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  
  ASSERT_TRUE( (ballots_toString(0) == "1 2 | 0 0") &&
               (ballots_toString(1) == "2 1 | 0 1") );

}

// ---

TEST(ballots, add_3) {
  candidates_clear(); 
  ballots_clear();
     
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 1 3");
  std::istringstream isBal3("3 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
    
  ASSERT_TRUE( ballots_toString(0) == "1 2 3 | 0 0" &&
               ballots_toString(1) == "2 1 3 | 0 1" && 
               ballots_toString(2) == "3 1 2 | 0 2");

}

// -----------
// election_tally()
// -----------

TEST(election, tally_1) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand("John Doe");
  candidates_add(isCand);
  
  std::istringstream isBal1("1");
  ballots_add(isBal1);
  
  election_tally();
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 1);

}

// ---

TEST(election, tally_2) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand("John Doe");
  candidates_add(isCand);
  
  std::istringstream isBal1("1");
  ballots_add(isBal1);
 
  std::istringstream isBal2("1");
  ballots_add(isBal2);
   
  election_tally();
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 2);

}

// ---

TEST(election, tally_3) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  ballots_add(isBal1);
 
  std::istringstream isBal2("1 2");
  ballots_add(isBal2);
   
  election_tally();
  
  ASSERT_TRUE( candidates_getNumVotes(0) == 2 &&
               candidates_getNumVotes(1) == 0 );

}

// ---

TEST(election, tally_4) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  std::istringstream isBal2("2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
   
  election_tally();
  
  ASSERT_TRUE( (ballots_getCount() == 2) &&
               (candidates_getNumVotes(0) == 1) &&
               (candidates_getNumVotes(1) == 1)  );

}

// ---

TEST(election, tally_5) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 1 3");
  std::istringstream isBal3("2 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  ASSERT_TRUE( (ballots_getCount() == 3) &&
               (candidates_getNumVotes(0) == 1) &&
               (candidates_getNumVotes(1) == 2) &&
               (candidates_getNumVotes(2) == 0)  );

}

// -----------
// election_hasMajorityWinner
// -----------
TEST(election, hasMajorityWinner_1) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 1 3");
  std::istringstream isBal3("2 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  int winner = -1;
  bool hasMajorityWinner = election_hasMajorityWinner(winner);
  
  ASSERT_TRUE( hasMajorityWinner && winner == 1);

}

// -----

TEST(election, hasMajorityWinner_2) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("3 2 1");
  std::istringstream isBal2("3 2 1");
  std::istringstream isBal3("3 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  int winner = -1;
  bool hasMajorityWinner = election_hasMajorityWinner(winner);
  
  ASSERT_TRUE( hasMajorityWinner && winner == 2);

}

// -----

TEST(election, hasMajorityWinner_3) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  // no winner here.
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 3 1");
  std::istringstream isBal3("3 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  int winner = -1;
  bool hasMajorityWinner = election_hasMajorityWinner(winner);
  
  ASSERT_TRUE( !hasMajorityWinner );

}

// -----

TEST(election, hasMajorityWinner_4) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("Red");
  std::istringstream isCand2("Green");
  std::istringstream isCand3("Blue");
  std::istringstream isCand4("Orange");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  candidates_add(isCand4);
  
  // no winner here.
  std::istringstream isBal1("1 2 3 4");
  std::istringstream isBal2("2 1 3 4");
  std::istringstream isBal3("2 3 1 4");
  std::istringstream isBal4("1 2 3 4");
  std::istringstream isBal5("3 4 1 2");
  std::istringstream isBal6("4 3 2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
  ballots_add(isBal5);
  ballots_add(isBal6);

  election_tally();
  
  int winner = -1;
  bool hasMajorityWinner = election_hasMajorityWinner(winner);
  
  ASSERT_TRUE( !hasMajorityWinner );

}

// ------------------
// isDeadTie
// ------------------

TEST(election, isDeadTie_1) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 1 3");
  std::istringstream isBal3("2 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  ASSERT_TRUE( ! election_isDeadTie() );

}

// -----

TEST(election, isDeadTie_2) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  std::istringstream isBal2("2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
     
  election_tally();
  
  ASSERT_TRUE( election_isDeadTie() );

}

// -----

TEST(election, isDeadTie_3) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("3 1 2");
  std::istringstream isBal3("2 3 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
     
  election_tally();
  
  ASSERT_TRUE( election_isDeadTie() );

}

// -----

TEST(election, isDeadTie_4) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("1 2 3");
  std::istringstream isBal3("3 2 1");
  std::istringstream isBal4("3 2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
     
  election_tally();
  election_tryRunoff();
  election_tally();
  
  ASSERT_TRUE( election_isDeadTie() );

}

// ------------------
// election_runoff
// ------------------

TEST(election, tryRunoff_1) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  
  std::istringstream isBal1("1 2 3");
  std::istringstream isBal2("2 1 3");
  std::istringstream isBal3("2 3 1");
  std::istringstream isBal4("1 2 3");
  std::istringstream isBal5("3 1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
  ballots_add(isBal5);
        
  election_tally();
  
  bool bRunoff = election_tryRunoff();
  
  election_tally();
  
  std::string sBal = ballots_toString(4);
  
  ASSERT_TRUE( bRunoff );
  
}

// ------

TEST(election, tryRunoff_2) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  std::istringstream isCand4("Paul");
  std::istringstream isCand5("Mary");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  candidates_add(isCand4);
  candidates_add(isCand5);
  
  std::istringstream isBal1("1 2 3 4 5");
  std::istringstream isBal2("2 1 3 4 5");
  std::istringstream isBal3("2 3 1 5 4");
  std::istringstream isBal4("1 3 2 5 4");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
        
  election_tally();
  
  bool bRunoff = election_tryRunoff();
  bool bSecondRunoff = election_tryRunoff();
  
  ASSERT_TRUE( bRunoff && !bSecondRunoff && election_isDeadTie() );
  
}

// ------

TEST(election, tryRunoff_3) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  std::istringstream isCand3("Sirhan");
  std::istringstream isCand4("Paul");
  std::istringstream isCand5("Mary");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  candidates_add(isCand4);
  candidates_add(isCand5);
  
  std::istringstream isBal1("1 2 3 4 5");
  std::istringstream isBal2("2 1 3 4 5");
  std::istringstream isBal3("3 2 1 5 4");
  std::istringstream isBal4("1 3 2 5 4");
  std::istringstream isBal5("3 1 2 4 5");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
  ballots_add(isBal5);
          
  election_tally();
  
  // first runoff is the zeroes.
  // second runoff is jane smith
  // then it's a win for john
  bool bRunoff = election_tryRunoff();
  election_tally();
  bool bSecondRunoff = election_tryRunoff();
  election_tally();

  ASSERT_TRUE( bRunoff && bSecondRunoff && !election_isDeadTie() );
  
}

TEST(election, tryRunoff_4) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  std::istringstream isBal2("2 1");
  std::istringstream isBal3("2 1");
  std::istringstream isBal4("1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
        
  election_tally();
  
  bool bRunoff = election_tryRunoff();

  election_tally();

  ASSERT_TRUE( !bRunoff );
  
}

// ------------------
// election_outputTieCands
// ------------------

TEST(election, outputTieCands_1) {
  candidates_clear();
  ballots_clear();
  
  std::istringstream isCand1("John Doe");
  std::istringstream isCand2("Jane Smith");
  candidates_add(isCand1);
  candidates_add(isCand2);
  
  std::istringstream isBal1("1 2");
  std::istringstream isBal2("2 1");
  std::istringstream isBal3("2 1");
  std::istringstream isBal4("1 2");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
        
  election_tally();
  
  std::ostringstream o;
  election_outputTieCands(o);

  ASSERT_TRUE( election_isDeadTie() && o.str() == "John Doe\nJane Smith" );
  
}

// ------

TEST(election, outputTieCands_2) {
  candidates_clear();
  ballots_clear();
  
  // from quiz
  std::istringstream isCand1("Red");
  std::istringstream isCand2("Green");
  std::istringstream isCand3("Blue");
  std::istringstream isCand4("Orange");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  candidates_add(isCand4);
  
  // no winner here.
  std::istringstream isBal1("1 2 3 4");
  std::istringstream isBal2("2 1 3 4");
  std::istringstream isBal3("2 3 1 4");
  std::istringstream isBal4("1 2 3 4");
  std::istringstream isBal5("3 4 1 2");
  std::istringstream isBal6("4 3 2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
  ballots_add(isBal5);
  ballots_add(isBal6);

  election_tally();
  election_tryRunoff();
  election_tally();


  std::ostringstream o;
  election_outputTieCands(o);

  ASSERT_TRUE( election_isDeadTie() && o.str() == "Red\nGreen" );
  
}

// ------

TEST(election, outputTieCands_3) {
  candidates_clear();
  ballots_clear();
  
  // from quiz
  std::istringstream isCand1("Red");
  std::istringstream isCand2("Green");
  std::istringstream isCand3("Blue");
  std::istringstream isCand4("Orange");
  candidates_add(isCand1);
  candidates_add(isCand2);
  candidates_add(isCand3);
  candidates_add(isCand4);
  
  // no winner here.
  std::istringstream isBal1("1 2 3 4");
  std::istringstream isBal2("2 1 3 4");
  std::istringstream isBal3("2 3 1 4");
  std::istringstream isBal4("1 2 3 4");
  std::istringstream isBal5("3 4 1 2");
  std::istringstream isBal6("4 3 2 1");
  ballots_add(isBal1);
  ballots_add(isBal2);
  ballots_add(isBal3);
  ballots_add(isBal4);
  ballots_add(isBal5);
  ballots_add(isBal6);

  election_tally();
  election_tryRunoff();
  election_tally();


  std::ostringstream o;
  election_outputTieCands(o);

  ASSERT_TRUE( election_isDeadTie() && o.str() == "Red\nGreen" );
  
}

// ------------------
// election_eval
// ------------------

TEST(election, eval_1) {
  std::istringstream is("1\nJohn\n1");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 1);
  ASSERT_TRUE( ballots_getCount() == 1);
  ASSERT_TRUE( os.str() == "John\n" );
  
}

// ------

TEST(election, eval_2) {
  std::istringstream is("3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 3);
  ASSERT_TRUE( ballots_getCount() == 3);
  ASSERT_TRUE( os.str() == "Jane\n" );
  
}

// ------

TEST(election, eval_3) {
  // same as 2 but with newline at end
  std::istringstream is("3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 3);
  ASSERT_TRUE( ballots_getCount() == 3);
  ASSERT_TRUE( os.str() == "Jane\n" );
  
}

// ------

TEST(election, eval_4) {
  std::istringstream is("3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 3);
  ASSERT_TRUE( ballots_getCount() == 4);
  ASSERT_TRUE( os.str() == "John\nJane\n" );
  
}

// ------

TEST(election, eval_5) {
  std::istringstream is("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 4);
  ASSERT_TRUE( ballots_getCount() == 6);
  ASSERT_TRUE( os.str() == "Red\nGreen\n" );
  
}

// ------

TEST(election, eval_6) {
  // make red win
  std::istringstream is("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 1 2");
  std::ostringstream os("");
  
  election_eval(is, os);

  ASSERT_TRUE( candidates_getCount() == 4);
  ASSERT_TRUE( ballots_getCount() == 6);
  ASSERT_TRUE( os.str() == "Red\n" );
  
}

// ------------------
// election_eval
// ------------------

TEST(voting, eval_1) {
  // make red win
  std::istringstream is("2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 1 2\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1");
  std::ostringstream os("");

  voting_eval(is, os);

  ASSERT_TRUE( os.str() == "Red\n\nJane\n" );

}

// --------

TEST(voting, eval_2) {
  // make red win
  std::istringstream is("2\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n\n3\nJohn\nJane\nSirhan\n1 2 3\n3 1 2\n2 3 1");
  std::ostringstream os("");

  voting_eval(is, os);

  ASSERT_TRUE( os.str() == "John\nJane\n\nJohn\nJane\nSirhan\n" );

}

// --------

TEST(voting, eval_3) {
  // make red win
  std::istringstream is("3\n\n3\nJohn\nJane\nSirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n\n3\nJohn\nJane\nSirhan\n1 2 3\n3 1 2\n2 3 1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
  std::ostringstream os("");

  voting_eval(is, os);

  ASSERT_TRUE( os.str() == "John\nJane\n\nJohn\nJane\nSirhan\n\nRed\nGreen\n" );

}