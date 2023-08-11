#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}



Party &Graph::getPartyNew(int partyId) //used at simulation.
{
    return mVertices[partyId];
}

// returns the Main matrix
vector<vector<int>> &Graph::getEdgesMatrix()
{
    return mEdges;
}

void Graph::changeParty (int partyId, Coalition coalition){
    Party &newParty = getPartyNew(partyId);
    if (newParty.getState() == Waiting){
        newParty.setState(CollectingOffers);
        newParty.addTime();
    }
    newParty.addOffer(coalition);
}