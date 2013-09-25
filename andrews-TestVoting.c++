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

 TEST(voting_cases, read_4) {
     std::istringstream r("\n\n");
     int i;
     const bool b = voting_cases(r, i);
     ASSERT_TRUE(b == false);}

 TEST(voting_cases, read_5) {
     std::istringstream r("1234");
     int i;
     const bool b = voting_cases(r, i);
     ASSERT_TRUE(b == false);}

 // ----
 // read candidates
 // ----
 TEST(voting_candidates, read_2){
 	std::istringstream r("3\napple seed\njohnny dude\nehee ha\n");
 	std::string candidates [20];
 	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(b == true);
 	ASSERT_TRUE(candidates[0].compare("apple seed") == 0);
 	ASSERT_TRUE(candidates[1].compare("johnny dude") == 0);
 	ASSERT_TRUE(candidates[2].compare("ehee ha") == 0);
 }

 TEST(voting_candidates, read_6){
 	std::istringstream r("4\nMike Tyson\napple seed\njohnny dude\nehee ha\n\n");
 	std::string candidates [20];
 	int num_candidates = 0;

 	const bool b = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(b == true);

 	ASSERT_TRUE(candidates[0].compare("Mike Tyson") == 0);
 	ASSERT_TRUE(candidates[1].compare("apple seed") == 0);
 	ASSERT_TRUE(candidates[2].compare("johnny dude") == 0);
 	ASSERT_TRUE(candidates[3].compare("ehee ha") == 0);
 }


 TEST(voting_candidates_and_cases, read_3){
 	std::istringstream r("1\n\n3\napple seed\njohnny dude\nehee ha\n");
 	std::string candidates [20];
 	int num_elections, num_candidates;

 	const bool b = voting_cases(r, num_elections);
     ASSERT_TRUE(b == true);
     ASSERT_TRUE(num_elections ==    1);

 	const bool a = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(a == true);
 }

 TEST(voting_ballots, read_4){
 	int num_ballots;
 	std::istringstream r("1 2 3\n2 3 1\n3 1 2\n\n");
 	std::vector<std::vector<int> > ballots;
 	const bool b = voting_ballots(r, ballots, num_ballots);
 	ASSERT_TRUE(b == true);
 	ASSERT_TRUE(ballots[0][0] == 1);
 	ASSERT_TRUE(ballots[0][1] == 2);
 	ASSERT_TRUE(ballots[0][2] == 3);
 	ASSERT_TRUE(ballots[1][0] == 2);
 	ASSERT_TRUE(ballots[1][1] == 3);
 	ASSERT_TRUE(ballots[1][2] == 1);
 	ASSERT_TRUE(ballots[2][0] == 3);
 	ASSERT_TRUE(ballots[2][1] == 1);
 	ASSERT_TRUE(ballots[2][2] == 2);
 }

 TEST(voting_candidates_and_ballots, read_8){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n3 2 1\n2 3 1\n\n");
 	std:: string candidates[20];
 	int num_candidates;
 	int num_ballots;
 	std::vector<std::vector<int> > ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(num_candidates == 3);
 	ASSERT_TRUE(candidates[0].compare("johnny dude") == 0);
 	ASSERT_TRUE(candidates[1].compare("andrew guy") == 0);
 	ASSERT_TRUE(candidates[2].compare("ethan hawke") == 0);

 	const bool b = voting_ballots(r, ballots, num_ballots);
 	ASSERT_TRUE(b == true);
 	ASSERT_TRUE(ballots[0][0] == 1);
 	ASSERT_TRUE(ballots[0][1] == 2);
 	ASSERT_TRUE(ballots[0][2] == 3);
 	ASSERT_TRUE(ballots[1][0] == 3);
 	ASSERT_TRUE(ballots[1][1] == 2);
 	ASSERT_TRUE(ballots[1][2] == 1);
 	ASSERT_TRUE(ballots[2][0] == 2);
 	ASSERT_TRUE(ballots[2][1] == 3);
 	ASSERT_TRUE(ballots[2][2] == 1);
 }

 // ----
 // eval
 // ----
 TEST(voting_eval, eval_1){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n");
 	std:: string candidates[20];
 	int num_candidates;
 	int num_ballots;
 	std::vector<std::vector<int> > ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, ballots, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);
 	const std::string c = voting_eval(num_candidates, candidates, ballots, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\n") == 0);
 }

 TEST(voting_eval, eval_2){
 	std::istringstream r("3\njohnny dude\nandrew guy\nethan hawke\n1 2 3\n1 3 2\n2 3 1\n2 1 3\n");
 	std:: string candidates[20];
 	int num_candidates;
 	int num_ballots;
 	std::vector<std::vector<int> > ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, ballots, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);
 	const std::string c = voting_eval(num_candidates, candidates, ballots, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\nandrew guy\n") == 0);
 }

 TEST(voting_eval, eval_3){
 	std::istringstream r("4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n");
 	std:: string candidates[20];
 	int num_candidates;
 	int num_ballots;
 	std::vector<std::vector<int> > ballots;
 	const bool a = voting_candidates(r, candidates, num_candidates);
 	const bool b = voting_ballots(r, ballots, num_ballots);
 	ASSERT_TRUE(a == true);
 	ASSERT_TRUE(b == true);
 	const std::string c = voting_eval(num_candidates, candidates, ballots, num_ballots);
 	ASSERT_TRUE(c.compare("johnny dude\nandrew guy\n") == 0);
 }

TEST(voting_eval, eval_4){
	std::istringstream r("5\njane Smith\nJohn\nmary boo\nsally doo colly\nJimmy\n4 3 1 5 2\n4 3 2 1 5\n4 5 2 3 1\n3 2 4 1 5\n3 2 4 1 5\n5 4 1 3 2\n2 5 3 1 4\n5 2 4 3 1\n1 3 5 4 2\n2 4 3 1 5\n");
	std:: string candidates[20];
	int num_candidates;
	int num_ballots;
	std::vector<std::vector<int> > ballots;
	const bool a = voting_candidates(r, candidates, num_candidates);
	const bool b = voting_ballots(r, ballots, num_ballots);
	ASSERT_TRUE(a == true);
	ASSERT_TRUE(b == true);
	const std::string c = voting_eval(num_candidates, candidates, ballots, num_ballots);
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
 	int count;    
 	int num_ballots;   
 	int num_candidates = 0;
 	std::string candidates [20];
 	std::vector<std::vector<int> > ballots;

 	voting_cases(r, count);

 	for (int i = 0; i < count; ++i)
 	{

 		voting_candidates(r, candidates, num_candidates);
 		voting_ballots(r, ballots, num_ballots);
 		std::string winner = voting_eval(num_candidates, candidates, ballots, num_ballots);
 		ASSERT_TRUE(winner.compare("johnny dude\nandrew guy\n") == 0);
 	}

 }

 TEST(voting_solve, solve_2){
 	std::istringstream r("2\n\n4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n\n3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n");
 	int count;    
 	int num_ballots;   
 	int num_candidates = 0;
 	std::string candidates [20];
 	std::vector<std::vector<int> > ballots;

 	voting_cases(r, count);

 	for (int i = 0; i < count; ++i)
 	{

 		voting_candidates(r, candidates, num_candidates);
 		voting_ballots(r, ballots, num_ballots);
 		std::string winner = voting_eval(num_candidates, candidates, ballots, num_ballots);
 		if(i == 0){
 			ASSERT_TRUE(winner.compare("johnny dude\nandrew guy\n") == 0);
 		}
 		else if(i == 1){
 			ASSERT_TRUE(winner.compare("johnny dude\n") == 0);	
 		}
 	}
 }

TEST(voting_solve, solve_3){
 	std::istringstream r("3\n\n4\njohnny dude\nandrew guy\nethan hawke\ngoodguy greg\n1 2 3 4\n1 3 2 4\n2 3 1 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n\n3\njohnny dude\nandrew guy\nethan hawke\n 1 2 3\n1 3 2\n2 3 1\n\n4\nethan poulter\nandrew solis\ndustin hopper\nchris myers\n3 1 4 2\n3 2 1 4\n3 1 2 4\n4 2 1 3\n1 4 3 2\n3 1 4 2\n4 2 3 1\n4 1 3 2\n2 3 4 1\n4 2 1 3\n2 1 4 3\n4 3 1 2\n1 4 2 3\n4 2 1 3\n4 1 2 3\n1 4 2 3\n4 1 3 2\n1 2 3 4\n4 1 2 3\n3 2 1 4\n1 2 3 4\n2 1 3 4\n2 3 4 1\n3 4 1 2\n4 2 1 3\n3 4 2 1\n1 4 3 2\n4 3 2 1\n4 2 1 3\n3 2 4 1\n3 2 1 4\n4 2 1 3\n3 4 1 2\n3 1 2 4\n1 4 3 2\n3 1 2 4\n3 2 4 1\n4 2 3 1\n2 4 3 1\n4 1 2 3\n1 2 4 3\n2 3 4 1\n2 1 3 4\n2 3 1 4\n1 3 4 2\n4 3 1 2\n4 3 1 2\n3 1 4 2\n2 3 4 1\n1 3 4 2\n"); 	
	int count;
 	int num_ballots;   
 	int num_candidates = 0;
 	std::string candidates [20];
 	std::vector<std::vector<int> > ballots;

	voting_cases(r, count);

	for(int i =0; i < count; i++){

		voting_candidates(r, candidates, num_candidates);
		voting_ballots(r, ballots, num_ballots);
		std::string winner = voting_eval(num_candidates, candidates, ballots, num_ballots);

 	}
}
