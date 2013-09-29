// --------------------------
// Project Voting
// Noah Cho, ncho91
// Daniel Robertson, daniel10
// --------------------------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include "gtest/gtest.h"
#include "Voting.h"

TEST(Voting, set_losers1) {
	Election e; 
	Candidate c1, c2, c3; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 

	c1.nballots = 2; 
	c2.nballots = 1; 
	c3.nballots = 2; 

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.ncandidates = 3; 
	e.nballots = 5; 
	set_losers(e); 

	ASSERT_TRUE(e.candidates[1].loser);
}

TEST(Voting, set_losers2) {
	Election e; 
	Candidate c1, c2, c3; 
	std::vector<Candidate> candidates(3);

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 

	c1.nballots = 2; 
	c2.nballots = 1; 
	c3.nballots = 2; 
	c3.loser = false; 

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.ncandidates = 3; 
	e.nballots = 5; 
	set_losers(e); 

	ASSERT_TRUE(!e.candidates[2].loser);
}


TEST(Voting, set_losers3) {
	Election e; 
	Candidate c1, c2, c3, c4, c5; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 
	c4.name = "Kennedy";
	c5.name = "Douglas"; 

	c1.nballots = 3; 
	c2.nballots = 1; 
	c3.nballots = 2; 
	c4.nballots = 1;
	c5.nballots = 1;

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.candidates.push_back(c4);
	e.candidates.push_back(c5);
	e.ncandidates = 5; 
	e.nballots = 8; 
	set_losers(e); 

	ASSERT_TRUE(e.candidates[1].loser);
}


TEST(Voting, has_winners1) {
	bool b; 
	Election e; 
	Candidate c1, c2; 
	std::vector<Candidate> candidates;

	c1.name = "George Washington";
	c2.name = "Abe Lincoln";
	c1.nballots = 2; 
	c2.nballots = 0;
	e.ballots.push_back("1 2");
	e.ballots.push_back("1 2"); 
	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.ncandidates = 2; 
	e.nballots = 2;  

	b = has_winners(e); 
	ASSERT_TRUE(b); 
}

TEST(Voting, has_winners2) {
	bool b; 
	Election e; 
	Candidate c1, c2, c3, c4, c5; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 
	c4.name = "Kennedy";
	c5.name = "Douglas"; 

	c1.nballots = 3; 
	c2.nballots = 1; 
	c3.nballots = 2; 
	c4.nballots = 1;
	c5.nballots = 1;

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.candidates.push_back(c4);
	e.candidates.push_back(c5);
	e.ncandidates = 5; 
	e.nballots = 8; 

	b = has_winners(e); 
	ASSERT_TRUE(!b); 
}

TEST(Voting, has_winners3) {
	bool b; 
	Election e; 
	Candidate c1;
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";

	e.candidates.push_back(c1);
	e.ncandidates = 1; 
	e.nballots = 0; 

	b = has_winners(e); 
	ASSERT_TRUE(b);  
}

TEST(Voting, evaluate1) {
	bool b; 
	Election e; 
	Candidate c1, c2, c3, c4, c5; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 
	c4.name = "Kennedy";
	c5.name = "Douglas"; 

	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("1 2 3 4 5");

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.candidates.push_back(c4);
	e.candidates.push_back(c5);
	e.ncandidates = 5; 
	e.nballots = 6; 

	b = evaluate(e); 
	ASSERT_TRUE(b);
}


TEST(Voting, evaluate2) {
	bool b; 
	Election e; 
	Candidate c1, c2, c3, c4, c5; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 
	c4.name = "Kennedy";
	c5.name = "Douglas"; 

	e.ballots.push_back("1 2 3 4 5");
	e.ballots.push_back("2 3 4 5 1");
	e.ballots.push_back("5 3 1 4 2");
	e.ballots.push_back("1 2 3 4 5");

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.candidates.push_back(c4);
	e.candidates.push_back(c5);
	e.ncandidates = 5; 
	e.nballots = 4; 

	b = evaluate(e); 
	ASSERT_TRUE(b);
}

TEST(Voting, evaluate3) {
	bool b; 
	Election e; 
	Candidate c1, c2, c3, c4, c5; 
	std::vector<Candidate> candidates;

	c1.name = "Teddy Rosevelt";
	c2.name = "Barack Obamizzle";
	c3.name = "Georgrizzle Bush"; 
	c4.name = "Kennedy";
	c5.name = "Douglas"; 

	e.candidates.push_back(c1);
	e.candidates.push_back(c2);
	e.candidates.push_back(c3);
	e.candidates.push_back(c4);
	e.candidates.push_back(c5);
	e.ncandidates = 5; 
	e.nballots = 0; 

	b = evaluate(e); 
	ASSERT_TRUE(b);
}