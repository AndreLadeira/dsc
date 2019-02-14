#ifndef PLAYER_H
#define PLAYER_H

#include "base/random.h"

namespace atsp
{

typedef unsigned int uint;

class Player
{
private:

    explicit Player(uint gameSize);

    inline double getWeight(uint mask) const;
    static void setRandFcn(base::rand_fcn_t, uint rand_max);

private:

    // how much a player like a number beside other number

    double _ps[512][512];

private:

    uint _size;

    friend class BettingPhase1;
    friend class BettingPhase2;
};

inline double Player::getWeight(uint mask) const
{
    return _p1[mask] * _totalNoBetProd / (1.0 - _p1[mask]);
}

}
#endif // PLAYER_H
