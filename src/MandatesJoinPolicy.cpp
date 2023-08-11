#include "JoinPolicy.h"
#include "Coalition.h"


int MandatesJoinPolicy::bestToJoin(vector<Coalition> &offeredCoalitions){
int bestOffer = -1;
int bestOfferedMandates = 0;
int i = 0;
while((unsigned)i < offeredCoalitions.size()){
    if((bestOffer == -1) | (offeredCoalitions[i].getNumOfMandates() > bestOfferedMandates)){
        bestOffer = offeredCoalitions[i].getCoalitionId();
        bestOfferedMandates = offeredCoalitions[i].getNumOfMandates();
    
    }
    i++;
}
return bestOffer;
}

JoinPolicy* MandatesJoinPolicy::clone()
{
    JoinPolicy *jp = new MandatesJoinPolicy();
    return jp;
}
