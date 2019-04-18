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
    uint getConsecutiveWins(uint);

private:

    const uint        _trsz;
    const uint        _pickCount;
    Player * const    _players;
    const uint        _playerCount;

    // player stats. Usefull in phase 2
    uint _gamesAlive[512] = {0};
    uint _consecutiveWins[512] = {0};

    // game stats. To check how the game is evolving
    uint _played;
    uint _winners;
    uint _broken;

};



}
}
#endif // BETTING_ALGORITHM_H
