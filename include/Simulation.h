#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"

using std::string;
using std::vector;

class Party;
class SelectionPolicy;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    Graph &getGraphNew(); // added method to use graph //used at agent
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    vector<Agent> &getAgentsNew();
    int getNonJoinedParties()const;
    void decreaseByOneNonJoinedParties();
    Coalition &getCoalition (int coalitionId);

    vector<Coalition>& createCoalitionsVector (vector<Coalition> &coalitions);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> coalitions;
    int nonJoinedParties;
};
