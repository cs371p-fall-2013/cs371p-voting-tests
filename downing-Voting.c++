
#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>  // assert
#include <vector>
#include <algorithm>

using namespace std;

class Ballot{
public:
    int top;
    vector<int> votes;

    Ballot() {top = 0;}
    int getVote(){
        assert(top >= 0);
        if(top >= votes.size()){ return -1; } else { return votes[top]; } }
};

class Candidate{
public:
    int voteCount;
    string name;
    vector<Ballot> ballots;

    Candidate() {voteCount = 0; }
    void addVote(Ballot& ballot);
};

class BallotBox{
public:
    int numberOfBallots, numOfValidCandidates;
    vector<Candidate> candidates;

    BallotBox() {numberOfBallots = 0; numOfValidCandidates = 0;}
    void addCandidate(string& name);
    void castBallot(string ballot);
    vector<int> ballotStringtoVector(string ballot, int size);
    int isMajority(int majority);
    vector<Candidate*> getLastPlace();
    void sortLosers(vector<Candidate*>& losers);
};

vector<string> voting_findWinner(BallotBox&);

void voting_read (istream&, BallotBox&);

void voting_print (ostream&, vector<string>&, bool);

void voting_holdElection(istream&, ostream&, bool);

void Candidate::addVote(Ballot& ballot){
    voteCount++;

    if(ballot.top < ballot.votes.size()){
        ballot.top += 1;
        ballots.push_back(ballot);
    }
}

///////////////////////////////////////////////////////////////


void BallotBox::addCandidate(string& name){
    Candidate candidate;
    candidate.name = name;
    candidates.push_back(candidate);
    numOfValidCandidates++;
    assert(candidates.size() <= 20);
}

void BallotBox::castBallot(string ballotString){
    numberOfBallots++;
    assert(numberOfBallots <= 1000);

    Ballot ballot;
    ballot.votes = ballotStringtoVector(ballotString, candidates.size());
    int firstChoice = ballot.getVote();
    assert(firstChoice-1 >= 0);
    candidates[firstChoice-1].addVote(ballot);
}

vector<int> BallotBox::ballotStringtoVector(string ballot, int size){
    vector<int> ballotVector;

    string temp = "";
    string test = "";
    for(int i =0; i < ballot.length(); i+=2){

    temp = ballot.substr(i+1, 1);
    if(temp == " "){
        test = ballot.substr(i, 1);
    }
    else{
        test = ballot.substr(i, 2);
        i++;
    }
    ballotVector.push_back(atoi(test.c_str()));
    }

    return ballotVector;
}

int BallotBox::isMajority(int majority){
    int count = 0;
    for(vector<Candidate>::iterator it = candidates.begin(); it != candidates.end(); ++it){
        if((*it).voteCount >= majority){
            return count;
        }
        count++;
    }
    return -1;
}

vector<Candidate*> BallotBox::getLastPlace(){
    vector<Candidate*> losersReturn;
    vector<int> losersIndex;
    int smallestVote = numberOfBallots + 1;

    Candidate* currentCandidate;

    int count = 0;
    for(vector<Candidate>::iterator it = candidates.begin(); it != candidates.end(); ++it){
        currentCandidate = &(*it);
        //want to ignore all invalid candidates
        if( currentCandidate->voteCount != -1){
            if(currentCandidate->voteCount < smallestVote){
                losersIndex.clear();

                smallestVote = currentCandidate->voteCount;

                losersIndex.push_back(count);

            }
            else if(currentCandidate->voteCount == smallestVote){
                losersIndex.push_back(count);
            }
        }
        count++;
    }

    //get all the losers and set their votes to -1 making them invalid
    for(unsigned int i = 0; i< losersIndex.size(); i++){
        assert(losersIndex[i] >= 0);
        currentCandidate = &candidates[losersIndex[i]];
        //candidates[losersIndex[i]]->voteCount = -1;
    currentCandidate->voteCount = -1;

        losersReturn.push_back(currentCandidate);
    }
    return losersReturn;
}

void BallotBox::sortLosers(vector<Candidate*>& losers){
    Candidate* loser;
    Candidate nextCandidate;
    vector<Ballot> ballots;
    Ballot ballot;
    int nextChoice;
    for(vector<Candidate*>::iterator it = losers.begin(); it != losers.end(); ++it){
        loser = *it;
        ballots = loser->ballots;

        for(vector<Ballot>::iterator it = ballots.begin(); it != ballots.end(); ++it){
        // for(unsigned int j = 0; j < ballots.size(); j++){
            ballot = *it;

            do{
                nextChoice = ballot.getVote();
                nextCandidate = candidates[nextChoice -1];

                if(nextCandidate.voteCount != -1){
                    candidates[nextChoice - 1].addVote(ballot);

                }
                else{
                    assert(nextCandidate.voteCount == -1);
                    ballot.top += 1; //should be able to delete this
                }
            }while(nextCandidate.voteCount == -1 && ballot.top < ballot.votes.size());
        }
        numOfValidCandidates--;
    }

}

///////////////////////////////////////////////////////////////////////

vector<string> voting_findWinner(BallotBox& box){
    bool winnerFound = false;
    vector<string> winners;
    int majority = (box.numberOfBallots /2) + 1;
    assert((box.numberOfBallots - majority) < majority);

    while(!winnerFound){
        int isMajority = box.isMajority(majority);
        if(isMajority >= 0){
            winners.push_back(box.candidates[isMajority].name);

            winnerFound = true;
        }
        else{
            assert(isMajority == -1);
            vector<Candidate*> losers = box.getLastPlace();
            if(losers.size() == box.numOfValidCandidates){
                for(vector<Candidate*>::iterator it = losers.begin(); it != losers.end(); ++it){
                    winners.push_back((*it)->name);
                }
                winnerFound = true;
            }
            else{
                box.sortLosers(losers);
            }
        }


    }
    return winners;

}


//TODO on suceed needs to return the ballot object
//TODO on fail needs to return null
void voting_read (istream& reader, BallotBox& box) {
    int numberOfCandidates;
    reader >> numberOfCandidates;
    assert(reader);
    string candidateName;
    getline (reader, candidateName); // this is to skip to the next line sincde reader >> did not
    for(int i =0; i < numberOfCandidates; i++){
        getline(reader, candidateName);
        box.addCandidate(candidateName);
        assert(reader);
    }
    string ballot = "";
    while(true){
        getline(reader, ballot);
        if(ballot.compare("") != 0){
            box.castBallot(ballot);
        }
        else if(ballot.compare("") == 0){
            break;
        }
    }
    //cout << "------voting_read" << endl;
}

// -------------
// voting_print
// -------------

void voting_print (ostream& writer, vector<string>& winnerNames, bool lastOne) {
    for(vector<string>::iterator it = winnerNames.begin(); it != winnerNames.end(); ++it){
        writer << *it;
        //if(it == !lastOne)
        writer << endl;
    }
    if(!lastOne) writer << endl;
}

void voting_holdElection(istream& reader, ostream& writer, bool lastOne){
    BallotBox box;
    vector<string> winners;
    //cout << "------- about to read" << endl;
    voting_read(reader, box);
    //cout << "------- done with read" << endl;
    winners = voting_findWinner(box);
    voting_print(writer, winners, lastOne);
}

int main () {
    ////cout << "------main" << endl;
    using namespace std;
    int numberOfElections;
    string blankLine;

    ////cout << "------- start" << endl;

    cin >> numberOfElections;
    getline(cin, blankLine);
    getline(cin, blankLine);

    for(int i=0; i< numberOfElections; i++){
	////cout << "------- election" << endl;
        voting_holdElection(cin, cout, !(i < numberOfElections -1));
    }

    return 0;
}
