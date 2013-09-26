// CS371p 

// Austin deBruyn (eid: ad29763) (cs user: austind)
// austin.debruyn@yahoo.com

// John Hall (eid: jrh4289) (cs user; jrh4289)
// halljr1919@hotmail.com

#include <iostream>
#include <cassert>
#include <sstream>
#include <string.h>
#include "gtest/gtest.h"
#include "Voting.h"


//-
//TestVoting
//-

// getname and addname
TEST(Voting, getname1)
{
  election e;
  (&e)->numCand = 1;
  std::string tmp = "John";
  (&e)->addName(tmp);
  std::string res = (*((&e)->getName(0)));
  ASSERT_TRUE(res == tmp);
}

TEST(Voting, getname2)
{
  election e;
  (&e)->numCand = 2;
  std::string tmp1 = "John";
  std::string tmp2 = "Austin";
  (&e)->addName(tmp1);
  (&e)->addName(tmp2);
  std::string res = (*((&e)->getName(1)));
  ASSERT_TRUE(res == tmp2);
  ASSERT_TRUE(res != tmp1);
}

TEST(Voting, getname3)
{
  election e;
  (&e)->numCand = 20;
  std::string tmp1 = "Downing";
  std::string tmp2 = "Austin";
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp1);
  (&e)->addName(tmp2);
  std::string res1 = (*((&e)->getName(18)));
  std::string res2 = (*((&e)->getName(19)));
  ASSERT_TRUE(res1 == tmp1);
  ASSERT_TRUE(res2 == tmp2);
}

//vote and getBallot
TEST(Voting, vote1)
{
  election e;
  (&e)->numCand = 4;
  std::string name1 = "A";
  std::string name2 = "B";
  std::string name3 = "C";
  std::string name4 = "D";
  (&e)->addName(name1); 
  (&e)->addName(name2); 
  (&e)->addName(name3); 
  (&e)->addName(name4); 
  (&e)->vote(0, 1);
  (&e)->vote(0, 2);
  (&e)->vote(0, 3);
  (&e)->vote(0, 4);
  int i = *((&e)->getBallot(0, 1));
  ASSERT_TRUE(i == 2);
}

TEST(Voting, vote2)
{
  election e;
  (&e)->numCand = 3;
  std::string name1 = "A";
  std::string name2 = "B";
  std::string name3 = "C";
  (&e)->addName(name1);
  (&e)->addName(name2);
  (&e)->addName(name3);
  (&e)->vote(0, 1);
  (&e)->vote(0, 3);
  (&e)->vote(0, 2);
  (&e)->vote(1, 3);
  (&e)->vote(1, 2);
  (&e)->vote(1, 1);
  (&e)->vote(2, 1);
  (&e)->vote(2, 2);
  (&e)->vote(2, 3);
  int i = *((&e)->getBallot(0, 0));
  int j = *((&e)->getBallot(1, 1));
  int k = *((&e)->getBallot(2, 2));
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 2);
  ASSERT_TRUE(k == 3);
  
}
//read

TEST(Voting, read1) {
        election data;
	std::istringstream in("3\nJohn\nAustin\nDowning\n2 2 2\n1 2 3\n3 2 1");
	election_read(in, &data);
	ASSERT_TRUE(data.numCand == 3);
//        printf("\n\n\n\n\n344444444444444%s", data.name[0]);
        ASSERT_TRUE((*data.getName(0) == "John"));
        ASSERT_TRUE((*data.getName(1) == "Austin"));
        ASSERT_TRUE((*data.getName(2) == "Downing"));
}

TEST(Voting, read2)
{
  election data;
  std::istringstream in("6\nJohn\nAustin\nDowning\nPsy\nSpencer\nRobb\n1 2 3 4 5 6\n2 3 1 4 5 6\n3 1 2 4 5 6\n4 1 2 3 5 6\n5 6 1 4 2 3\n6 1 4 2 3 5");;
  election_read(in, &data);
  ASSERT_TRUE(data.numCand == 6);
        ASSERT_TRUE((*data.getName(0) == "John"));
        ASSERT_TRUE((*data.getName(1) == "Austin"));
        ASSERT_TRUE((*data.getName(2) == "Downing"));
        ASSERT_TRUE((*data.getName(3) == "Psy"));
        ASSERT_TRUE((*data.getName(4) == "Spencer"));
        ASSERT_TRUE((*data.getName(5) == "Robb"));
}

TEST(Voting, read3)
{
  election data;
  std::istringstream in("4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3");
  election_read(in, &data);
  ASSERT_TRUE(data.numCand == 4);
        ASSERT_TRUE((*data.getName(0) == "Peter"));
        ASSERT_TRUE((*data.getName(1) == "James"));
        ASSERT_TRUE((*data.getName(2) == "John"));
        ASSERT_TRUE((*data.getName(3) == "Zebedee"));
  
}

//tally votes
TEST(Voting, tally1)
{
  election e;
  std::istringstream in("4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3");
  election_read(in, &e);
  std::vector<int> tally (20, 0);
  std::vector<bool> elimination(20, 0);
  tally_votes(e.ballots, tally, elimination);
  ASSERT_TRUE(tally.at(0) == 2);
  ASSERT_TRUE(tally.at(1) == 1);
  ASSERT_TRUE(tally.at(2) == 0);
  ASSERT_TRUE(tally.at(3) == 1);
}

TEST(Voting, tally2)
{
  election e;
  std::istringstream in("6\nJohn\nAustin\nDowning\nPsy\nSpencer\nRobb\n1 2 3 4 5 6\n2 3 1 4 5 6\n3 1 2 4 5 6\n4 1 2 3 5 6\n5 6 1 4 2 3\n6 1 4 2 3 5");
  election_read(in, &e);
  std::vector<int> tally (20, 0);
  std::vector<bool> elimination(20, 0);
  tally_votes(e.ballots, tally, elimination);
  ASSERT_TRUE(tally.at(0) == 1);
  ASSERT_TRUE(tally.at(1) == 1);
  ASSERT_TRUE(tally.at(2) == 1);
  ASSERT_TRUE(tally.at(3) == 1);
  ASSERT_TRUE(tally.at(4) == 1);
  ASSERT_TRUE(tally.at(5) == 1);
}

TEST(Voting, tally3)
{
  election e;
  std::istringstream in("3\nJohn\nAustin\nDowning\n2 2 2\n1 2 3\n3 2 1");
  election_read(in, &e);
  std::vector<int> tally (20, 0);
  std::vector<bool> elimination (20, 0);
  tally_votes(e.ballots, tally, elimination);
  ASSERT_TRUE(tally.at(0) == 1);
  ASSERT_TRUE(tally.at(1) == 1);
  ASSERT_TRUE(tally.at(2) == 1);
}
//eval

TEST(Voting, eval1)
{
  election e;
  std::istringstream in("4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3");
  election_read(in, &e);
  std::string s = voting_eval(&e);
  std::string res = "Peter";
  ASSERT_TRUE(s == "Peter\n");
}

TEST(Voting, eval2)
{
  election e;
  std::istringstream in("3\nJohn\nAustin\nDowning\n2 2 2\n1 2 3\n3 2 1");
  election_read(in, &e);
  std::string s = voting_eval(&e);
  std::string r = "John\nAustin\nDowning\n";
  ASSERT_TRUE(s == r); 
}

TEST(Voting, eval3)
{
  election e;
  std::istringstream in("6\nJohn\nAustin\nDowning\nPsy\nSpencer\nRobb\n1 2 3 4 5 6\n2 3 1 4 5 6\n3 1 2 4 5 6\n4 1 2 3 5 6\n5 6 1 4 2 3\n6 1 4 2 3 5");;
  election_read(in, &e);
  std::string s = voting_eval(&e);
  std::string r = "John\nAustin\nDowning\nPsy\nSpencer\nRobb\n";
  ASSERT_TRUE(s == r);
}
//print

TEST(Voting, print1)
{
   std::ostringstream out;
   voting_print(out, "A plz?");
   ASSERT_TRUE(out.str() == "A plz?");
}

TEST(Voting, print2)
{
   std::ostringstream out;
   voting_print(out, "\n\n\n\n\n");
   ASSERT_TRUE(out.str() == "\n\n\n\n\n");
}

TEST(Voting, print3)
{
   std::ostringstream out;
   voting_print(out, "");
   ASSERT_TRUE(out.str() == "");
}
//solve
TEST(Voting, solve1)
{
  std::ostringstream out;
  std::istringstream in("1\n\n3\nJohn\nAustin\nDowning\n1 2 3\n1 2 3\n1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str() == "John\n");
}
TEST(Voting, solve2)
{
  std::ostringstream out;
  std::istringstream in("1\n\n4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str() == "Peter\n");
}

TEST(Voting, solve3)
{
  std::ostringstream out;
  std::istringstream in("2\n\n4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3\n\n3\nJohn\nAustin\nDowning\n1 2 3\n1 2 3\n1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str() == "Peter\n\nJohn\n"); 
}
// getName, also tests the addName function
TEST(Voting, getName1)
{
  election e;
  e.addName("John");
  e.addName("Austin");
  e.addName("Downing");
  ASSERT_TRUE(*e.getName(0) == "John");
}

TEST(Voting, getName2)
{
  election e;
  e.addName(" ");
  e.addName("Austin");
  e.addName("\n");
  ASSERT_TRUE(*e.getName(1) == "Austin");
}

TEST(Voting, getName3)
{
  election e;
  e.addName("Peter");
  e.addName("Kal-el");
  e.addName("Downing");
  ASSERT_TRUE(*e.getName(2) == "Downing");
}
