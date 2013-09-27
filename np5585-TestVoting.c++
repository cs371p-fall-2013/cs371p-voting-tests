#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"


// ----------
// Tie-Bug
// ----------
// Unit tests to reproduce the tie bug for #15 & #16

TEST(Voting, tie_bug) {
  Election e = Election();

  e.add_candidate("John Doe");
  e.add_candidate("Jane Smith");
  e.add_candidate("Sirhan Sirhan");

  pref_t a[] = {0, 1, 3};
  pref_t b[] = {1, 0, 3};
  e.add_ballot(a);
  e.add_ballot(b);

  std::vector<std::string> results = std::vector<std::string>();
  int num_winners = e.compute_winners(results);
  ASSERT_EQ(results.size(), 2);
  ASSERT_EQ(num_winners, 2);

  ASSERT_TRUE(results.back().compare("Jane Smith") == 0);
  results.pop_back();
  ASSERT_TRUE(results.back().compare("John Doe") == 0);
}

// -----------
// RunVoting
// -----------

TEST(RunVoting, test_parse_sample) {
  std::istringstream in("1\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 3 2\n");
  std::ostringstream out;

  parse(in, out);

  ASSERT_TRUE(out.str() == "John Doe\n");
}

TEST(RunVoting, test_parse_spaces_out_correctly) {
  std::istringstream in("3\n\n1\nJohn Doe\n1\n\n1\nJane Smith\n1\n\n1\nSirhan Sirhan\n1\n");
  std::ostringstream out;

  parse(in, out);

  ASSERT_TRUE(out.str() == "John Doe\n\nJane Smith\n\nSirhan Sirhan\n");
}

TEST(RunVoting, test_parse_tie) {  
  std::istringstream in("1\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n");
  std::ostringstream out;
 
  parse(in, out);
 
  ASSERT_TRUE(out.str() == "John Doe\nJane Smith\n");
}

// -----------
// TestVoting
// -----------

TEST(Voting, compute_stats_3) {
  Election e = Election();

  e.add_candidate("a");
  e.add_candidate("b");
  e.add_candidate("c");
  
  size_t counts[]={1, 2, 1};
  size_t mx;
  pref_t mxi[M_CANDIDATES] = {0};
  size_t nxn;
  size_t mn;
  pref_t mni[M_CANDIDATES] = {0};
  size_t nmn;

  e.compute_stats(counts, mx, mxi, nxn, mn, mni, nmn);

  ASSERT_EQ(mx, 2);
  ASSERT_EQ(nmn, 2);
  ASSERT_EQ(nxn, 1);
  ASSERT_EQ(mni[0], 0);
  ASSERT_EQ(mni[1], 2);
  ASSERT_EQ(mxi[0], 1);  
}

TEST(Voting, compute_stats_2) {
  Election e = Election();

  e.add_candidate("a");
  e.add_candidate("b");

  size_t counts[] = {1, 1};
  size_t mx;
  pref_t mxi[M_CANDIDATES] = {0};
  size_t nxn;
  size_t mn;
  pref_t mni[M_CANDIDATES] = {0};
  size_t nmn;

  e.compute_stats(
      counts,
      mx, mxi, nxn, mn, mni, nmn
  );

  ASSERT_EQ(mx, 1);
  ASSERT_EQ(mxi[0], 0);
  ASSERT_EQ(mxi[1], 1);
  ASSERT_EQ(nxn, 2);
  ASSERT_EQ(nmn, 2);
  ASSERT_EQ(mni[0], 0);
  ASSERT_EQ(mni[1], 1);
}

TEST(Voting, compute_stats_1) {

  Election e = Election();

  e.add_candidate("a");
  e.add_candidate("b");
  e.add_candidate("c");
  e.add_candidate("d");
  e.add_candidate("e");

  size_t counts[] = {1, 2, 3, 4, 5};
  size_t mx;
  pref_t mxi[M_CANDIDATES] = {0};
  size_t nxn;
  size_t mn;
  pref_t mni[M_CANDIDATES] = {0};
  size_t nmn;

  e.compute_stats(
      counts,
      mx, mxi, nxn, mn, mni, nmn
  );

  ASSERT_EQ(mx, 5);
  ASSERT_EQ(mxi[0], 4);
  ASSERT_EQ(nxn, 1);
  ASSERT_EQ(mn, 1);
  ASSERT_EQ(nmn, 1);
  ASSERT_EQ(mni[0], 0);

}

TEST(Voting, compute_winners_3) {
  Election e=Election();
  e.add_candidate("John Doe");
  e.add_candidate("Jane Smith");
  
  pref_t a[] = {0, 1};
  pref_t b[] = {1, 0};
  pref_t c[] = {0, 1};
  pref_t d[] = {1, 0};
  e.add_ballot(a);
  e.add_ballot(b);
  e.add_ballot(c);
  e.add_ballot(d);
  
  std::vector<std::string> results = std::vector<std::string>();
  int num_winner = e.compute_winners(results);
  ASSERT_EQ(num_winner, 2);
  ASSERT_EQ(results.size(), 2);
  
  ASSERT_TRUE(results[0].compare("John Doe")==0);
  ASSERT_TRUE(results[1].compare("Jane Smith")==0);

}

TEST(Voting, compute_winners_1) {
  Election e = Election();

  e.add_candidate("John Doe");
  e.add_candidate("Jane Smith");
  e.add_candidate("Sirhan Sirhan");

  pref_t a[] = {0, 1, 2};
  pref_t b[] = {1, 0, 2};
  pref_t c[] = {1, 2, 0};
  pref_t d[] = {0, 1, 2};
  pref_t f[] = {2, 0, 1};
  e.add_ballot(a);
  e.add_ballot(b);
  e.add_ballot(c);
  e.add_ballot(d);
  e.add_ballot(f);

  std::vector<std::string> results = std::vector<std::string>();
  int num_winners = e.compute_winners(results);
  ASSERT_EQ(results.size(), 1);
  ASSERT_EQ(num_winners, 1);

  ASSERT_TRUE(results.back().compare("John Doe") == 0);
}

TEST(Voting, tally_all_3) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  size_t buf[100] = {};
  e.tally_all(buf);
  ASSERT_EQ(buf[0], 0);
  ASSERT_EQ(buf[1], 0);
}

TEST(Voting, tally_all_2) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  pref_t abal[] = {(pref_t)a, (pref_t)b};
  e.add_ballot(abal);

  size_t buf[100] = {};
  e.tally_all(buf);
  ASSERT_EQ(buf[0], 1);
  ASSERT_EQ(buf[1], 0);
}

TEST(Voting, tally_all) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  pref_t abal[] = {(pref_t)a, (pref_t)b};
  pref_t bbal[] = {(pref_t)b, (pref_t)a};
  pref_t cbal[] = {(pref_t)a, (pref_t)b};
  e.add_ballot(abal);
  e.add_ballot(bbal);

  size_t buf[100] = {};
  e.tally_all(buf);
  ASSERT_EQ(buf[0], 1);
  ASSERT_EQ(buf[1], 1);

  e.add_ballot(cbal);
  e.tally_all(buf);
  ASSERT_EQ(buf[0], 2);
  ASSERT_EQ(buf[1], 1);
}

TEST(Voting, tally_candidate_3) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  size_t buf;
  e.tally_candidate(buf, a);
  ASSERT_EQ(buf, 0);
  e.tally_candidate(buf, b);
  ASSERT_EQ(buf, 0);
}

TEST(Voting, tally_candidate_2) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  pref_t abal[] = {(pref_t)a, (pref_t)b};
  e.add_ballot(abal);

  size_t buf;
  e.tally_candidate(buf, a);
  ASSERT_EQ(buf, 1);
  e.tally_candidate(buf, b);
  ASSERT_EQ(buf, 0);
}

TEST(Voting, tally_candidate) {
  Election e = Election();

  size_t a = e.add_candidate("a");
  size_t b = e.add_candidate("b");

  pref_t abal[] = {(pref_t)a, (pref_t)b};
  pref_t bbal[] = {(pref_t)b, (pref_t)a};
  pref_t cbal[] = {(pref_t)a, (pref_t)b};
  e.add_ballot(abal);
  e.add_ballot(bbal);

  size_t buf;
  e.tally_candidate(buf, a);
  ASSERT_EQ(buf, 1);
  e.tally_candidate(buf, b);
  ASSERT_EQ(buf, 1);

  e.add_ballot(cbal);
  e.tally_candidate(buf, a);
  ASSERT_EQ(buf, 2);
  e.tally_candidate(buf, b);
  ASSERT_EQ(buf, 1);
}

TEST(Voting, election_add_candidate) {
  Election e = Election();

  ASSERT_EQ(e.get_num_candidates(), 0);
  ASSERT_EQ(e.add_candidate("a"), 0);

  ASSERT_EQ(e.get_num_candidates(), 1);
  ASSERT_EQ(e.add_candidate("b"), 1);
  ASSERT_EQ(e.get_num_candidates(), 2);
}

TEST(Voting, election_add_ballot) {
  Election e = Election();

  const pref_t arr[] = {1, 2};
  ASSERT_EQ(e.get_num_ballots(), 0);
  try {
    e.add_ballot(arr);
    ASSERT_TRUE(false);
  } catch (const char* msg) {}

  ASSERT_EQ(e.get_num_ballots(), 0);
  e.add_candidate("a");
  e.add_ballot(arr);
  ASSERT_EQ(e.get_num_ballots(), 1);
}





