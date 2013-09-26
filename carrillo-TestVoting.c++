#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Voting.h"

TEST(Voting, read_ballot1){
    using namespace std;
    ballot b;
    vector<Candidate> c;
    c.push_back(Candidate("A"));
    c.push_back(Candidate("B"));
    c.push_back(Candidate("C"));
    istringstream r("1 2 3");
    read_ballot(r, c, b);
    ASSERT_EQ(c.size(), b.size());
    for (unsigned int i = 0; i < b.size(); i++){
        ASSERT_EQ(&c.at(i), b.at(i));
    }
}

TEST(Voting, empty_ballot){
    using namespace std;
    vector<Candidate> c;
    ballot b;
    istringstream r("");
    ASSERT_FALSE(read_ballot(r, c, b));
}

TEST(Voting, full_ballot){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("A"));
    c.push_back(Candidate("B"));
    c.push_back(Candidate("C"));
    ballot b;
    istringstream r("3 2 1");
    ASSERT_TRUE(read_ballot(r, c, b));
}

TEST(Voting, election_revote){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("Bob"));
    c.push_back(Candidate("Jane"));
    c.push_back(Candidate("Smith"));
    ballot_box votes;
    ballot b;
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]);
    b.push_back(&c[0]);
    b.push_back(&c[2]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[2]);
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    votes.push_back(b);
    ASSERT_STREQ("Bob\n", run_election(c, votes).c_str());
}

TEST(Voting, election_majority){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("Bob"));
    c.push_back(Candidate("Jane"));
    c.push_back(Candidate("Smith"));
    ballot_box votes;
    ballot b;
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    votes.push_back(b);
    ASSERT_STREQ("Bob\n", run_election(c, votes).c_str());
}

TEST(Voting, election_revote_advance_twice){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("Bob"));
    c.push_back(Candidate("Jane"));
    c.push_back(Candidate("Smith"));
    ballot_box votes;
    ballot b;
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[0]);
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]);
    b.push_back(&c[2]);
    b.push_back(&c[0]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[2]);
    b.push_back(&c[1]);
    b.push_back(&c[0]);
    votes.push_back(b);
    ASSERT_STREQ("Bob\n", run_election(c, votes).c_str());
}

TEST(Voting, election_revote_no_vote_candidate){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("Bob"));
    c.push_back(Candidate("Jane"));
    c.push_back(Candidate("Smith"));
    c.push_back(Candidate("Glen"));
    ballot_box votes;
    ballot b;
    b.push_back(&c[0]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[0]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[2]); b.push_back(&c[1]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    ASSERT_STREQ("Bob\n", run_election(c, votes).c_str());
}

TEST(Voting, election_revote_multistep){
    using namespace std;
    vector<Candidate> c;
    c.push_back(Candidate("Bob"));
    c.push_back(Candidate("Jane"));
    c.push_back(Candidate("Smith"));
    c.push_back(Candidate("Glen"));
    ballot_box votes;
    ballot b;
    b.push_back(&c[0]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[0]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]); b.push_back(&c[0]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[0]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[3]); b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[0]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[2]); b.push_back(&c[1]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[2]); b.push_back(&c[1]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    b.clear();
    b.push_back(&c[1]); b.push_back(&c[2]); b.push_back(&c[0]); b.push_back(&c[3]);
    votes.push_back(b);
    ASSERT_STREQ("Jane\n", run_election(c, votes).c_str());
}

TEST(Voting, parsing1){
    using namespace std;
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nOther");
    vector<Candidate> names;
    ballot_box ballots;
    parse(r, names, ballots);
    ASSERT_STREQ("John Doe", names[0].name().c_str());
    ASSERT_STREQ("Jane Smith", names[1].name().c_str());
    ASSERT_STREQ("Sirhan Sirhan", names[2].name().c_str());
    
    ASSERT_EQ(5, ballots.size());
    ASSERT_EQ(3, ballots[0].size());
    ASSERT_EQ(3, ballots[1].size());
    ASSERT_EQ(3, ballots[2].size());
    ASSERT_EQ(3, ballots[3].size());
    ASSERT_EQ(3, ballots[4].size());

    ASSERT_EQ(&names[0], ballots[0][0]);
    ASSERT_EQ(&names[1], ballots[0][1]);
    ASSERT_EQ(&names[2], ballots[0][2]);
    ASSERT_EQ(&names[1], ballots[1][0]);
    ASSERT_EQ(&names[0], ballots[1][1]);
    ASSERT_EQ(&names[2], ballots[1][2]);
    ASSERT_EQ(&names[1], ballots[2][0]);
    ASSERT_EQ(&names[2], ballots[2][1]);
    ASSERT_EQ(&names[0], ballots[2][2]);
    ASSERT_EQ(&names[0], ballots[3][0]);
    ASSERT_EQ(&names[1], ballots[3][1]);
    ASSERT_EQ(&names[2], ballots[3][2]);
    ASSERT_EQ(&names[2], ballots[4][0]);
    ASSERT_EQ(&names[0], ballots[4][1]);
    ASSERT_EQ(&names[1], ballots[4][2]);
}

TEST(Voting, parsing2){
    using namespace std;
    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n");
    vector<Candidate> names;
    ballot_box ballots;
    parse(r, names, ballots);
    ASSERT_STREQ("John Doe", names[0].name().c_str());
    ASSERT_STREQ("Jane Smith", names[1].name().c_str());
    ASSERT_STREQ("Sirhan Sirhan", names[2].name().c_str());
    
    ASSERT_EQ(2, ballots.size());
    ASSERT_EQ(3, ballots[0].size());
    ASSERT_EQ(3, ballots[1].size());

    ASSERT_EQ(&names[0], ballots[0][0]);
    ASSERT_EQ(&names[1], ballots[0][1]);
    ASSERT_EQ(&names[2], ballots[0][2]);
    ASSERT_EQ(&names[1], ballots[1][0]);
    ASSERT_EQ(&names[0], ballots[1][1]);
    ASSERT_EQ(&names[2], ballots[1][2]);
}

TEST(Voting, parsing_post){
    using namespace std;
    istringstream r("2\nJohn Doe\nJane Smith\n1 2 3\n2 1 3\n\n5");
    vector<Candidate> names;
    ballot_box ballots;
    parse(r, names, ballots);
    int k;
    r >> k;
    ASSERT_EQ(5, k);
}

TEST(Candidate, return_votes){
    Candidate c("loser");
    Candidate o("other");
    ballot b;
    b.push_back(&c);
    b.push_back(&o);
    c.give_vote(b);
    c.lose();
    c.return_votes();
    ASSERT_EQ(1, o.votes());
}

TEST(Candidate, return_votes_skip){
    Candidate c("loser");
    Candidate a("already lost");
    Candidate o("other");
    ballot b;
    b.push_back(&c);
    b.push_back(&a);
    b.push_back(&o);
    c.give_vote(b);
    c.lose();
    a.lose();
    c.return_votes();
    ASSERT_EQ(1, o.votes());
}

TEST(Candidate, return_votes_empty){
    Candidate c("loser");
    Candidate o("other");
    ballot b;
    b.push_back(&c);
    b.push_back(&o);
    c.give_vote(b);
    c.lose();
    c.return_votes();
    ASSERT_EQ(0, c.votes());
}

TEST(Comparisons, zero){
   Candidate a("a");
   Candidate b("b");
   ASSERT_FALSE(fewer_votes(&a, &b));
}

TEST(Comparisons, more){
   Candidate a("a");
   ballot z;
   a.give_vote(z);
   Candidate b("b");
   ASSERT_FALSE(fewer_votes(&a, &b));
}

TEST(Comparisons, less){
   Candidate a("a");
   Candidate b("b");
   ballot z;
   b.give_vote(z);
   ASSERT_TRUE(fewer_votes(&a, &b));
}

TEST(Comparisons, less2){
   Candidate a("a");
   Candidate b("b");
   ballot z;
   a.give_vote(z);
   b.give_vote(z);
   b.give_vote(z);
   ASSERT_TRUE(fewer_votes(&a, &b));
}
