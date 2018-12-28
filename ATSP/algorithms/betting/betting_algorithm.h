#ifndef BETTING_ALGORITHM_H
#define BETTING_ALGORITHM_H

#include "atsp/algorithm.h"

namespace atsp {

class BettingAlgorithm : public Algorithm
{
public:
    BettingAlgorithm();

    virtual inline uint run(Path&, const Data &) const;


};

inline uint BettingAlgorithm::run(Path&, const Data &) const
{
    return 0;
}

}

#endif // BETTING_ALGORITHM_H
