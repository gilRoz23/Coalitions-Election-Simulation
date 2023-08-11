#pragma once

#include <vector>
#include "SelectionPolicy.h"

class Simulation;
class Party;
class Graph;
class Coalition;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    // copy constructor
    Agent (const Agent& other);

    // destructor
    ~Agent();

    // assaignment operator
    Agent& operator= (const Agent &other);

    // move constructor
    Agent(Agent&& other);

    // move asaaignment operator
    Agent& operator= (Agent &&other);


    Agent cloneAgent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int myCoalitionId);
    int getPartyId() const;
    int getId() const;
    void initialNeighborsVector(Simulation &); //creates a neighbors vector
    void step(Simulation &);
    SelectionPolicy *getSelectionPolicy();
    void setMyCoalitionId(int coalitionId);
    int getCoalitionId(); // used for selecting the best party(among those who had'nt been offered by my coalition)

private:
// methods
    void copyNeighbors(vector<int> othersNeighbors);
// members
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int agentState; // 1 === active, 0 ==== idle
    vector <int> neighborsWeights; // initialised at initialNeighborsVector
    bool wasInit; // guranteed that the neighbors vector was initialized only once
    int myCoalitionId; // used when an agent offers a party on behalf of the coalition he represents
};
