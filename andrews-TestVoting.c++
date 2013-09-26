#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // == 
#include "gtest/gtest.h"

#include "Voting.h"

// ----------
// TestVoting
// ----------

// ----
// read cases
// ----
TEST(voting_cases, read_1) {
    std::istringstream r("1\n\n");
    int i;
    const bool b = voting_cases(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);}

 TEST(voting_cases, read_2) {
     std::istringstream r("\n\n");
     int i;
     const bool b = voting_cases(r, i);
     ASSERT_TRUE(b == false);}

 TEST(voting_cases, read_3) {
     std::istringstream r("1234");
     int i;
     const bool b = voting_cases(r, i);
     ASSERT_TRUE(b == false);}

 // ----
 // read candidates
 // ----
 TEST(voting_candidates, read_4){
 	std::istringstream r("3\napple seed\njohnny dude\nehee ha\n");
  std::vector<Candidate> candidates; 
	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(b == true);
 	ASSERT_TRUE((candidates[0].getName()).compare("apple seed") == 0);
 	ASSERT_TRUE((candidates[1].getName()).compare("johnny dude") == 0);
 	ASSERT_TRUE((candidates[2].getName()).compare("ehee ha") == 0);
 }

 TEST(voting_candidates, read_5){
 	std::istringstream r("4\nMike Tyson\napple seed\njohnny dude\nehee ha\n\n");
	std::vector<Candidate> candidates;
 	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);

 	ASSERT_TRUE(b == true);
 	ASSERT_TRUE((candidates[0].getName()).compare("Mike Tyson") == 0);
 	ASSERT_TRUE((candidates[1].getName()).compare("apple seed") == 0);
 	ASSERT_TRUE((candidates[2].getName()).compare("johnny dude") == 0);
 	ASSERT_TRUE((candidates[3].getName()).compare("ehee ha") == 0);
 }

TEST(voting_candidates, read_6){
 	std::istringstream r("2\nMike Tyson\napple seed\njohnny dude\nehee ha");
	std::vector<Candidate> candidates;
 	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);

 	ASSERT_TRUE(b == true);
	ASSERT_TRUE(candidates.size() == 2);
 }

// ----
 // read ballots
 // ----
 
 TEST(voting_ballots, read_7){
 	std::istringstream r("3\nMike Tyson\napple seed\njohnny dude\n");
	std::vector<Candidate> candidates;
 	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(b == true);
 
 	int num_ballots;
 	std::istringstream s("1 2 3\n1 3 2\n2 3 1\n\n");
 	const bool c = voting_ballots(s, candidates, num_ballots);
 	ASSERT_TRUE(c == true);
	ASSERT_TRUE(num_ballots == 3);
	ASSERT_TRUE(candidates[0].getNumBallots() == 2);
	ASSERT_TRUE(candidates[1].getNumBallots() == 1);
	ASSERT_TRUE(candidates[2].getNumBallots() == 0);
 }

 TEST(voting_ballots, read_8){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n3 2 1\n2 3 1\n\n");
	std::vector<Candidate> candidates;
	int num_candidates;
 	int num_ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	
	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(num_candidates == 3);

 	const bool b = voting_ballots(r, candidates, num_ballots);
 	ASSERT_TRUE(b == true);
	ASSERT_TRUE(num_ballots == 3);
	ASSERT_TRUE(candidates[0].getNumBallots() == 1);
	ASSERT_TRUE(candidates[1].getNumBallots() == 1);
	ASSERT_TRUE(candidates[2].getNumBallots() == 1);
 }

 TEST(voting_ballots, read_9){
 	std::istringstream r("1\n\n2\njohnny dude\nandrew guy\nethan hawke\n1 2 3\n3 2 1\n2 3 1\n\n");
	std::vector<Candidate> candidates;
	int num_cases;
	int num_candidates;
 	int num_ballots;

  const bool c = voting_cases(r, num_cases);
	ASSERT_TRUE(c == true);
	ASSERT_TRUE(num_cases == 1);
	const bool a = voting_candidates(r, candidates, num_candidates);
 	
	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(num_candidates == 2);

 	const bool b = voting_ballots(r, candidates, num_ballots);
	ASSERT_TRUE(b == false);
 } 

 // ----
 // eval
 // ----
 TEST(voting_eval, eval_1){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n");
	std::vector<Candidate> candidates;
 	int num_candidates;
 	int num_ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, candidates, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);

 	const std::string c = voting_eval(num_candidates, candidates, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\n") == 0);
 }

 TEST(voting_eval, eval_2){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n1 2 3\n1 3 2\n2 3 1\n2 1 3\n");
	std::vector<Candidate> candidates;
 	int num_candidates;
 	int num_ballots;
 	
	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, candidates, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);

 	const std::string c = voting_eval(num_candidates, candidates, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\nandrew guy\n") == 0);
 }

 TEST(voting_eval, eval_3){
 	std::istringstream r("4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
	std::vector<Candidate> candidates;
 	int num_candidates;
 	int num_ballots;

 	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, candidates, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);

 	const std::string c = voting_eval(num_candidates, candidates, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\nandrew guy\n") == 0);
 }

TEST(voting_eval, eval_4){
	std::istringstream r("5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	std::vector<Candidate> candidates;
	int num_candidates;
	int num_ballots;

	const bool a = voting_candidates(r, candidates, num_candidates);
	const bool b = voting_ballots(r, candidates, num_ballots);
	ASSERT_TRUE(a == true);
	ASSERT_TRUE(b == true);
	const std::string c = voting_eval(num_candidates, candidates, num_ballots);
  ASSERT_TRUE(c.compare("sally doo colly\n") == 0);	
}

//-----
//PRINT
//-----


TEST(voting_print, print_1){
	std::ostringstream output;
	std::string temp = "";
	voting_print (output, temp);
    ASSERT_TRUE(output.str() == "");
}

TEST(voting_print, print_2){
	std::ostringstream output;
	std::string temp = "ANDREWssWWSS";
	voting_print (output, temp);
    ASSERT_TRUE(output.str() == "ANDREWssWWSS");
}

TEST(voting_print, print_3){
	std::ostringstream output;
	std::string temp = "John Jacob Jack Johnson";
	voting_print (output, temp);
    ASSERT_TRUE(output.str() == "John Jacob Jack Johnson");
}
//-----
//SOLVE
//-----

 TEST(voting_solve, solve_1){
 	std::istringstream r("1\n\n4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
 	std::ostringstream w;

	voting_solve(r, w);

 	ASSERT_TRUE((w.str()).compare("johnny dude\nandrew guy\n") == 0);
 }

 TEST(voting_solve, solve_2){
 	std::istringstream r("2\n\n4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n\n3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n");
	std::ostringstream w;
	
	voting_solve(r,w);
	
	ASSERT_TRUE((w.str()).compare("johnny dude\nandrew guy\n\njohnny dude\n") == 0);
 }

TEST(voting_solve, solve_3){
 	std::istringstream r("3\n\n4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n\n3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n4\nethan poulter\nandrew solis\ndustin hopper\nchris myers\n3 1 4 2\n3 2 1 4\n3 1 2 4\n4 2 1 3\n1 4 3 2\n3 1 4 2\n4 2 3 1\n4 1 3 2\n2 3 4 1\n4 2 1 3\n2 1 4 3\n4 3 1 2\n1 4 2 3\n4 2 1 3\n4 1 2 3\n1 4 2 3\n4 1 3 2\n1 2 3 4\n4 1 2 3\n3 2 1 4\n1 2 3 4\n2 1 3 4\n2 3 4 1\n3 4 1 2\n4 2 1 3\n3 4 2 1\n1 4 3 2\n4 3 2 1\n4 2 1 3\n3 2 4 1\n3 2 1 4\n4 2 1 3\n3 4 1 2\n3 1 2 4\n1 4 3 2\n3 1 2 4\n3 2 4 1\n4 2 3 1\n2 4 3 1\n4 1 2 3\n1 2 4 3\n2 3 4 1\n2 1 3 4\n2 3 1 4\n1 3 4 2\n4 3 1 2\n4 3 1 2\n3 1 4 2\n2 3 4 1\n1 3 4 2\n"); 	
	std::ostringstream w;

	voting_solve(r,w);
  ASSERT_TRUE((w.str()).compare("johnny dude\nandrew guy\n\njohnny dude\n\ndustin hopper\nchris myers\n") == 0);
}	


//------------------
// create candidates
// -----------------

TEST(votingCreateCanidate, candidate_1){
	std::istringstream r("4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
 	int num_candidates = 0;
 	std::vector<Candidate> candidates;

	voting_candidates(r, candidates, num_candidates);

	ASSERT_TRUE(candidates[0].getName().compare("johnny dude") == 0);
	ASSERT_TRUE(candidates[1].getName().compare("andrew guy") == 0);
	ASSERT_TRUE(candidates[2].getName().compare("ethan hawke") == 0);
	ASSERT_TRUE(candidates[3].getName().compare("goodguy greg") == 0);
 }

TEST(votingCreateCanidate, candidate_2){
	std::istringstream r("10\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
 	int num_candidates = 0;
 	std::vector<Candidate> candidates;

	voting_candidates(r, candidates, num_candidates);

	ASSERT_TRUE(candidates[0].getName().compare("johnny dude") == 0);
	ASSERT_TRUE(candidates[1].getName().compare("andrew guy") == 0);
	ASSERT_TRUE(candidates[2].getName().compare("ethan hawke") == 0);
	ASSERT_TRUE(candidates[3].getName().compare("goodguy greg") == 0);
	ASSERT_TRUE(candidates[4].getName().compare("1 2 3 4") == 0);
	ASSERT_TRUE(candidates[5].getName().compare("1 3 2 4") == 0);
	ASSERT_TRUE(candidates[6].getName().compare("2 3 1 4") == 0);
	ASSERT_TRUE(candidates[7].getName().compare("2 1 3 4") == 0);
	ASSERT_TRUE(candidates[8].getName().compare("3 1 2 4") == 0);
	ASSERT_TRUE(candidates[9].getName().compare("4 2 1 3") == 0);
 
}
TEST(votingCreateCanidate, candidate_3){
	std::istringstream r("2\njohnny dude\n\n");
 	int num_candidates = 0;
 	std::vector<Candidate> candidates;

	voting_candidates(r, candidates, num_candidates);

	ASSERT_TRUE(candidates[0].getName().compare("johnny dude") == 0);
	ASSERT_TRUE(candidates[1].getName().compare("") == 0);
}

//------------------
// assign ballots
// -----------------

  
 TEST(votingBallots, ballots_1){
	std::istringstream r("4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 1 2 3\n");
 	int num_candidates, num_ballots;
 	std::vector<Candidate> candidates;

	
	voting_candidates(r, candidates, num_candidates);
  voting_ballots(r, candidates, num_ballots);
	
	ASSERT_TRUE(candidates[0].getNumBallots() == 2);
	ASSERT_TRUE(candidates[1].getNumBallots() == 2);
	ASSERT_TRUE(candidates[2].getNumBallots() == 1);
	ASSERT_TRUE(candidates[3].getNumBallots() == 1);

	ASSERT_TRUE(candidates[0].getBallotsVector().size() == 2);
 	ASSERT_TRUE(candidates[1].getBallotsVector().size() == 2);
	ASSERT_TRUE(candidates[2].getBallotsVector().size() == 1);
	ASSERT_TRUE(candidates[3].getBallotsVector().size() == 1);
 	
 }


 TEST(votingBallots, ballots_2){
	std::istringstream r("4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n3 2 1 4\n");
 	int num_candidates;
 	std::vector<Candidate> candidates;
 	int num_ballots;

	voting_candidates(r, candidates, num_candidates);
	voting_ballots(r, candidates, num_ballots);

	ASSERT_TRUE(candidates[0].getName().compare("johnny dude") == 0);
	ASSERT_TRUE(candidates[1].getName().compare("andrew guy") == 0);
	ASSERT_TRUE(candidates[2].getName().compare("ethan hawke") == 0);
	ASSERT_TRUE(candidates[3].getName().compare("goodguy greg") == 0);
	
	 ASSERT_TRUE(candidates[0].getNumBallots() == 2);
	 ASSERT_TRUE(candidates[1].getNumBallots() == 2);
	 ASSERT_TRUE(candidates[2].getNumBallots() == 2);
	 ASSERT_TRUE(candidates[3].getNumBallots() == 0);

	 ASSERT_TRUE(candidates[0].getBallotsVector().size() == 2);
   ASSERT_TRUE(candidates[1].getBallotsVector().size() == 2);
	 ASSERT_TRUE(candidates[2].getBallotsVector().size() == 2);
	 ASSERT_TRUE(candidates[3].getBallotsVector().size() == 0);

 }
 
TEST(votingBallots, ballots_3){
	std::istringstream r("4\njohnny dude\n\nethan hawke\ngoodguy greg\n2 1 3 4\n2 3 1 4\n1 3 2 4\n2 1 3 4\n3 1 2 4\n");
 	int num_candidates;
 	std::vector<Candidate> candidates;
 	int num_ballots;

	voting_candidates(r, candidates, num_candidates);
	voting_ballots(r, candidates, num_ballots);	

	std::string checkWinner = voting_eval(num_candidates, candidates, num_ballots);
	ASSERT_TRUE(checkWinner.compare("\n") == 0); 
 }
