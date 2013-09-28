// --------
// includes
// --------

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"

#include "Voting.h"

// --------
// global
// --------

TEST(Voting, getCandidates1) 
{
    numberOfCandidates = 4;
    std::istringstream r("Matthew\nMark\nLuke\nJohn");
    getCandidates( r );

    ASSERT_TRUE( rc(0) == "Matthew");
    ASSERT_TRUE( rc(1) == "Mark");
    ASSERT_TRUE( rc(2) == "Luke");
    ASSERT_TRUE( rc(3) == "John");
}

TEST(Voting, getCandidates2) 
{
    numberOfCandidates = 2;
    std::istringstream r("Supercalifragilisticexpialidocious\nGregor Samsa awake one moring from uneasy dreams");
    getCandidates( r );

    ASSERT_TRUE( rc(0) == "Supercalifragilisticexpialidocious");
    ASSERT_TRUE( rc(1) == "Gregor Samsa awake one moring from uneasy dreams");
}

TEST(Voting, getCandidates3) 
{
    numberOfCandidates = 20;
    std::istringstream r("a a\nb b\nc c\nd d\ne e\nf f\ng g\nh h\ni i\nj j\nk k\nl l\nm m\nn n\no o\np p\nq q\nr r\ns s\nt t");
    getCandidates( r );

    ASSERT_TRUE( rc(0) == "a a");
    ASSERT_TRUE( rc(1) == "b b");
    ASSERT_TRUE( rc(2) == "c c");
    ASSERT_TRUE( rc(3) == "d d");
    ASSERT_TRUE( rc(4) == "e e");
    ASSERT_TRUE( rc(5) == "f f");
    ASSERT_TRUE( rc(6) == "g g");
    ASSERT_TRUE( rc(7) == "h h");
    ASSERT_TRUE( rc(8) == "i i");
    ASSERT_TRUE( rc(9) == "j j");
    ASSERT_TRUE( rc(10) == "k k");
    ASSERT_TRUE( rc(11) == "l l");
    ASSERT_TRUE( rc(12) == "m m");
    ASSERT_TRUE( rc(13) == "n n");
    ASSERT_TRUE( rc(14) == "o o");
    ASSERT_TRUE( rc(15) == "p p");
    ASSERT_TRUE( rc(16) == "q q");
    ASSERT_TRUE( rc(17) == "r r");
    ASSERT_TRUE( rc(18) == "s s");
    ASSERT_TRUE( rc(19) == "t t");
}

TEST(Voting, load_votes1)
{
    ballots.clear();
    totalBallots = 0;
    std::istringstream r("1 2 3 4\n5 4 3 2\n");
    load_votes( r );
    ASSERT_TRUE(totalBallots == 2);
}

TEST(Voting, load_votes2)
{
    ballots.clear();
    totalBallots = 0;
    std::istringstream r("11 10 9 8 7 6 5 4 3 2 1\n1 2 3 4 5 6 7 8 9 10 11\n2 4 6 8 10 1 3 5 7 9\n1 3 5 7 9 11 2 4 6 8 10");
    load_votes( r );
    ASSERT_TRUE(totalBallots == 4);
}

TEST(Voting, load_votes3)
{
    ballots.clear();
    totalBallots = 0;
    std::istringstream r("1 2\n2 1\n1 2\n1 2\n2 1\n1 2\n2 1\n2 1\n1 2\n1 2\n2 1");
    load_votes( r );
    ASSERT_TRUE(totalBallots == 11);
}

TEST(Voting, count_votes1)
{
    int i = 0;
    std::vector< std::vector<int> > forCounting;
    while(i < 20)
    {
        std::vector<int> foo;
        foo.push_back(i);
        forCounting.push_back(foo);
        i++;
    }
    i = count_votes( forCounting );
    ASSERT_TRUE(i == 20);
}

TEST(Voting, count_votes2)
{
    int i = 0;
    std::vector< std::vector<int> > forCounting;
    while(i < 80)
    {
        std::vector<int> foo;
        foo.push_back(i);
        forCounting.push_back(foo);
        i++;
    }
    i = count_votes( forCounting );
    ASSERT_TRUE(i == 80);
}

TEST(Voting, count_votes3)
{
    int i = 0;
    std::vector< std::vector<int> > forCounting;
    while(i < 64)
    {
        std::vector<int> foo;
        foo.push_back(i);
        forCounting.push_back(foo);
        i++;
    }
    i = count_votes( forCounting );
    ASSERT_TRUE(i == 64);
}

TEST(Voting, process_votes1)
{
    std::istringstream r("3\nBlack\nWhite\nGray\n1 2 3\n3 2 1\n3 1 2\n2 1 3\n");
    std::vector<std::string> out;
 	getCandidates( r );
	load_votes( r );
    out = process_votes();
    ASSERT_TRUE(out.at(0) == "3");
}

TEST(Voting, process_votes2)
{
    std::istringstream r("4\nPoe\nTwain\nMelville\nKafka\n4 3 2 1\n4 3 2 1\n3 1 2 4\n1 2 3 4\n3 4 1 2\n4 1 3 2\n4 2 3 1\n");
    std::vector<std::string> out;
    getCandidates( r );
    load_votes( r );
    out = process_votes();
    ASSERT_TRUE(out.at(0) == "4");
}

TEST(Voting, process_votes3)
{
    std::istringstream r("2\nLeft\nRight\n2 1\n2 1\n1 2\n1 2\n1 2\n1 2\n2 1\n");
    std::vector<std::string> out;
    getCandidates( r );
    load_votes( r );
    out = process_votes();
    // ASSERT_TRUE(out.at(0) == "2");
}