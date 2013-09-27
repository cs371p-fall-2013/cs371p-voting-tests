
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
// ---
// set_name
// ---

TEST(Voting,name1)
{
	struct Candidate c;
	char name[80] = "BJ Honeycut";
	c.set_name(name);
	
	ASSERT_TRUE(strcmp(c.name,"BJ Honeycut")==0);
	ASSERT_TRUE(c.voteCount == 0);
	ASSERT_TRUE(c.stillInRace == true);
}
TEST(Voting,hard_to_pronouce_name)
{
	struct Candidate c;
	char name[80] = "$%$&WETRSHYSE";
	c.set_name(name);
	
	ASSERT_TRUE(strcmp(c.name,"$%$&WETRSHYSE")==0);
	ASSERT_TRUE(c.voteCount == 0);
	ASSERT_TRUE(c.stillInRace == true);
}
TEST(Voting,max_name)
{
	struct Candidate c;
	char name[80] = "My Name Is Eighty Characters Long And There Is Nothing You Can Do About It Haha";
	c.set_name(name);
	
	ASSERT_TRUE(strcmp(c.name,"My Name Is Eighty Characters Long And There Is Nothing You Can Do About It Haha")==0);
	ASSERT_TRUE(c.voteCount == 0);
	ASSERT_TRUE(c.stillInRace == true);
}
// ---
// add_vote
// ---
TEST(Voting,1vote)
{
	struct Candidate c;
	c.set_name("blank_cand");
	int votes[1000][20];
	votes[0][0]=1;
	votes[0][1]=2;
	votes[0][2]=3;
	c.add_vote(0);
	
	ASSERT_TRUE(c.voteCount == 1);
	ASSERT_TRUE(c.votej[0] == 0);

}
TEST(Voting,2votes)
{
	struct Candidate c;
	c.set_name("blank_cand");
	int votes[1000][20];
	votes[0][0]=1;
	votes[0][1]=2;
	votes[0][2]=3;
	votes[1][0]=1;
	votes[1][1]=2;
	votes[1][2]=3;
	c.add_vote(0);
	c.add_vote(1);
	
	ASSERT_TRUE(c.voteCount == 2);
	ASSERT_TRUE(c.votej[0] == 0);
	ASSERT_TRUE(c.votej[1] == 1);

}


// ----
// read
// ----
TEST(Voting, input_small){
	std::istringstream r("1\n\n1\nGeorge Washington\n1\n");
	int votes[1000][20];
	vector<Candidate> candidates;
	int numVotes;
	
	Candidate c;
	c.set_name("blank cand");
	candidates.push_back(c);

	int ncases;
	r >> ncases;
	r.get();
	r.get();

	voting_read(r,votes,candidates,numVotes);
	
	ASSERT_TRUE(votes[0][0] == 1);
	ASSERT_TRUE(candidates.size()-1 == 1);
	
	string name0 = candidates[0].name;
	ASSERT_TRUE (name0 == "blank cand");
	
	string name1 = candidates[1].name;
	ASSERT_TRUE(name1 == "George Washington");
	ASSERT_TRUE(candidates[1].votej.size() == 1);
	ASSERT_TRUE(votes[ candidates[1].votej[0] ][0] == 1);
	ASSERT_TRUE(candidates[1].stillInRace == true);
}

TEST(Voting, input_three){
	std::istringstream r("1\n\n3\nBob\nBill\nTed\n1 2 3\n1 2 3\n1 3 2\n2 1 3\n3 2 1");
	int votes[1000][20];
	vector<Candidate> candidates;
	int numVotes;
	
	Candidate c;
	c.set_name("blank cand");
	candidates.push_back(c);

	int ncases;
	r >> ncases;
	r.get();
	r.get();

	voting_read(r,votes,candidates,numVotes);
	
	ASSERT_TRUE(votes[0][0] == 1);
	ASSERT_TRUE(votes[0][1] == 2);
	ASSERT_TRUE(votes[0][2] == 3);
	ASSERT_TRUE(candidates.size()-1 == 3);
	
	string name0 = candidates[0].name;
	ASSERT_TRUE (name0 == "blank cand");
	
	string name1 = candidates[1].name;
	ASSERT_TRUE(name1 == "Bob");
	ASSERT_TRUE(candidates[1].voteCount == 3);
	ASSERT_TRUE( votes[ candidates[1].votej[0] ][0] == 1);
	ASSERT_TRUE( votes[ candidates[1].votej[1] ][0] == 1);
	ASSERT_TRUE( votes[ candidates[1].votej[2] ][0] == 1);
	ASSERT_TRUE(candidates[1].stillInRace == true);

	string name2 = candidates[2].name;
	ASSERT_TRUE(name2 == "Bill");
	ASSERT_TRUE(candidates[2].voteCount == 1);
	ASSERT_TRUE( votes[ candidates[2].votej[0] ][0] == 2);
	ASSERT_TRUE(candidates[2].stillInRace == true);
	
	string name3 = candidates[3].name;
	ASSERT_TRUE(name3 == "Ted");
	ASSERT_TRUE(candidates[3].voteCount == 1);
	ASSERT_TRUE( votes[ candidates[3].votej[0] ][0] == 3);
	ASSERT_TRUE(candidates[3].stillInRace == true);
}


// ----
// round
// ----

TEST(Voting, round_majority){
	vector<Candidate> candidates;
	int votes[1000][20];
	vector<Candidate> winners;
	
	Candidate c0;
	c0.set_name("blank cand");
	
	Candidate c1;
	c1.set_name("Fred");

	Candidate c2;
	c2.set_name("Ned");
	
	//first vote 2 1
	votes[0][0] = 2; 
	votes[0][1] = 1;
	c2.add_vote(1);
	//second vote 1 2
	votes[1][0] = 1;
	votes[1][1] = 2;
	c1.add_vote(1);
	//third vote 2 1
	votes[2][0] = 2; 
	votes[2][1] = 1;
	c2.add_vote(1);

	candidates.push_back(c0);
	candidates.push_back(c1);
	candidates.push_back(c2);

	int numVotes = 3;

	bool cont = voting_round(candidates, winners, numVotes, votes);
	ASSERT_TRUE(cont==false);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(strcmp(winners[0].name, "Ned") == 0);
}

TEST(Voting, round_all_tie){
	vector<Candidate> candidates;
	int votes[1000][20];
	vector<Candidate> winners;
	
	Candidate c0;
	c0.set_name("blank cand");
	
	Candidate c1;
	c1.set_name("Fred");

	Candidate c2;
	c2.set_name("Ned");
	
	//first vote 2 1
	votes[0][0] = 2; 
	votes[0][1] = 1;
	c2.add_vote(1);
	//second vote 1 2
	votes[1][0] = 1;
	votes[1][1] = 2;
	c1.add_vote(1);

	candidates.push_back(c0);
	candidates.push_back(c1);
	candidates.push_back(c2);

	int numVotes = 2;

	bool cont = voting_round(candidates, winners, numVotes, votes);
	ASSERT_TRUE(cont==false);
	ASSERT_TRUE(winners.size() == 2);
	ASSERT_TRUE(strcmp(winners[0].name, "Fred") == 0);
	ASSERT_TRUE(strcmp(winners[1].name, "Ned") == 0);
}

TEST(Voting, round_one_loser){
	vector<Candidate> candidates;
	int votes[1000][20];
	vector<Candidate> winners;
	
	Candidate c0;
	c0.set_name("blank cand");
	
	Candidate c1;
	c1.set_name("Fred");
	
	Candidate c2;
	c2.set_name("Ned");
	
	Candidate c3;
	c3.set_name("Ted");
	
	//first vote 2 1 3
	votes[0][0] = 2; 
	votes[0][1] = 1;
	votes[0][2] = 3;
	c2.add_vote(0);
	//second vote 1 2 3
	votes[1][0] = 1;
	votes[1][1] = 2;
	votes[1][2] = 3;
	c1.add_vote(1);
	//third vote 2 1 3
	votes[2][0] = 2; 
	votes[2][1] = 1;
	votes[2][2] = 3;
	c2.add_vote(2);
	//fourth vote 1 2 3
	votes[3][0] = 1;
	votes[3][1] = 2;
	votes[3][2] = 3;
	c1.add_vote(3);
	//fifth vote 3 2 1
	votes[4][0] = 3;
	votes[4][1] = 2;
	votes[4][2] = 1;
	c3.add_vote(4);
	

	candidates.push_back(c0);
	candidates.push_back(c1);
	candidates.push_back(c2);
	candidates.push_back(c3);

	int numVotes = 5;

	bool cont = voting_round(candidates, winners, numVotes, votes);
	ASSERT_TRUE(cont==true);
	ASSERT_TRUE(winners.size() == 0);
	ASSERT_TRUE(candidates[1].votej.size() == 2);
	ASSERT_TRUE(candidates[2].votej.size() == 3);
	ASSERT_TRUE(candidates[3].votej.size() == 0);
}

// ----
// print
// ----

TEST(Voting, print_one){
	std::ostringstream w;
	vector<Candidate> winners;
	Candidate c0;
	c0.set_name("Jud");
	winners.push_back(c0);

	voting_print(w, winners);

	ASSERT_TRUE(w.str() == "Jud\n");
}

TEST(Voting, print_two){
	std::ostringstream w;
	vector<Candidate> winners;
	Candidate c0;
	c0.set_name("Jud");
	winners.push_back(c0);
	Candidate c1;
	c1.set_name("Curly");
	winners.push_back(c1);

	voting_print(w, winners);

	ASSERT_TRUE(w.str() == "Jud\nCurly\n");
}

TEST(Voting, print_spaces){
	std::ostringstream w;
	vector<Candidate> winners;
	Candidate c0;
	c0.set_name("George Washington");
	winners.push_back(c0);
	Candidate c1;
	c1.set_name("George Bush");
	winners.push_back(c1);

	voting_print(w, winners);

	ASSERT_TRUE(w.str() == "George Washington\nGeorge Bush\n");
}

// ----
// solve
// ----

TEST(Voting, solve_simple){
	std::istringstream r("1\n\n1\nGeorge Washington\n1\n");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "George Washington\n");
}

TEST(Voting, solve_simple_majority){
	std::istringstream r("1\n\n2\nBill\nTed\n1 2\n2 1\n2 1\n");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "Ted\n");
}

TEST(Voting, solve_simple_tied){
	std::istringstream r("1\n\n2\nBill\nTed\n1 2\n2 1\n");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "Bill\nTed\n");
}

TEST(Voting, solve_simple_elimination){
	std::istringstream r("1\n\n3\nBill\nTed\nBob\n1 2 3\n2 1 3\n1 2 3\n2 3 1\n3 2 1");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "Ted\n");
}

TEST(Voting, solve_two_elections){
	std::istringstream r("2\n\n3\nBill\nTed\nBob\n1 2 3\n2 1 3\n1 2 3\n2 3 1\n3 2 1\n\n5\nfirst\nsecond\nthird\nfourth\nfifth\n1 2 3 4 5\n2 3 4 5 1\n3 4 5 1 2\n4 5 1 2 3\n5 1 2 3 4\n1 2 3 4 5\n2 3 4 5 1\n3 4 5 1 2");
	std::ostringstream w;
	voting_solve(r,w);
	ASSERT_TRUE(w.str() == "Ted\n\nfirst\n");



}




