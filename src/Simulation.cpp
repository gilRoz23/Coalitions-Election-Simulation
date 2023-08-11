#include "Simulation.h"
#include "Party.h"
#include "SelectionPolicy.h"

#include <iostream>
using namespace std;

// asddf
Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitions(), nonJoinedParties (mGraph.getNumVertices() - agents.size())
{
    for (int i = 0; (unsigned)i < mAgents.size(); i++){ 
        Coalition coalition = Coalition(i, mGraph.getParty(mAgents[i].getPartyId())); // intialize coalitions vector, each contains selectionPolicy, current party and current mandates
        mAgents[i].setMyCoalitionId(i); //initialize coalitionId member for each agent input in simulation
        coalitions.push_back(coalition);

    }
    
}


int Simulation::getNonJoinedParties()const{
    return nonJoinedParties;
}

void Simulation::decreaseByOneNonJoinedParties(){ //updating nonJoinedParties after a party joins to a coalition
    nonJoinedParties-=1;
}

void Simulation::step()
{
   
    // loop over all parties, call party.step
    for (int i = 0; i < mGraph.getNumVertices(); i++){
        mGraph.getPartyNew(i).step(*this); 
    }

    //loop over all agents, call agent.step
    for (int i = 0; (unsigned)i< this->getAgents().size(); i++){
 
        mAgents[i].step(*this); 
    }


}

bool Simulation::shouldTerminate() const
{
    if (nonJoinedParties == 0){
        return true;
    }
    for (int i = 0; (unsigned)i < coalitions.size(); i++)
    {
        if (coalitions[i].getNumOfMandates() > 60)
        {
            return true;
        }
        
    }    
    return false;

    
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraphNew()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getAgentsNew(){ // used for cloning an Agent and add him to the Agents vector
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}





const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalitions;

    for (int i = 0; (unsigned)i < coalitions.size(); i++)
    {
        partiesByCoalitions.push_back(coalitions[i].getParties());
    }
    return partiesByCoalitions;
}

Coalition &Simulation::getCoalition (int coalitionId)
{
    return coalitions[coalitionId];
}
