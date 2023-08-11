#include "SelectionPolicy.h"
#include "Graph.h"
#include "Coalition.h"
#include "Party.h"


int MandatesSelectionPolicy::bestParty(vector<int> &neighbors, Graph &graph, int agentCoalitionId){

    int bestPartyId = -1;
    int bestPartyMandats = -1;

    for (int i = 0; (unsigned)i < neighbors.size(); i++)
    {
        if (neighbors[i] != 0) // make sure to check only current relevant neighbors
        {
            Party currentParty = graph.getParty(i);
            if (currentParty.getState() == Joined) // current checked party is state joined (means its actually irrelevant)
            {
                neighbors[i] = 0; // sign it irrelevant
            }
            else { // neighbors != joined
            vector<Coalition> currentPartyOffers = currentParty.getOffers();
            bool foundSameCoalition = false;

            for (int j = 0; (unsigned)j < (currentPartyOffers.size() & !foundSameCoalition); j++) // loop over the coalitions that offered current checked party to join
            {
                if (currentPartyOffers[j].getCoalitionId() == agentCoalitionId) // if current checked party had already been offered by an agent from this coalition, sign her as irrelevant
                {
                    neighbors[i] = 0;
                    foundSameCoalition = true;
                }
            }
            if (!foundSameCoalition){
                    
                    if (bestPartyId == -1) // if current checked party is first relevant party that we reached as long far in the checking loop
                    {
                        bestPartyId = i;
                        bestPartyMandats = currentParty.getMandates();
                    }
                    else{ // current party is not first relevant we reached as long far
                        int currentPartyMandates = currentParty.getMandates();

                        if (currentPartyMandates > bestPartyMandats) // current party has more mandates than previous best party
                        {
                            bestPartyId = i; // change bestParty to current checked one
                            bestPartyMandats = currentPartyMandates;
                        }
                        
                    }
                    
                }
                
            
            }
            
            
        }
        
    }
    if ((bestPartyId != -1)){
        neighbors[bestPartyId] = 0;
    }
    return bestPartyId;            
}

SelectionPolicy* MandatesSelectionPolicy::clone() 
{
    SelectionPolicy *sp = new MandatesSelectionPolicy();
    return sp;
}


