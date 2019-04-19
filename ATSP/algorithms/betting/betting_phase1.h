#ifndef BETTING_ALGORITHM_H
#define BETTING_ALGORITHM_H

#include "atsp/algorithm.h"
#include "greedy/greedy_algorithm.h"
#include "player.h"
#ifdef __DEBUG__
#include <iostream>
#endif
#include <algorithm> // std::sort

namespace atsp {
namespace bet{

class BetAgorithm1 : public Algorithm
{
public:

    BetAgorithm1(uint trSize, uint pickCount,
                 Player * const players, uint playerCount);
    virtual uint run(Path&, const Data &);
    void setMaskCount(uint maskCount);

    uint getPlayed();
    uint getWinners();
    uint getBroken();
    uint getGamesAlive(uint);
    uint getMaxGamesAlive(uint);
    uint getConsecutiveWins(uint);
    uint getMaxConsecutiveWins(uint);

    enum Algoritm
    {
        Basic = 0
    };

    void setAlgorithm(Algoritm);

private:

    const uint        _trsz;
    const uint        _pickCount;
    Player * const    _players;
    const uint        _playerCount;

    // player stats. Usefull in phase 2
    uint _gamesAlive[512] = {0};
    uint _consecutiveWins[512] = {0};

    uint _gamesAliveMax[512] = {0};
    uint _consecutiveWinsMax[512] = {0};

    // game stats. To check how the game is evolving
    uint _played;
    uint _winners;
    uint _broken;

private:

    Algoritm algo;
    uint basicAlgorithm(Path&, const Data &);

};



}
}
#endif // BETTING_ALGORITHM_H
