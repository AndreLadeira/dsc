#ifndef BETTING_ALGORITHM_H
#define BETTING_ALGORITHM_H

#include "atsp/algorithm.h"
#include "player.h"
#include <algorithm> // std::sort

namespace atsp {
namespace bet{

class BetAlgorithm1 : public Algorithm
{
public:

    BetAlgorithm1(uint trSize, uint trCount, uint pickPolicy,
                 Player * const players, uint playerCount);
    ~BetAlgorithm1();

    virtual uint run( atsp::Path&, const atsp::Data &);
    void setMaskCount(uint maskCount);

private:

    const uint          _trsz;
    const uint          _trCount;
    const uint          _pickPolicy;
    Player * const      _players;
    const uint          _playerCount;

private:

};



}
}
#endif // BETTING_ALGORITHM_H
