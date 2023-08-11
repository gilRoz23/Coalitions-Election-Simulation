#pragma once
#include <vector>
using std::vector;
#include "SelectionPolicy.h"

class Party; // declare class party
class Agent;

class Coalition
{
private:
    int coalitionId;
    int numOfMandates;
    vector<int> myParties;
    

public:
    Coalition(int coalitionId, Party firstParty); // firstParty input added for initialize the first party in the coalition's parties vector, and add her mandates
    vector<int> createPartiesVector ( Party firstParty);
    int getCoalitionId() const;
    int getNumOfMandates() const;
    void addMandates(int mandates);
    void addParty(Party party);
    vector<int> getParties() const;
    
};