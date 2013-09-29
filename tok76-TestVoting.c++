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


#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <vector> //vector
#include "gtest/gtest.h"
#include "Voting.h"
using namespace std;

TEST(Voting, start_1)
{
	std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
	std::ostringstream w;
	voting_start(r, w);
	ASSERT_TRUE(w.str().compare("John Smith"));
}

TEST(Voting, start_2)
{
	std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n2 1 3\n2 1 3\n1 3 2\n3 1 2\n2 1 3\n2 3 1\n");
	std::ostringstream w;
	voting_start(r, w);
	ASSERT_TRUE(w.str().compare("Jane Doe"));
}

TEST(Voting, start_3)
{
	std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n3 1 2\n3 2 1\n1 3 2\n1 2 3\n3 1 2\n3 2 1\n");
	std::ostringstream w;
	voting_start(r, w);
	ASSERT_TRUE(w.str().compare("Jack Shepard"));
}

TEST(Voting, readinput_1)
{
	std::istringstream r("3\nJohn Smith\nJane Doe\nJack Shepard\n2 1 3\n2 1 3\n1 3 2\n3 1 2\n2 1 3\n2 3 1\n");
	int winnerindex = voting_readInput(r);
	ASSERT_TRUE(winnerindex == 1);
}

TEST(Voting, readinput_2)
{
	std::istringstream r("4\nDara\nTolu\nCamryn\nBobby\n4 2 3 1\n4 2 1 3\n4 1 3 2\n4 3 1 2\n4 2 1 3\n2 3 4 1\n");
	int winnerindex = voting_readInput(r);
	ASSERT_TRUE(winnerindex == 3);
}

TEST(Voting, readinput_3)
{
	std::istringstream r("2\nMary Kate\nAshley\n1 2\n2 1\n1 2\n");
	int winnerindex = voting_readInput(r);
	ASSERT_TRUE(winnerindex == 0);
}

TEST(Voting, getWinner_1)
{
	string allnames[] = {"John Doe", "April", "May", "June", "July"};
	int winnerindex = 2;
	int maxvotes = 0;
	std::ostringstream w;
	voting_getwinner(winnerindex, maxvotes, w, allnames);
	ASSERT_TRUE(w.str().compare("May"));
}

TEST(Voting, getWinner_2)
{
	string allnames[] = {"Leonardo", "Michelangelo", "Raphael", "Donatello"};
	int winnerindex = 1;
	int maxvotes = 0;
	std::ostringstream w;
	voting_getwinner(winnerindex, maxvotes, w, allnames);
	ASSERT_TRUE(w.str().compare("Michelangelo"));
}

TEST(Voting, getWinner_3)
{

	string allnames[] = {"Mary Kate", "Ashley"};
	int winnerindex = 1;
	int maxvotes = 0;
	std::ostringstream w;
	voting_getwinner(winnerindex, maxvotes, w, allnames);
	ASSERT_TRUE(w.str().compare("Ashley"));
}

