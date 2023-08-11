#pragma once
#include <vector>

class Coalition;
class Graph;
class Party;

using std::vector;

class SelectionPolicy {
    public:
        virtual int bestParty(vector<int> &neighbors, Graph &graph, int agentCoalitionId) = 0; // also graph is an input for getting the parties object and their state.
                                                                                         // also agentCoalitionId is an input for making sure not offer a party which had been offered by the agent's coalition
        virtual ~SelectionPolicy() = default;
        virtual SelectionPolicy* clone() = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
    public:

        virtual int bestParty(vector<int> &neighbors, Graph &graph, int agentCoalitionId);
        virtual SelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
        virtual int bestParty(vector<int> &neighbors, Graph &graph, int agentCoalitionId);
        virtual SelectionPolicy* clone();
};

