#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;

std::vector<Candidate> Candidate::candidates(0);

TEST(Ballot, checkChoice_10_candidates) {
    char choices[] = "1 2 3 4 5 6 7 8 9 10";
    Ballot b(choices, 10);
    for (int i = 0; i < 10; i++)
    {
        b.position = i;
        ASSERT_EQ(b.checkChoice(), i);
    }
}

TEST(Ballot, checkChoice_20_candidates) {
    char choices[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    Ballot b(choices, 20);
    for (int i = 0; i < 20; i++)
    {
        b.position = i;
        ASSERT_EQ(b.checkChoice(), i);
    }
}

TEST(Ballot, checkChoice_fail_check_21) {
    char choices[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    Ballot b(choices, 20);
    b.position = 21;
    ASSERT_DEATH(b.checkChoice(), ".*");
}

TEST(Ballot, fromString_fail_bad_num1) {
    char choices[] = "1 2 3 4 5 6 7 -1 9 10";
    Ballot b;
    ASSERT_DEATH(b.fromString(choices, 10), ".*");
}

TEST(Ballot, fromString_fail_duplicate_ballot) {
    char choices[] = "1 2 3 4 5 6 7 10 9 10";
    Ballot b;
    ASSERT_DEATH(b.fromString(choices, 10), ".*");
}

TEST(Ballot, fromString_accept_empty_with_0) {
    char choices[] = "";
    Ballot b;
    b.fromString(choices, 0), ".*";
}

TEST(Ballot, fromString_fail_21) {
    char choices[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
    Ballot b;
    ASSERT_DEATH(b.fromString(choices, 21), ".*");
}

TEST(Ballot, movePosition_fail_past_end) {
    char choices[] = "1 2 3";
    Ballot b(choices, 3);
    b.position = 4;
    ASSERT_DEATH(b.movePosition(), ".*");
}

TEST(Ballot, movePosition_fail_past_20) {
    char choices[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    Ballot b(choices, 20);
    b.position = 20;
    ASSERT_DEATH(b.movePosition(), ".*");
}

class CandidateT : public ::testing::Test {
 protected:

  virtual void SetUp() {
        Candidate::candidates.push_back(candidate1);
        Candidate::candidates.push_back(candidate2);
        Candidate::candidates.push_back(candidate3);
        Candidate::candidates.push_back(candidate4);
  }

  virtual void TearDown() {
        Candidate::candidates.clear();
  }
  // virtual void TearDown() {}

  Candidate candidate1;
  Candidate candidate2;
  Candidate candidate3;
  Candidate candidate4;
};

TEST_F(CandidateT, acceptBallot_1) {
    char choices[] = "1 2 3 4 5 6 7 8 9";
    Candidate::candidates.push_back(candidate1);

    Ballot b(choices, 9);
    candidate1.acceptBallot(&b);
    ASSERT_TRUE(candidate1.ballots.size() == 1);
}

TEST_F(CandidateT, acceptBallot_2) {
    char choices[] = "1 2 3 4";
    Ballot b1(choices, 4);

    Candidate::candidates.push_back(candidate1);
    Ballot b2("4 1 2 3",4);

    candidate1.acceptBallot(&b1);
    candidate1.acceptBallot(&b2);
    ASSERT_TRUE(candidate1.ballots.size() == 2);
}

TEST_F(CandidateT, acceptBallot_3) {
    char choices[] = "1 2 3 4";
    Ballot b1(choices, 4);

    Ballot b2("4 1 2 3",4);


    Candidate candidate2;

    Candidate::candidates.push_back(candidate1);
    Candidate::candidates.push_back(candidate2);
    candidate1.acceptBallot(&b1);
    candidate2.acceptBallot(&b2);

    ASSERT_EQ(candidate1.ballots.size(), 1);
    ASSERT_EQ(candidate2.ballots.size(), 1);
}

TEST_F(CandidateT, giveUpBallot_1) {
    char choices[] = "1 2 3 4 5 6 7 8 9";

    Candidate::candidates.push_back(candidate1);
    Ballot b(choices, 9);
    candidate1.acceptBallot(&b);
    ASSERT_EQ(candidate1.ballots.size(), 1);

    candidate1.isLoser = true;
    candidate1.giveUpBallots();
    ASSERT_TRUE(candidate1.ballots.size() == 0);
}

TEST_F(CandidateT, giveUpBallot_2) {
    char choices[] = "1 2 3 4";
    Ballot b1(choices, 4);

    Ballot b2("4 1 2 3",4);


    Candidate::candidates.push_back(candidate1);

    candidate1.acceptBallot(&b1);
    candidate1.acceptBallot(&b2);
    ASSERT_TRUE(candidate1.ballots.size() == 2);

    candidate1.isLoser = true;
    candidate1.giveUpBallots();
    ASSERT_TRUE(candidate1.ballots.size() == 0);
}

TEST_F(CandidateT, giveUpBallot_3) {
    char choices[] = "1 2 3 4";
    Ballot b1(choices, 4);

    Ballot b2("4 1 2 3",4);


    Candidate candidate2;
    Candidate::candidates.push_back(candidate1);
    Candidate::candidates.push_back(candidate2);

    candidate1.acceptBallot(&b1);
    candidate2.acceptBallot(&b2);
    ASSERT_TRUE(candidate1.ballots.size() == 1 && candidate1.ballots.size() == 1);

    candidate1.isLoser = true;
    candidate2.isLoser = true;

    candidate1.giveUpBallots();
    candidate2.giveUpBallots();
    ASSERT_TRUE(candidate1.ballots.size() == 0 && candidate2.ballots.size() == 0);
}

TEST_F(CandidateT, getVotes_1) {
    Ballot b1("1 2 4 3", 4);
    Ballot b2("1 3 2 4", 4);
    Ballot b3("1 4 2 3", 4);


    Candidate::candidates.push_back(candidate1);


    candidate1.acceptBallot(&b1);
    candidate1.acceptBallot(&b2);
    candidate1.acceptBallot(&b3);

    ASSERT_TRUE(candidate1.getVotes() == 3);
}

TEST_F(CandidateT, getVotes_2) {
    Ballot b1("1 2 3 ", 3);


    Candidate::candidates.push_back(candidate1);

    candidate1.acceptBallot(&b1);

    ASSERT_TRUE(candidate1.getVotes() == 1);
}

TEST_F(CandidateT, getVotes_3) {
    Ballot b1("1 2 4 3", 4);
    Ballot b2("1 3 2 4", 4);
    Ballot b3("1 4 2 3", 4);
    Ballot b4("1 2 4 3", 4);
    Ballot b5("1 3 2 4", 4);
    Ballot b6("1 4 2 3", 4);
    Ballot b7("1 2 4 3", 4);
    Ballot b8("1 3 2 4", 4);
    Ballot b9("1 4 2 3", 4);



    Candidate::candidates.push_back(candidate1);

    candidate1.acceptBallot(&b1);
    candidate1.acceptBallot(&b2);
    candidate1.acceptBallot(&b3);
    candidate1.acceptBallot(&b4);
    candidate1.acceptBallot(&b5);
    candidate1.acceptBallot(&b6);
    candidate1.acceptBallot(&b7);
    candidate1.acceptBallot(&b8);
    candidate1.acceptBallot(&b9);

    ASSERT_TRUE(candidate1.getVotes() == 9);
}

TEST_F(CandidateT, operators_test_1)  {
    Ballot ballots[2] = {};
    Ballot b1("1 2 4 3", 4);

    Candidate::candidates.push_back(candidate1);

    candidate1.ballots.push_back(&b1);

    ASSERT_TRUE(candidate1 > 0);
}

TEST_F(CandidateT, operators_test_2)  {
    Ballot b1("1 2 4 3", 4);
    Ballot b2("1 2 4 3", 4);
    Ballot b3("1 2 4 3", 4);
    Ballot b4("1 2 4 3", 4);

    Candidate::candidates.push_back(candidate1);

    candidate1.ballots.push_back(&b1);
    candidate1.ballots.push_back(&b2);
    candidate1.ballots.push_back(&b3);
    candidate1.ballots.push_back(&b4);

    ASSERT_TRUE(candidate1 > 3);
}

TEST_F(CandidateT, operators_test_3)  {
    Ballot b1("1 2 4 3", 4);
    Ballot b2("1 2 4 3", 4);
    Ballot b3("1 2 4 3", 4);
    Ballot b4("1 2 4 3", 4);

    Candidate::candidates.push_back(candidate1);

    candidate1.ballots.push_back(&b1);
    candidate1.ballots.push_back(&b2);
    candidate1.ballots.push_back(&b3);
    candidate1.ballots.push_back(&b4);

    ASSERT_TRUE(candidate1 > 3);
}

TEST_F(CandidateT, operators_test_4)  {
    Ballot ballots[2] = {};
    Ballot b1("1 2 4 3", 4);

    Candidate::candidates.push_back(candidate1);

    candidate1.ballots.push_back(&b1);

    ASSERT_TRUE(candidate1 < 4);
}

TEST_F(CandidateT, operators_test_5)  {
    Candidate::candidates.push_back(candidate1);

    ASSERT_TRUE(candidate1 < 1 );
}

TEST_F(CandidateT, operators_test_6)  {
    Ballot b1("1 2 4 3", 4);
    Ballot b2("1 2 4 3", 4);
    Ballot b3("1 2 4 3", 4);
    Ballot b4("1 2 4 3", 4);

    Candidate::candidates.push_back(candidate1);

    candidate1.ballots.push_back(&b1);
    candidate1.ballots.push_back(&b2);
    candidate1.ballots.push_back(&b3);
    candidate1.ballots.push_back(&b4);

    ASSERT_FALSE(candidate1 < 3);
}
