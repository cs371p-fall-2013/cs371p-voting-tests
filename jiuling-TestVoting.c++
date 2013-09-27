
// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>
#include <queue>
#include "gtest/gtest.h"

#include "Voting.h"
using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----
TEST(Voting, read1) {
    ballots =  vector< queue<int> >();
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    const bool b = voting_read(r);
    vector< queue<int> > expected_ballots = vector< queue<int> >();
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(n == 3);
    ASSERT_TRUE(candidates[0].compare("John Doe") == 0);
    ASSERT_TRUE(candidates[1].compare("Jane Smith") == 0);
    ASSERT_TRUE(candidates[2].compare("Sirhan Sirhan") == 0);
    queue<int> row1 = queue<int>();row1.push(0);row1.push(1);row1.push(2);
	queue<int> row2 = queue<int>();row2.push(0);row2.push(1);row2.push(2);
	queue<int> row3 = queue<int>();row3.push(0);row3.push(2);row3.push(1);
	queue<int> row4 = queue<int>();row4.push(0);row4.push(1);row4.push(2);
	queue<int> row5 = queue<int>();row5.push(0);row5.push(2);row5.push(1);
	queue<int> row6 = queue<int>();row6.push(0);row6.push(1);row6.push(2);

	expected_ballots.push_back(row1);
	expected_ballots.push_back(row2);
	expected_ballots.push_back(row3);
	expected_ballots.push_back(row4);
	expected_ballots.push_back(row5);
	expected_ballots.push_back(row6);

	ASSERT_TRUE(ballots.size() == expected_ballots.size());
	for (int i = 0; i < ballots.size(); i++){
		queue<int> row1 = ballots[i];
		queue<int> row2 = expected_ballots[i];
		ASSERT_TRUE(row1.size() == row2.size());
		while (!row1.empty() && !row2.empty()){
			ASSERT_TRUE(row1.front() == row2.front());
			row1.pop();row2.pop();	
		}
	}

}


TEST(Voting, read2) {
    istringstream r("3\nCarmelo Anthony\nLebron James\nChrish Bosh\n3 2 1\n3 2 1\n1 2 3\n");
    ballots =  vector< queue<int> >();
    const bool b = voting_read(r);
    vector< queue<int> > expected_ballots = vector< queue<int> >();
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(n == 3);
    ASSERT_TRUE(candidates[0].compare("Carmelo Anthony") == 0);
    ASSERT_TRUE(candidates[1].compare("Lebron James") == 0);
    ASSERT_TRUE(candidates[2].compare("Chrish Bosh") == 0);
    queue<int> row1 = queue<int>();row1.push(2);row1.push(1);row1.push(0);
	queue<int> row2 = queue<int>();row2.push(2);row2.push(1);row2.push(0);
	queue<int> row3 = queue<int>();row3.push(0);row3.push(1);row3.push(2);

	expected_ballots.push_back(row1);
	expected_ballots.push_back(row2);
	expected_ballots.push_back(row3);

	ASSERT_TRUE(ballots.size() == expected_ballots.size());
	for (int i = 0; i < ballots.size(); i++){
		queue<int> row1 = ballots[i];
		queue<int> row2 = expected_ballots[i];
		ASSERT_TRUE(row1.size() == row2.size());
		while (!row1.empty() && !row2.empty()){
			ASSERT_TRUE(row1.front() == row2.front());
			row1.pop();row2.pop();	
		}
	}

}

TEST(Voting, read3) {
    istringstream r("2\nGoogle\nFacebook\n2 1\n1 2\n");
    ballots =  vector< queue<int> >();
    const bool b = voting_read(r);
    vector< queue<int> > expected_ballots = vector< queue<int> >();
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(n == 2);
    ASSERT_TRUE(candidates[0].compare("Google") == 0);
    ASSERT_TRUE(candidates[1].compare("Facebook") == 0);
    queue<int> row1 = queue<int>();row1.push(1);row1.push(0);
	queue<int> row2 = queue<int>();row2.push(0);row2.push(1);
	expected_ballots.push_back(row1);
	expected_ballots.push_back(row2);

	ASSERT_TRUE(ballots.size() == expected_ballots.size());
	for (int i = 0; i < ballots.size(); i++){
		queue<int> row1 = ballots[i];
		queue<int> row2 = expected_ballots[i];
		ASSERT_TRUE(row1.size() == row2.size());
		while (!row1.empty() && !row2.empty()){
			ASSERT_TRUE(row1.front() == row2.front());
			row1.pop();row2.pop();	
		}
	}

}

TEST(Voting, read4) {
    istringstream r("2\nMicrosoft\nTwitter\n2 1\n1 2\n2 1\n");
    ballots =  vector< queue<int> >();
    const bool b = voting_read(r);
    vector< queue<int> > expected_ballots = vector< queue<int> >();
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(n == 2);
    ASSERT_TRUE(candidates[0].compare("Microsoft") == 0);
    ASSERT_TRUE(candidates[1].compare("Twitter") == 0);
    queue<int> row1 = queue<int>();row1.push(1);row1.push(0);
	queue<int> row2 = queue<int>();row2.push(0);row2.push(1);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(0);
	expected_ballots.push_back(row1);
	expected_ballots.push_back(row2);
	expected_ballots.push_back(row3);
	
	ASSERT_TRUE(ballots.size() == expected_ballots.size());
	for (int i = 0; i < ballots.size(); i++){
		queue<int> row1 = ballots[i];
		queue<int> row2 = expected_ballots[i];
		ASSERT_TRUE(row1.size() == row2.size());
		while (!row1.empty() && !row2.empty()){
			ASSERT_TRUE(row1.front() == row2.front());
			row1.pop();row2.pop();	
		}
	}

}

TEST(Voting, read5) {
    istringstream r("4\nGoogle\nFacebook\nMicrosoft\nTwitter\n4 3 2 1\n1 2 3 4\n");
    ballots =  vector< queue<int> >();
    const bool b = voting_read(r);
    vector< queue<int> > expected_ballots = vector< queue<int> >();
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(n == 4);
    ASSERT_TRUE(candidates[0].compare("Google") == 0);
    ASSERT_TRUE(candidates[1].compare("Facebook") == 0);
    ASSERT_TRUE(candidates[2].compare("Microsoft") == 0);
    ASSERT_TRUE(candidates[3].compare("Twitter") == 0);
    queue<int> row1 = queue<int>();row1.push(3);row1.push(2);row1.push(1);row1.push(0);
	queue<int> row2 = queue<int>();row2.push(0);row2.push(1);row2.push(2);row2.push(3);
	expected_ballots.push_back(row1);
	expected_ballots.push_back(row2);
	
	ASSERT_TRUE(ballots.size() == expected_ballots.size());
	for (int i = 0; i < ballots.size(); i++){
		queue<int> row1 = ballots[i];
		queue<int> row2 = expected_ballots[i];
		ASSERT_TRUE(row1.size() == row2.size());
		while (!row1.empty() && !row2.empty()){
			ASSERT_TRUE(row1.front() == row2.front());
			row1.pop();row2.pop();	
		}
	}

}



TEST(Voting, print1) {
    ostringstream w;
    candidates[0] = "Joe";
    candidates[1] = "Anthony";
    candidates[2] = "James";
    winners = vector<int>();
    winners.push_back(1);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("Anthony\n")==0);

}
TEST(Voting, print2) {
    ostringstream w;
    candidates[0] = "Joe";
    candidates[1] = "Anthony";
    candidates[2] = "James";
    winners = vector<int>();
    winners.push_back(2);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("James\n")==0);

}
TEST(Voting, print3) {
    ostringstream w;
    candidates[0] = "Joe";
    candidates[1] = "Anthony";
    candidates[2] = "James";
    winners = vector<int>();
    winners.push_back(1);
    winners.push_back(2);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("Anthony\nJames\n")==0);

}

TEST(Voting, print4) {
    ostringstream w;
    candidates[0] = "David";
    candidates[1] = "Bosh";
    candidates[2] = "Carmelo";
    winners = vector<int>();
    winners.push_back(0);
    winners.push_back(1);
    winners.push_back(2);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("David\nBosh\nCarmelo\n")==0);

}
TEST(Voting, print5) {
    ostringstream w;
    candidates[0] = "Microsoft";
    candidates[1] = "Twitter";
    candidates[2] = "Facebook";
    winners = vector<int>();
    winners.push_back(0);
    winners.push_back(2);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("Microsoft\nFacebook\n")==0);

}

TEST(Voting, print6) {
    ostringstream w;
    candidates[0] = "Microsoft";
    candidates[1] = "Twitter";
    candidates[2] = "Facebook";
    winners = vector<int>();
    winners.push_back(0);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("Microsoft\n")==0);

}
TEST(Voting, print7) {
    ostringstream w;
    candidates[0] = "A";
    candidates[1] = "B";
    candidates[2] = "C";
    winners = vector<int>();
    winners.push_back(1);
    voting_print(w);
    ASSERT_TRUE(w.str().compare("B\n")==0);

}

TEST(Voting,init){
	voting_init();

	for (int i = 0; i < MAXN; i++){
		ASSERT_TRUE(counts[i] == 0);
		ASSERT_TRUE(ranking[i].size() == 0);
		ASSERT_TRUE(candidates[i].compare("") == 0);
		}

	ASSERT_TRUE(ballots.size() == 0);
	ASSERT_TRUE(winners.size() == 0);
}



TEST(Voting,eval1){
	ostringstream w;
	n= 3;     
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);row1.push(2);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);row2.push(2);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(2);row3.push(0);
	queue<int> row4 = queue<int>();row4.push(0);row4.push(1);row4.push(2);
	queue<int> row5 = queue<int>();row5.push(2);row5.push(0);row5.push(1);
	ballots.push_back(row1);
	ballots.push_back(row2);
	ballots.push_back(row3);
	ballots.push_back(row4);
	ballots.push_back(row5);

	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 0 );

}

TEST(Voting,eval2){
	ostringstream w;
	n= 3;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);row1.push(2);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);row2.push(2);
	ballots.push_back(row1);
	ballots.push_back(row2);

	voting_eval(w);
	ASSERT_TRUE(winners.size() == 2);
	ASSERT_TRUE(winners[0] == 0 );
	ASSERT_TRUE(winners[1] == 1 );

}

TEST(Voting,eval3){
	ostringstream w;
	n= 3;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);row1.push(2);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);row2.push(2);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(0);row3.push(2);
	ballots.push_back(row1);
	ballots.push_back(row2);
	ballots.push_back(row3);

	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 1 );

}

TEST(Voting,eval8){
	ostringstream w;
	n= 3;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);row1.push(2);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);row2.push(2);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(0);row3.push(2);
	queue<int> row4 = queue<int>();row4.push(1);row4.push(0);row4.push(2);
	queue<int> row5 = queue<int>();row5.push(0);row5.push(1);row5.push(2);
	ballots.push_back(row1);
	ballots.push_back(row2);
	ballots.push_back(row3);
	ballots.push_back(row4);
	ballots.push_back(row5);

	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 1 );

}

TEST(Voting,eval4){
	ostringstream w;
	n= 2;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(0);
	queue<int> row4 = queue<int>();row4.push(1);row4.push(0);
	queue<int> row5 = queue<int>();row5.push(0);row5.push(1);
	ballots.push_back(row1);
	ballots.push_back(row2);
	ballots.push_back(row3);
	ballots.push_back(row4);
	ballots.push_back(row5);

	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 1 );

}

TEST(Voting,eval5){
	ostringstream w;
	n= 2;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);
	ballots.push_back(row1);
	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 0 );
}

TEST(Voting,eval6){
	ostringstream w;
	n= 2;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);
	ballots.push_back(row1);
	ballots.push_back(row2);
	voting_eval(w);
	ASSERT_TRUE(winners.size() == 2);
	ASSERT_TRUE(winners[0] == 0 );
	ASSERT_TRUE(winners[1] == 1 );
}

TEST(Voting,eval7){
	ostringstream w;
	n= 2;
	for (int i = 0; i < MAXN; i++){
			counts[i] = 0;
			ranking[i] = queue<int>();
			candidates[i] = "";
			ballots = vector< queue<int> >();
		}
	winners = vector<int>();
	queue<int> row1 = queue<int>();row1.push(0);row1.push(1);
	queue<int> row2 = queue<int>();row2.push(1);row2.push(0);
	queue<int> row3 = queue<int>();row3.push(1);row3.push(0);
	ballots.push_back(row1);
	ballots.push_back(row2);
	ballots.push_back(row3);
	voting_eval(w);
	ASSERT_TRUE(winners.size() == 1);
	ASSERT_TRUE(winners[0] == 1 );
}

//solve
TEST(voting_solve, solve_1)
{
  std::ostringstream out;
  std::istringstream in("1\n\n3\nJohn\nAustin\nDowning\n1 2 3\n1 2 3\n1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str().compare("John\n")==0);
}
TEST(voting_solve, solve_2)
{
  std::ostringstream out;
  std::istringstream in("1\n\n4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str().compare("Peter\n") == 0);
}

TEST(voting_solve, solve_3)
{
  std::ostringstream out;
  std::istringstream in("2\n\n4\nPeter\nJames\nJohn\nZebedee\n1 2 3 4\n2 1 4 3\n1 3 2 4\n4 1 2 3\n\n3\nJohn\nAustin\nDowning\n1 2 3\n1 2 3\n1 2 3");
  voting_solve(in, out);
  ASSERT_TRUE(out.str().compare("Peter\n\nJohn\n") == 0);
}


TEST(voting_solve, solve_4) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("John Doe\n") ==0);
}

TEST(Voting, solve_5)
{
    std::istringstream r("1\n\n3\nAbe\nBear\nCharlie\n1 2 3\n1 3 2\n1 2 3\n2 3 1\n2 1 3\n3 2 1\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("Abe\n") == 0);
}

TEST(voting_solve, solve_6) {
    std::istringstream r("1\n\n3\nJoe\nPhil\na\n3 2 1\n3 1 2");
    std::ostringstream w;
    voting_solve(r, w);

    ASSERT_TRUE(w.str().compare("a\n") == 0);
}

TEST(voting_solve, solve_7)
{
    std::istringstream r("1\n\n6\nAbe\nBay\nCat\nDog\nEel\nFat\n1 2 3 4 5 6");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("Abe\n") == 0);
}


TEST(voting_solve, solve_8)
{
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("John Doe\n\nRed\nGreen\n") == 0);
}

TEST(voting_solve, solve_10)
{
    std::istringstream r("1\n\n5\nK\nE\nV\nI\nN\n1 2 3 4 5\n2 1 3 4 5\n3 1 2 4 5\n4 1 2 3 5\n5 1 2 3 4");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str().compare("K\nE\nV\nI\nN\n") == 0);
}
