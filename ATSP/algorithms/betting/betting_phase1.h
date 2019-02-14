#ifndef BETTING_ALGORITHM_H
#define BETTING_ALGORITHM_H

#include "atsp/algorithm.h"
#include "player.h"
#include <vector>
#include <cmath>

namespace atsp {

class BettingPhase1 : public Algorithm
{
public:
    BettingPhase1(uint numPlayers, uint _size, uint msksz);
    ~BettingPhase1();

    virtual inline uint run(Path&, const Data &) const;
    void setMask(uint mask);

private:

    uint _numPlayers;
    uint _mask;
    uint _msksz;

    std::vector<Player> _player;

};

inline uint BettingPhase1::run(Path&, const Data &) const
{
    double pweights[512];

    double res = 0.0;

    for (uint i = 0; i < _numPlayers; ++i)
    {
        pweights[i] = _player.at(i).getWeight(_mask);
        res += pweights[i];
    }
    double omega = 1.0 / res;

    return static_cast<uint>( omega );

}

}

#endif // BETTING_ALGORITHM_H
