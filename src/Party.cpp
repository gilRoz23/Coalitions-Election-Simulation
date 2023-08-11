#include "Party.h"
#include "Agent.h"
#include "Simulation.h"
#include <iostream>
using namespace std;


Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), time(-1), offeredCoalitions(){}
//rule of 5
//copy constructor

Party::Party (const Party &other): mId(other.mId), mName(other.mName), mMandates(other.mMandates),
    mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), time(other.time), 
    offeredCoalitions(other.offeredCoalitions){}

//destructor
Party::~Party(){
    
    if (mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy = nullptr;

}
//copy assignment operator
Party& Party::operator=(const Party &other){
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    *(mJoinPolicy) = *(other.mJoinPolicy);
    mState = other.mState;
    time = other.time;
    offeredCoalitions = other.offeredCoalitions;

    return *this;

}
//move constructor
Party::Party (Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates),
    mJoinPolicy(other.mJoinPolicy), mState(other.mState), time(other.time), 
    offeredCoalitions(other.offeredCoalitions){
    other.mJoinPolicy = nullptr;
    }
//move assignment operator
Party& Party::operator=(Party &&other){

    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;

    if (mJoinPolicy) delete mJoinPolicy;
    *(mJoinPolicy) = *(other.mJoinPolicy);
    other.mJoinPolicy = nullptr;

    mState = other.mState;
    time = other.time;
    offeredCoalitions = other.offeredCoalitions;
    return *this;

}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

//rule of 5

//added methods
void Party::addTime()
{
    time++;
}

int Party::getId() const{
    return mId;
}

int Party::getTime() const{
    return time;
}

vector<Coalition> Party::getOffers(){ //used for send the offers to mJoinPolicy so it will join the best one
    return offeredCoalitions;
}

void Party::addOffer(Coalition coalition){ // add an offer from a coalition to the offers vector
    offeredCoalitions.push_back(coalition);


}


void Party::step(Simulation &s)
{
    if (Party::getState() == CollectingOffers )
    {
        Party::addTime();
        if (getTime()==3)
        {
            int bestCoalitionId = (*mJoinPolicy).bestToJoin(offeredCoalitions); //here I sent offeredCoalitions member as input, because I had to send an lvalue, so it can be binded to a reference
            s.getCoalition(bestCoalitionId).addParty(*this); //add this party to the chosen Coalition

            SelectionPolicy *newAgentsPolicy = s.getAgentsNew()[bestCoalitionId].getSelectionPolicy();
            s.getAgentsNew().push_back(s.getAgentsNew()[bestCoalitionId].cloneAgent(s.getAgents().size(), mId, newAgentsPolicy , bestCoalitionId)); //clone an agent and add him to the simulation's agents vector
            setState(Joined);
            s.decreaseByOneNonJoinedParties(); // update non-Joined_parties
        }
        
    }
    
}
