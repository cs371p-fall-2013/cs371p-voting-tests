// --------------------------------
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

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

// --------
// read_num
// --------

TEST(Voting, read_number_simple){
	std::istringstream r("1\n");
	int i;
	bool success;

	success = read_num(r, i);
	
	ASSERT_TRUE(success);
	ASSERT_EQ(1, i);
}

TEST(Voting, read_number_empty) {
	std::istringstream r("\n");
	int i;
	bool success;

	success = read_num(r, i);
	ASSERT_FALSE(success);
}

TEST(Voting, read_number_multiline){
	std::istringstream r("1\n2\n");
	int i, j;
	bool success;
	
	success = read_num(r, i);
	ASSERT_TRUE(success);

	success = read_num(r, j);
	ASSERT_TRUE(success);

	ASSERT_EQ(1, i);
	ASSERT_EQ(2, j);
}

TEST(Voting, read_number_sameline){
	std::istringstream r("1 2 3");
	int i, j, k;
	bool success;

	success = read_num(r, i);
	ASSERT_TRUE(success);

	success = read_num(r, j);
	ASSERT_TRUE(success);

	success = read_num(r, k);
	ASSERT_TRUE(success);
	
	ASSERT_EQ(1, i);
	ASSERT_EQ(2, j);
	ASSERT_EQ(3, k);
}

// ---------------
// read_candidates
// ---------------

TEST(Voting, read_candidates_simple) {
	int num_cand = 3;
	std::vector<std::string> candidates;

	std::istringstream r("One\nTwo\nThree\n");

	read_candidates(r, num_cand, candidates);

	ASSERT_EQ("One", candidates[0]);
	ASSERT_EQ("Two", candidates[1]);
	ASSERT_EQ("Three", candidates[2]);
}

TEST(Voting, read_candidates_80_char) {
	int num_cand = 1;
	std::vector<std::string> candidates;
	std::string char80 = "aaaaabbbbbcccccdddddeeeeefffffggggghhhhhiiiiijjjjjkkkkklllllmmmmmnnnnnoooooppppp"; 

	std::istringstream r(char80);

	read_candidates(r, num_cand, candidates);

	ASSERT_EQ(char80, candidates[0]);
}


TEST(Voting, read_candidates_rand_char) {
	int num_cand = 1;
	std::vector<std::string> candidates;
	std::string chars = "1234567890!@#$%^&*()|}{[]<>?,.;:"; 
	std::istringstream r(chars);

	read_candidates(r, num_cand, candidates);

	ASSERT_EQ(chars, candidates[0]);
}

TEST(Voting, read_many_candidates) {
	int num_cand = 20;
	std::vector<std::string> candidates; 
	std::stringstream str;
	
	str << "One" << std::endl;
	str << "Two" << std::endl;
	str << "Three" << std::endl;
	str << "Four" << std::endl; 
	str << "Five" << std::endl; 
	str << "Six" << std::endl; 
	str << "Seven" << std::endl; 
	str << "Eight" << std::endl; 
	str << "Nine" << std::endl; 
	str << "Ten" << std::endl; 
	str << "Eleven" << std::endl; 
	str << "Twelve" << std::endl; 
	str << "Thirteen" << std::endl; 
	str << "Fourteen" << std::endl; 
	str << "Fifteen" << std::endl; 
	str << "Sixteen" << std::endl; 
	str << "Seventeen" << std::endl; 
	str << "Eighteen" << std::endl; 
	str << "Nineteen" << std::endl; 
	str << "Twenty" << std::endl; 

	std::istringstream r(str.str());
	read_candidates(r, num_cand, candidates);
	
	ASSERT_EQ("One", candidates[0]);
	ASSERT_EQ("Two", candidates[1]);
	ASSERT_EQ("Three", candidates[2]);
	ASSERT_EQ("Four", candidates[3]);	
	ASSERT_EQ("Five", candidates[4]);
	ASSERT_EQ("Six", candidates[5]);
	ASSERT_EQ("Seven", candidates[6]);
	ASSERT_EQ("Eight", candidates[7]);	
	ASSERT_EQ("Nine", candidates[8]);
	ASSERT_EQ("Ten", candidates[9]);
	ASSERT_EQ("Eleven", candidates[10]);
	ASSERT_EQ("Twelve", candidates[11]);	
	ASSERT_EQ("Thirteen", candidates[12]);
	ASSERT_EQ("Fourteen", candidates[13]);
	ASSERT_EQ("Fifteen", candidates[14]);
	ASSERT_EQ("Sixteen", candidates[15]);	
	ASSERT_EQ("Seventeen", candidates[16]);
	ASSERT_EQ("Eighteen", candidates[17]);
	ASSERT_EQ("Nineteen", candidates[18]);
	ASSERT_EQ("Twenty", candidates[19]);
}

// ------------
// read_ballots
// ------------

TEST(Voting, read_ballots_simple) {
	std::vector<int> ballots;

	std::istringstream r("1 2 3\n");

	read_ballots(r, ballots);

	ASSERT_EQ(1, ballots[0]);
	ASSERT_EQ(2, ballots[1]);
	ASSERT_EQ(3, ballots[2]);
}

TEST(Voting, read_ballots_newlines) {
	std::vector<int> ballots;

	std::istringstream r("1\n2\n3\n");

	read_ballots(r, ballots);
	
	ASSERT_EQ(1, ballots[0]);
	ASSERT_EQ(2, ballots[1]);
	ASSERT_EQ(3, ballots[2]);
}

TEST(Voting, read_multiple_ballots) {
	std::vector<int> ballots;

	std::istringstream r("1 2 3\n4 5 6\n7 8 9\n");

	read_ballots(r, ballots);

	ASSERT_EQ(1, ballots[0]);
	ASSERT_EQ(2, ballots[1]);
	ASSERT_EQ(3, ballots[2]);
	ASSERT_EQ(4, ballots[3]);
	ASSERT_EQ(5, ballots[4]);
	ASSERT_EQ(6, ballots[5]);
	ASSERT_EQ(7, ballots[6]);
	ASSERT_EQ(8, ballots[7]);
	ASSERT_EQ(9, ballots[8]);
}

// -----------
// voting_eval
// -----------

TEST(Voting, voting_eval_one_candidate){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 1;

	candidates.push_back("A");

	ballots.push_back(1);

	ballots.push_back(1);

	ballots.push_back(1);

	winners = voting_eval(num_candidates, candidates, ballots);

	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(1, winners.size());
	ASSERT_EQ("A", winners[0]);
}

TEST(Voting, voting_eval_two_candidates){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 2;

	candidates.push_back("David");
	candidates.push_back("Chao");

	ballots.push_back(1);
	ballots.push_back(2);

	ballots.push_back(1);
	ballots.push_back(2);

	ballots.push_back(2);
	ballots.push_back(1);

	winners = voting_eval(num_candidates, candidates, ballots);

	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(1, winners.size());
	ASSERT_EQ("David", winners[0]);
}

TEST(Voting, voting_eval_tie){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 3;

	candidates.push_back("A");
	candidates.push_back("B");
	candidates.push_back("C");

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(2);
	ballots.push_back(3);
	ballots.push_back(1);

	ballots.push_back(3);
	ballots.push_back(1);
	ballots.push_back(2);

	winners = voting_eval(num_candidates, candidates, ballots);

	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(3, winners.size());
	ASSERT_EQ("A", winners[0]);
	ASSERT_EQ("B", winners[1]);
	ASSERT_EQ("C", winners[2]);
}

TEST(Voting, voting_eval_majority_vote){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 3;

	candidates.push_back("A");
	candidates.push_back("B");
	candidates.push_back("C");

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(1);
	ballots.push_back(3);
	ballots.push_back(2);

	ballots.push_back(3);
	ballots.push_back(2);
	ballots.push_back(1);

	ballots.push_back(2);
	ballots.push_back(3);
	ballots.push_back(1);

	winners = voting_eval(num_candidates, candidates, ballots);

	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(1, winners.size());
	ASSERT_EQ("A", winners[0]);
}

TEST(Voting, voting_eval_more_candidates_than_ballots){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 3;

	candidates.push_back("A");
	candidates.push_back("B");
	candidates.push_back("C");

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	winners = voting_eval(num_candidates, candidates, ballots);

	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(1, winners.size());
	ASSERT_EQ("A", winners[0]);
}

TEST(Voting, voting_eval_uva_sample_input){
	std::vector<std::string> candidates; 
	std::vector<std::string> winners;
	std::vector<int> ballots;

	int num_candidates = 3;

	candidates.push_back("John Doe");
	candidates.push_back("Jane Smith");
	candidates.push_back("Sirhan Sirhan");

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(2);
	ballots.push_back(1);
	ballots.push_back(3);

	ballots.push_back(2);
	ballots.push_back(3);
	ballots.push_back(1);

	ballots.push_back(1);
	ballots.push_back(2);
	ballots.push_back(3);

	ballots.push_back(3);
	ballots.push_back(1);
	ballots.push_back(2);

	winners = voting_eval(num_candidates, candidates, ballots);
	
	ASSERT_FALSE(winners.empty());
	ASSERT_EQ(1, winners.size());
	ASSERT_EQ("John Doe", winners[0]);
}

// ------------
// voting_print
// ------------

TEST(Voting, print_one_candidate){
	std::ostringstream w;
	std::vector<std::string> names;

	names.push_back("John Doe");
	
	voting_print(w, names);

	ASSERT_EQ("John Doe", w.str());
}

TEST(Voting, print_multiple_candidates){
	std::ostringstream w;
	std::vector<std::string> names;

	names.push_back("Michael");
	names.push_back("Gavin");
	names.push_back("Ray");
	
	voting_print(w, names);

	ASSERT_EQ("Michael\nGavin\nRay", w.str());
}

// ------------
// voting_solve
// ------------

TEST(Voting, solve_one_candidate) {
	std::stringstream str;
	
	str << "1" << std::endl;
	str << std::endl;
	str << "1" << std::endl;
	str << "Kim Jong-un" << std::endl;
	str << "1" << std::endl;
	str << "1" << std::endl;
	str << "1" << std::endl;
    str << "1" << std::endl;
    str << "1";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("Kim Jong-un", w.str());
	// Glory and praise to our dear leader!
}

TEST(Voting, solve_tie) {
	std::stringstream str;
	
	str << "1" << std::endl;
	str << std::endl;
	str << "3" << std::endl;
	str << "Red" << std::endl;
	str << "Green" << std::endl;
	str << "Blue" << std::endl;
	str << "1 2 3" << std::endl;
	str << "2 1 3" << std::endl;
	str << "1 2 3" << std::endl;
    str << "2 1 3";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("Red\nGreen", w.str());
}

TEST(Voting, solve_total_tie) {
	std::stringstream str;
	
	str << "1" << std::endl;
	str << std::endl;
	str << "3" << std::endl;
	str << "Red" << std::endl;
	str << "Green" << std::endl;
	str << "Blue" << std::endl;
	str << "1 2 3" << std::endl;
	str << "2 1 3" << std::endl;
    str << "3 1 2";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("Red\nGreen\nBlue", w.str());
}

TEST(Voting, solve_uva_sample_input) {
	std::stringstream str;
	
	str << "1" << std::endl;
	str << std::endl;
	str << "3" << std::endl;
	str << "John Doe" << std::endl;
	str << "Jane Smith" << std::endl;
	str << "Sirhan Sirhan" << std::endl;
	str << "1 2 3" << std::endl;
	str << "2 1 3" << std::endl;
	str << "2 3 1" << std::endl;
    str << "1 2 3" << std::endl;
    str << "3 1 2";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("John Doe", w.str());
}

TEST(Voting, solve_more_candidates_than_ballots) {
	std::stringstream str;
	
	str << "1" << std::endl;
	str << std::endl;
	str << "3" << std::endl;
	str << "John Doe" << std::endl;
	str << "Jane Smith" << std::endl;
	str << "Sirhan Sirhan" << std::endl;
    str << "1 2 3" << std::endl;
    str << "3 1 2";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("John Doe\nSirhan Sirhan", w.str());
}

TEST(Voting, solve_multiple_cases) {
	std::stringstream str;
	
	str << "3" << std::endl;	// three cases
	str << std::endl;
	str << "2" << std::endl;	// first case; tie
	str << "Red" << std::endl;
	str << "Blue" << std::endl;
	str << "1 2" << std::endl;
	str << "2 1" << std::endl;
	str << "1 2" << std::endl;
    str << "2 1" << std::endl;
	str << std::endl;
	str << "3" << std::endl;	// second case; One wins
	str << "One" << std::endl;
	str << "Two" << std::endl;
	str << "Three" << std::endl;
	str << "1 2 3" << std::endl;
	str << "1 2 3" << std::endl;
	str << "1 2 3" << std::endl;
	str << std::endl;
	str << "4" << std::endl;	// third case; Spider-man wins
	str << "Superman" << std::endl;
	str << "Spider-man" << std::endl;
	str << "Batman" << std::endl;
	str << "Megaman" << std::endl;
	str << "1 2 4 3" << std::endl;
	str << "1 2 4 3" << std::endl;
	str << "1 2 4 3" << std::endl;
	str << "2 4 3 1" << std::endl;
	str << "2 1 4 3" << std::endl;
	str << "2 1 4 3" << std::endl;
	str << "3 4 2 1";

	std::istringstream r(str.str());
	std::ostringstream w;

	voting_solve(r, w);
	
	ASSERT_EQ("Red\nBlue\n\nOne\n\nSpider-man", w.str());
}

