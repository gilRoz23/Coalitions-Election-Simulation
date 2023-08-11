#include "Coalition.h"
#include "Party.h"
#include "Agent.h"


Coalition::Coalition(int coalitionId, Party firstParty) : coalitionId(coalitionId),numOfMandates(firstParty.getMandates()),
    myParties (createPartiesVector( firstParty)){}


vector<int> Coalition::createPartiesVector ( Party firstParty){ //test
    vector <int> myParties;
    myParties.push_back(firstParty.getId());
    return myParties;
}



int Coalition::getCoalitionId() const{
    return coalitionId;
}
int Coalition::getNumOfMandates() const{
    return numOfMandates;
}

void Coalition::addParty(Party party){ // after a party agreed to join, add her id to parties vector, and her mandates
    myParties.push_back(party.getId());
    numOfMandates+= party.getMandates();

}
vector<int> Coalition::getParties() const{
    return myParties;
}
