#ifndef HOUSE_H
#define HOUSE_H
#include <vector>

typedef unsigned int uint;

namespace atsp{
namespace bet
{

struct GameResults
{
    GameResults():index(0),result(0),improved(false){}    uint index;
    uint result;
    bool improved;

    bool operator<(const GameResults & rhs) const
    {return this->result < rhs.result;}

    bool operator>(const GameResults & rhs) const
    { return !(*this<rhs);}
};

class House
{
public:
    enum Policy
    {
       Single    = 0,
       WithNone  = 1,
       Multiple  = 2,
       Weighed   = 4,
       Full  = WithNone | Multiple | Weighed
    };

    House(uint trCount, uint pickPolicy = Single);
    uint getNumPicks();
    void getPicks(uint * P, uint * notP);
    void setPolicy(uint pickPolicy);

    typedef std::vector<GameResults> resultsVector_t;

    uint getWinner( resultsVector_t & results) const;


private:

    uint _trCount;
    uint _policy;
};
}
}
#endif // HOUSE_H
