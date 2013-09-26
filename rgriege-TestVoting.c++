#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <list>

#include "gtest/gtest.h"
#include "Voting.h"

bool check_ballots(int real_ballots[][20], std::list<std::list<int>> input_ballots[20], int num_ballots, int num_candidates)
{
  for (int i =0; i < num_ballots; i++) {
    int first = real_ballots[i][0];
    std::list<std::list<int>>candidate = input_ballots[first - 1];
    std::list<std::list<int>>::iterator it = candidate.begin();
    while (it != candidate.end()) {
      int count = 0;
      std::list<int> ballot = *it;
      for (auto &vote : ballot) {
        if (vote != real_ballots[i][count])
          break;
        count++;
      }
      if (count == num_candidates) {
        candidate.erase(it);
        break;
      }
      it++;
    }
    if (it == candidate.end())
      return false;
  }
  return true;
}

// ----
// read
// ----

TEST(Voting, read_1)
{
  std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
  std::string names[20];
  std::list<std::list<int>> ballots[20];
  const bool b = voting_read(r, names, ballots);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(names[0] == "John Doe");
  ASSERT_TRUE(names[1] == "Jane Smith");
  ASSERT_TRUE(names[2] == "Sirhan Sirhan");
  int real_ballots[5][20] = {
    {1, 2, 3},
    {1, 2, 3},
    {2, 1, 3},
    {2, 3, 1},
    {3, 1, 2}
  };
  bool m = check_ballots(real_ballots, ballots, 5, 3);
  ASSERT_TRUE(m == true);
}

TEST(Voting, read_one_candidate)
{
  std::istringstream r("1\nJohn Doe\n1\n1\n1\n1\n1");
  std::string names[20];
  std::list<std::list<int>> ballots[20];
  const bool b = voting_read(r, names, ballots);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(names[0] == "John Doe");
  int real_ballots[5][20] = {
    {1},
    {1},
    {1},
    {1},
    {1}
  };
  bool m = check_ballots(real_ballots, ballots, 5, 1);
  ASSERT_TRUE(m == true);
}

TEST(Voting, read_one_ballot)
{
  std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3");
  std::string names[20];
  std::list<std::list<int>> ballots[20];
  const bool b = voting_read(r, names, ballots);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(names[0] == "John Doe");
  ASSERT_TRUE(names[1] == "Jane Smith");
  ASSERT_TRUE(names[2] == "Sirhan Sirhan");
  int real_ballots[1][20] = {
    {1, 2, 3}
  };
  bool m = check_ballots(real_ballots, ballots, 1, 3);
  ASSERT_TRUE(m == true);
}

TEST(Voting, read_one_ballot_newline)
{
  std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n");
  std::string names[20];
  std::list<std::list<int>> ballots[20];
  const bool b = voting_read(r, names, ballots);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(names[0] == "John Doe");
  ASSERT_TRUE(names[1] == "Jane Smith");
  ASSERT_TRUE(names[2] == "Sirhan Sirhan");
  int real_ballots[1][20] = {
    {1, 2, 3}
  };
  bool m = check_ballots(real_ballots, ballots, 1, 3);
  ASSERT_TRUE(m == true);
}

// -----
// write
// -----

TEST(Voting, write_1)
{
  std::ostringstream w;
  std::string name = "John Doe";
  voting_print(w, name);
  ASSERT_TRUE(w.str() == name + "\n");
}

// ----
// eval
// ----

TEST(Voting, eval_1)
{
  std::string names[20] = { "John Doe", "Jane Smith", "Sirhan Sirhan" };
  std::list<std::list<int>> ballots[20];
  int real_ballots[5][3] = {
    {1, 2, 3},
    {2, 1, 3},
    {2, 3, 1},
    {1, 2, 3},
    {3, 1, 2}
  };
  ballots[0].push_back(std::list<int>(real_ballots[0], real_ballots[0]+3));
  ballots[0].push_back(std::list<int>(real_ballots[3], real_ballots[3]+3));
  ballots[1].push_back(std::list<int>(real_ballots[2], real_ballots[2]+3));
  ballots[1].push_back(std::list<int>(real_ballots[1], real_ballots[1]+3));
  ballots[2].push_back(std::list<int>(real_ballots[4], real_ballots[4]+3));
  std::vector<std::string> winning_names;
  voting_eval(names, ballots, winning_names);
  ASSERT_TRUE(winning_names.size() == 1);
  ASSERT_TRUE(winning_names[0] == "John Doe");
}

TEST(Voting, eval_tie)
{
  std::string names[20] = { "John Doe", "Jane Smith", "Sirhan Sirhan" };
  std::list<std::list<int>> ballots[20];
  int real_ballots[6][3] = {
    {1, 2, 3},
    {2, 1, 3},
    {2, 3, 1},
    {1, 2, 3},
    {3, 1, 2},
    {3, 1, 2}
  };
  ballots[0].push_back(std::list<int>(real_ballots[0], real_ballots[0]+3));
  ballots[0].push_back(std::list<int>(real_ballots[3], real_ballots[3]+3));
  ballots[1].push_back(std::list<int>(real_ballots[2], real_ballots[2]+3));
  ballots[1].push_back(std::list<int>(real_ballots[1], real_ballots[1]+3));
  ballots[2].push_back(std::list<int>(real_ballots[4], real_ballots[4]+3));
  ballots[2].push_back(std::list<int>(real_ballots[5], real_ballots[5]+3));

  std::vector<std::string> winning_names;
  voting_eval(names, ballots, winning_names);
  ASSERT_TRUE(winning_names.size() == 3);
  ASSERT_TRUE(winning_names[0] == "John Doe");
  ASSERT_TRUE(winning_names[1] == "Jane Smith");
  ASSERT_TRUE(winning_names[2] == "Sirhan Sirhan");
}

TEST(Voting, eval_three_rounds)
{
  std::string names[20] = { "John Doe", "Jane Smith", "Sirhan Sirhan", "Lee Harvey" };
  std::list<std::list<int>> ballots[20];
  int real_ballots[7][4] = {
    {1, 2, 3, 4},
    {2, 1, 3, 4},
    {2, 3, 1, 4},
    {1, 2, 3, 4},
    {3, 1, 2, 4},
    {3, 1, 2, 4},
    {4, 2, 1, 3} 
  };
  ballots[0].push_back(std::list<int>(real_ballots[0], real_ballots[0]+3));
  ballots[0].push_back(std::list<int>(real_ballots[3], real_ballots[3]+3));
  ballots[1].push_back(std::list<int>(real_ballots[2], real_ballots[2]+3));
  ballots[1].push_back(std::list<int>(real_ballots[1], real_ballots[1]+3));
  ballots[2].push_back(std::list<int>(real_ballots[4], real_ballots[4]+3));
  ballots[2].push_back(std::list<int>(real_ballots[5], real_ballots[5]+3));
  ballots[3].push_back(std::list<int>(real_ballots[6], real_ballots[6]+3));
  std::vector<std::string> winning_names;
  voting_eval(names, ballots, winning_names);
  ASSERT_TRUE(winning_names.size() == 1);
  ASSERT_TRUE(winning_names[0] == "Jane Smith");
}
// -----
// solve
// -----


TEST(Voting, solve_1)
{
  std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
  std::ostringstream w;
  
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "John Doe\n");
}

TEST(Voting, solve_multi)
{
  std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nRyan Greeeeg\nBlake Shalom\n1 2\n2 1\n1 2\n2 1");
  std::ostringstream w;
  
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "John Doe\n\nRyan Greeeeg\nBlake Shalom\n");

}

TEST(Voting, solve_multi_tie) 
{
  std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 1 2\n\n2\nRyan Greeeeg\nBlake Shalom\n1 2\n2 1\n1 2\n2 1");
  std::ostringstream w;
  
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n\nRyan Greeeeg\nBlake Shalom\n");
}

TEST(Voting, solve_one_candidate)
{
  std::istringstream r("1\n\n1\nBeez Kneez\n1\n1\n1");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_TRUE(w.str() == "Beez Kneez\n");
}

