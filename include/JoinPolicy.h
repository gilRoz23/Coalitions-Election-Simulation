#pragma once
#include <vector>
using std::vector;
class Coalition;

class JoinPolicy 
{
    public:
        virtual int bestToJoin(vector<Coalition> &offeredCoalitions) = 0;
        virtual ~JoinPolicy() = default;
        virtual JoinPolicy* clone() = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual int bestToJoin(vector<Coalition> &offeredCoalitions);
        virtual JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual int bestToJoin(vector<Coalition> &offeredCoalitions);
        virtual JoinPolicy* clone();
};