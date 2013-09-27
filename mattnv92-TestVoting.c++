#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Voting.h"

TEST(Voting, readTestNumber1){
	using namespace std;
	istringstream in("8");
	int numTests = -1;
	readTestNumber(in, numTests);
	assert(numTests == 8);
}
 
TEST(Voting, readTestNumber2){
	using namespace std;
	istringstream in("6, 5");
	int numTests = -1;
	readTestNumber(in, numTests);
	assert(numTests == 6);
}
 
TEST(Voting, readTestNumber3){
	using namespace std;
	istringstream in("80987");
	int numTests = -1;
	readTestNumber(in, numTests);
	assert(numTests == 80987);
}

TEST(Voting, readNumberCandidates1){
	using namespace std;
	istringstream in("5");
	int numCandidates;
	readNumberCandidates(in, numCandidates);
	assert(numCandidates == 5);
}

TEST(Voting, readNumberCandidates2){
	using namespace std;
	istringstream in("18");
	int numCandidates;
	readNumberCandidates(in, numCandidates);
	assert(numCandidates == 18);
}

TEST(Voting, readNumberCandidates3){
	using namespace std;
	istringstream in("10");
	int numCandidates;
	readNumberCandidates(in, numCandidates);
	assert(numCandidates == 10);
}


TEST(Voting, readCandidateNames1){
	using namespace std;
	int numCandidates = 3;
	istringstream in("Howard\nFrank\nJeeby");
	vector<Candidate> candidateList (0);			
	readCandidateNames(in, candidateList, numCandidates);
	assert(candidateList.at(0).name.compare("Howard") == 0);
}
 
TEST(Voting, readCandidateNames2){
	using namespace std;
	int numCandidates = 3;
	istringstream in("Howard\nFrank\nDavis\nGeorge");
	vector<Candidate> candidateList (0);			
	readCandidateNames(in, candidateList, numCandidates);
	assert(candidateList.at(2).name.compare("Davis") == 0);
}
 
TEST(Voting, readCandidateNames3){
	using namespace std;
	int numCandidates = 3;
	istringstream in("Howard\nFrank\nJeeby");
	vector<Candidate> candidateList (0);			
	readCandidateNames(in, candidateList, numCandidates);
	candidateList.erase(candidateList.begin());
	assert(candidateList.at(0).name.compare("Frank") == 0);
}

TEST(Voting, readBallots1){
	using namespace std;
	int numBallots = 0;
	vector<Candidate> candidateList (0);
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	istringstream in("1 2 3 4\n");
	readBallots(in, candidateList, numBallots);
	assert(candidateList.at(0).ballotList.size() == 1);

}
 
TEST(Voting, readBallots2){
	using namespace std;
	vector<Candidate> candidateList (0);
	int numBallots = 0;
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	Candidate b;
	b.name = "Bijee Smullz";
	candidateList.push_back(b);
	Candidate c;
	c.name = "TooPack Chakure";
	candidateList.push_back(c);
	istringstream in("1 2 3 \n2 1 3\n3 1 2");
	readBallots(in, candidateList, numBallots);
	assert(candidateList.at(0).ballotList.size() == 1);
	assert(candidateList.at(1).ballotList.size() == 1);
	assert(candidateList.at(2).ballotList.size() == 1);
} 

TEST(Voting, readBallots3){
	using namespace std;
	int numBallots = 0;
	vector<Candidate> candidateList (0);
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	Candidate b;
	b.name = "Bijee Smullz";
	candidateList.push_back(b);
	Candidate c;
	c.name = "TooPack Chakure";
	candidateList.push_back(c);
	istringstream in("");
	readBallots(in, candidateList, numBallots);
	assert(candidateList.at(0).ballotList.size() == 0);
	assert(candidateList.at(1).ballotList.size() == 0);
	assert(candidateList.at(2).ballotList.size() == 0);
} 

TEST(Voting, findWinner1){
	using namespace std;
	vector<Candidate> candidateList (0);
	vector<int> candidateStack (0);
	int numBallots = 0;
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	Candidate b;
	b.name = "Bijee Smullz";
	candidateList.push_back(b);
	Candidate c;
	c.name = "TooPack Chakure";
	candidateList.push_back(c);
	istringstream in("1 2 3\n");
	readBallots(in, candidateList, numBallots);
	Outcome result = findWinner(candidateList, candidateStack, numBallots);
	assert(result == WINNER);
}

TEST(Voting, findWinner2){
	using namespace std;
	vector<Candidate> candidateList (0);
	vector<int> candidateStack (0);
	int numBallots = 0;
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	Candidate b;
	b.name = "Bijee Smullz";
	candidateList.push_back(b);
	Candidate c;
	c.name = "TooPack Chakure";
	candidateList.push_back(c);
	istringstream in("1 2 3\n1 2 3\n3 2 1\n3 2 1\n2 3 1");
	readBallots(in, candidateList, numBallots);
	Outcome result = NO_WINNER;
	while(result == NO_WINNER)
		result = findWinner(candidateList, candidateStack, numBallots);
	assert(result == WINNER);
	assert(candidateStack.at(0) == 2);
}

TEST(Voting, findWinner3){
	using namespace std;
	vector<Candidate> candidateList (0);
	vector<int> candidateStack (0);
	int numBallots = 0;
	Candidate a;
	a.name = "Ron Jeremy";
	candidateList.push_back(a);
	Candidate b;
	b.name = "Bijee Smullz";
	candidateList.push_back(b);
	Candidate c;
	c.name = "TooPack Chakure";
	candidateList.push_back(c);
	Candidate d;
	c.name = "ComeyMummy";
	candidateList.push_back(c);
	istringstream in("1 2 3 4\n4 1 2 3\n3 2 4 1\n2 3 1 4");
	readBallots(in, candidateList, numBallots);
	Outcome result = NO_WINNER;
	while(result == NO_WINNER)
		result = findWinner(candidateList, candidateStack, numBallots);
	assert(result == TIE);
	assert(candidateStack.size() == 4);
}
