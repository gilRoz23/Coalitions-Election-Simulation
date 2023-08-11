#include "Agent.h"
#include "Simulation.h"
#include "Party.h"
#include "Graph.h"
#include "Coalition.h"

#include <iostream>
using namespace std;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), agentState(1), neighborsWeights(), wasInit(false), myCoalitionId(-1){}

//rule of 5

// copy ctr
Agent::Agent (const Agent& other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy->clone()),
    agentState(other.agentState), neighborsWeights(), wasInit(other.wasInit), myCoalitionId(other.myCoalitionId){
    copyNeighbors(other.neighborsWeights);
    }
    
//destructor
Agent::~Agent(){
    if (mSelectionPolicy) {
        delete mSelectionPolicy;
        mSelectionPolicy = nullptr; }
}
//copy assignment operator
Agent& Agent::operator= (const Agent &other){
    if (this != &other)
    {
        mAgentId=other.mAgentId;
        mPartyId=other.mPartyId;
        agentState=other.agentState;
        wasInit=other.wasInit;
        myCoalitionId=other.myCoalitionId;

        copyNeighbors(other.neighborsWeights);
        this->mSelectionPolicy = other.mSelectionPolicy->clone();
    }
        return *this;   
    }

//move constructor
Agent::Agent(Agent&& other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy),
    agentState(other.agentState), neighborsWeights(0), wasInit(other.wasInit), myCoalitionId(other.myCoalitionId){
    
    copyNeighbors(other.neighborsWeights);
    other.mSelectionPolicy = nullptr;

}
//move assignment operator
Agent& Agent::operator= (Agent &&other){
    mAgentId=other.mAgentId;
    mPartyId=other.mPartyId;
    agentState=other.agentState;
    wasInit=other.wasInit;
    myCoalitionId=other.myCoalitionId;
    copyNeighbors(other.neighborsWeights);    
    if (mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
    mSelectionPolicy = other.mSelectionPolicy;

    other.mSelectionPolicy = nullptr;
    return *this;   
}

//end of rule of 5

// private method used for copy neighbors from other agent
void Agent::copyNeighbors(vector<int> othersNeighbors){
    __SIZE_TYPE__ i;
        for (i = 0; i < othersNeighbors.size(); i++) // copy the neighbors vector
        {
            neighborsWeights.push_back(othersNeighbors[i]);
        }
}

// method creating a new agent with coalitionId member as input only by an other agent, like reproducing. should be a constructor but it means we'll need more rule of 5
Agent Agent::cloneAgent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int coalitionId)
    {

    
    Agent newAgent = Agent(agentId, partyId, selectionPolicy->clone());
    newAgent.myCoalitionId = coalitionId;
    return newAgent;
    }

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalitionId(){ // used for selecting the best party(among those who had'nt been offered by my coalition)
    return myCoalitionId;
}

void Agent::setMyCoalitionId(int coalitionId){ // used only updating the coalitionId member in the input agents in simulation, because they already initialized
    myCoalitionId = coalitionId;
}

SelectionPolicy *Agent::getSelectionPolicy(){  // used for transfer the selectionPolicy to the initialized coalition in simulation
    return mSelectionPolicy;
    
}

void Agent::initialNeighborsVector(Simulation &sim)
{
    // run over all the neighbors of agent's party. add to the vector
    Graph &graph = sim.getGraphNew();
    
    neighborsWeights = graph.getEdgesMatrix()[mPartyId]; // *** i need to copy this vector by value to erase some parties later
    // is it copied or refrenced?? (the matrix is refrenced)
}

void Agent::step(Simulation &sim)
{   


    // if agent is idle
    if (agentState == 0){ 
        return;
    }
    // initialize only once
    if(!wasInit) 
    {
        initialNeighborsVector(sim);
        wasInit = true;
    }



    int bestPartyId = mSelectionPolicy->bestParty(neighborsWeights, sim.getGraphNew(), getCoalitionId()); //select the best party
    
    // if nothing returned - make idle
    if (bestPartyId == -1){
        agentState = 0;
    }
    else {

        sim.getGraphNew().changeParty(bestPartyId, sim.getCoalition(myCoalitionId));
    }
   

    
}
