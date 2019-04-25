#include "house.h"

using namespace atsp::bet;

House::House(uint trCount, uint pickPolicy)
    :_trCount(trCount), _policy(pickPolicy)
{
}

namespace
{
uint _2pow(uint power)
{
    if (power == 0)
        return 1;
    else {
        uint res = 2;
        for(uint i = 1; i < power; i++)
            res *=2;
        return res;
    }
}



}

uint House::getNumPicks()
{
    if ( _policy & Multiple )
    {
        if ( _policy & WithNone)
            return _2pow(_trCount);
        else
            return _2pow(_trCount) - 1;
    }

    uint res = _trCount;
    if ( _policy & WithNone )
        res += 1;

    return res;
}

void House::getPicks(uint *P, uint *notP)
{
    uint numPicks = getNumPicks();
    uint start = _policy & WithNone ? 0 : 1;
    uint shift = !start;
    uint fullrange = _2pow(_trCount) - 1;

    for(uint i = 0; i < numPicks; i++ )
    {
        // P
        uint v = i + start;
        if ( _policy & Multiple )
            P[i] = v;
        else
            if (i == 0)
                P[i] = v;
            else
                P[i] = 1 << (i-shift);

        // notP
        if (_policy & Weighed)
        {
            notP[i] = ~P[i] & fullrange;
        }
        else
        {
            if (_policy & WithNone && i == 0)
                notP[i] =  ~0u & fullrange;
            else
               notP[i] = 0;
        }
    }
}

void House::setPolicy(uint pickPolicy)
{
    _policy = pickPolicy;
}

uint House::getWinner(std::vector<GameResults> & results) const
{
    // ordena
    std::sort(results.begin(),results.end());
    // avalia
    if (_policy & Multiple )
    {
        uint res = 0x0;

        for (auto & r : results) {
            if (r.improved)
            {
                //uint shift = _policy & WithNone ? 1 : 0;
                uint val = 0x1 << r.index;
                res |= val;
            }
        }
        return res;
    }
    else
    {
        if ( _policy & WithNone)
        {
            if ( results.at(0).improved )
                //return 0x1 << (results.at(0).index);
                return results.at(0).index + 1;
            else
                return 0;
        }
        else {
            return results.at(0).index;
        }
    }


}
