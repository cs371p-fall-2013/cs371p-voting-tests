// -----------------
// Steven Spohrer
// -----------------

#include "gtest/gtest.h"
#include "Voting.h"

// -- parsing i guess. 
TEST(VoteMachine, parseBallot) {
    std::vector<int> votes;
    std::string voteline = "1 2 3 4";
    VoteMachine::parseBallot(voteline, votes, 4);
    ASSERT_TRUE(votes[0] == 0);
    ASSERT_TRUE(votes[1] == 1);
    ASSERT_TRUE(votes[2] == 2);
    ASSERT_TRUE(votes[3] == 3);

       
}
TEST(VoteMachine, parseBallot_2) {
    std::vector<int> votes;
    std::string voteline = "2 1";
    VoteMachine::parseBallot(voteline, votes, 2);
    ASSERT_TRUE(votes[0] == 1);
    ASSERT_TRUE(votes[1] == 0);
}

TEST(VoteMachine, parseBallot_3) {
    std::vector<int> votes;
    std::string voteline = "2 1 3";
    VoteMachine::parseBallot(voteline, votes, 3);
    ASSERT_TRUE(votes[0] == 1);
    ASSERT_TRUE(votes[1] == 0);
    ASSERT_TRUE(votes[2] == 2);
}

// Canadite::voteCount
TEST(Canadite, votecount1)
{
    Election::Canadite c("t1");
    ASSERT_TRUE(c.voteCount() == 0);
}

TEST(Canadite, canadite2)
{
    Election::Canadite c("t1");
    ASSERT_TRUE(c.name == "t1"); 
}

TEST(Canadite, votecount3)
{
    Election::Canadite c("someothername");
    ASSERT_TRUE(c.name == "someothername");
    ASSERT_TRUE(c.voteCount() == 0); 
}

// -- Ballot::move
TEST(Ballot, move)
{
    Election::CanaditeList cl;
    cl.push_back(Election::Canadite("c1"));
    cl.push_back(Election::Canadite("c2"));
    std::vector<int> prefs;
    prefs.push_back(0);
    prefs.push_back(1);
    Election::Ballot b(prefs, cl);
    ASSERT_TRUE(b.pref_idx == 0);
    b.move(cl);
    ASSERT_TRUE(b.pref_idx == 1); 
       
}

TEST(Ballot, move2)
{
    Election::CanaditeList cl;
    cl.push_back(Election::Canadite("c1"));
    cl.push_back(Election::Canadite("c2"));
    cl.push_back(Election::Canadite("c3"));
                 
    std::vector<int> prefs;
    prefs.push_back(0);
    prefs.push_back(1);
    prefs.push_back(2);
    //(0, 1, 2);
    Election::Ballot b(prefs, cl);
    ASSERT_TRUE(b.pref_idx == 0);
    b.move(cl);
    ASSERT_TRUE(b.pref_idx == 1);
}
TEST(Ballot, move3)
{
    Election::CanaditeList cl;
    cl.push_back(Election::Canadite("c1"));
    std::vector<int> prefs;
    prefs.push_back(0);
    Election::Ballot b(prefs, cl);
    ASSERT_TRUE(b.pref_idx == 0);
}

// --- Election::acceptBallot
TEST(Election, acceptBallot1)
{
    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c2");
    cn.push_back("c3");
    std::ostringstream w; 
    Election e(cn, w);
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    ASSERT_TRUE(e.acceptBallot(v) == 1); 
}

TEST(Election, acceptBallot2)
{
    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c2");
    cn.push_back("c3");

    std::ostringstream w; 
    Election e(cn, w);
    std::vector<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3); 
    ASSERT_TRUE(e.acceptBallot(b) == 1);
    ASSERT_TRUE(e.acceptBallot(b) == 2);
    ASSERT_TRUE(e.acceptBallot(b) == 3); 
}
TEST(Election, acceptBallot3)
{
    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c3");
    std::ostringstream w; 
    Election e(cn, w);
    std::vector<int> b;
    b.push_back(1);
    b.push_back(2); 
    ASSERT_TRUE(e.acceptBallot(b) == 1);
    ASSERT_TRUE(e.acceptBallot(b) == 2);
    ASSERT_TRUE(e.acceptBallot(b) == 3); 
}

// - Election::score
TEST(Election, score1)
{

    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c2");
    std::ostringstream w; 
    Election e(cn, w);
    std::vector<int> b;
    b.push_back(0);
    b.push_back(1); 
    e.acceptBallot(b);
    e.score();
    ASSERT_TRUE(w.str() == "c1"); 
}
TEST(Election, score2)
{

    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c2");
    std::ostringstream w; 
    Election e(cn, w);
    std::vector<int> v;
    v.push_back(1);
    v.push_back(0); 
    e.acceptBallot(v);
    e.score();
    ASSERT_TRUE(w.str() == "c2"); 
}
TEST(Election, score3)
{

    std::vector<std::string> cn;
    cn.push_back("c1");
    cn.push_back("c2");
    std::ostringstream w; 
    Election e(cn, w);

    std::vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(0);
    e.acceptBallot(v1);
    e.acceptBallot(v2);
    e.score();
    ASSERT_TRUE(w.str() == "c1\nc2"); 
}

// -- VoteMachine::parseElection
TEST(VoteMachine, parseElection1)
{
    std::istringstream r("2\nc1\nc2\n1 2");
    std::ostringstream w;
    VoteMachine::parseElection(r, w);
    ASSERT_TRUE(w.str() == "c1\n"); 
}


TEST(VoteMachine, parseElection2)
{
    std::istringstream r("2\nc1\nc2\n1 2\n2 1");
    std::ostringstream w;
    VoteMachine::parseElection(r, w);
    ASSERT_TRUE(w.str() == "c1\nc2\n"); 
}

TEST(VoteMachine, parseElection3)
{
    std::istringstream r("2\nc1\nc2\n1 2\n1 2");
    std::ostringstream w;
    VoteMachine::parseElection(r, w);
    ASSERT_TRUE(w.str() == "c1\n"); 
}

// -- VoteMachine::runMachine
TEST(VoteMachine, runMachine1)
{
    std::istringstream r("1\n\n2\nc1\nc2\n1 2");
    std::ostringstream w;
    VoteMachine::runMachine(r, w);
    ASSERT_TRUE(w.str() == "c1\n"); 
}


TEST(VoteMachine, runMachine2)
{
    std::istringstream r("1\n\n2\nc1\nc2\n1 2\n2 1");
    std::ostringstream w;
    VoteMachine::runMachine(r, w);
    ASSERT_TRUE(w.str() == "c1\nc2\n"); 
}

TEST(VoteMachine, runMachine3)
{
    std::istringstream r("1\n\n2\nc1\nc2\n1 2\n1 2");
    std::ostringstream w;
    VoteMachine::runMachine(r, w);
    ASSERT_TRUE(w.str() == "c1\n"); 
}
