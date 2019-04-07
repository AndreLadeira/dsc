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
    virtual uint run(Path&, const Data &) const;
    void setMaskCount(uint maskCount);

private:

    const uint        _trsz;
    const uint        _pickCount;
    Player * const    _players;
    const uint        _playerCount;

};



}
}
#endif // BETTING_ALGORITHM_H
