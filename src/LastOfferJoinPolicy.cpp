#include "JoinPolicy.h"
#include "Coalition.h"

int LastOfferJoinPolicy::bestToJoin(vector<Coalition> &offeredCoalitions){
    int bestOffer = -1;
    if (offeredCoalitions.size()>0)
    {
        return offeredCoalitions[offeredCoalitions.size()-1].getCoalitionId();
    }
    return bestOffer;
}

JoinPolicy* LastOfferJoinPolicy::clone()
{
    JoinPolicy *jp = new LastOfferJoinPolicy();
    return jp;
}