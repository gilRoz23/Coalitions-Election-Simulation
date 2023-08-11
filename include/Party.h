#pragma once
#include <vector>
#include <string>
#include "Coalition.h"
#include "JoinPolicy.h"


using std::string;
class Agent;
class Simulation;


enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    //rule of 5

    // copy constructor
    Party (const Party& other);

    // destructor
    ~Party();

    // assaignment operator
    Party& operator= (const Party &other);

    // move constructor
    Party(Party&& other);

    // move asaaignment operator
    Party& operator= (Party&&other);


    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void addTime(); // added for increasing time.
    int getId() const; //added for adding the party to suitable Coalition after it chose one
    int getTime() const;
    vector<Coalition> getOffers();
    void addOffer(Coalition coalition);
    

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int time; //added for the collecting offers stage
    vector<Coalition> offeredCoalitions;
};
