#ifndef BETTING_ALGORITHM_H
#define BETTING_ALGORITHM_H

#include "atsp/algorithm.h"
#include "greedy/greedy_algorithm.h"
#include "player.h"
#include <algorithm> // std::sort

namespace atsp {
namespace bet{

class BetAgorithm1 : public Algorithm
{
public:

    BetAgorithm1(uint trSize, uint pickCount,
                 Player * const players, uint playerCount);
    virtual inline uint run(Path&, const Data &) const;
    void setMaskCount(uint maskCount);

private:

    const uint        _trsz;
    const uint        _pickCount;
    Player * const    _players;
    const uint        _playerCount;

};

inline uint BetAgorithm1::run(Path &        path,
                              const Data &  data) const
{
    // Gets new random points of path transformation
    // huge buffer, avoid allocation....
    uint picks[512] = {0};
    const uint pathSz = path.getSize();

    picks[0] = static_cast<uint>(base::fast_rand()) % pathSz;

    {
        for(uint i = 1; i < _pickCount; ++i)
        {
            back:
            uint attempt = static_cast<uint>(base::fast_rand()) % pathSz;
            for(uint j = 0; j < i; ++j)
            {
                if ( attempt == picks[j]) goto back;
            }
            picks[i] = attempt;
        }
    }

    // get the set of players to find out how they rank
    // each available pick (trPoint)

    // holds the sum of rates of all players on all picks
    // used later to calculate the odds
    double R = 0.0;

    for (uint i = 0; i < _playerCount; ++i)
        R += _players[i].ratePicks(picks,_pickCount);

    // calculate the house probabilities, based on player's collective knowledge
    double houseProbs[512] = {0.0};

    for(uint i = 0; i < _pickCount; i++)
    {
        for(uint j = 0; j < _playerCount; ++j)
            houseProbs[i] += _players[j].rating[i];
        houseProbs[i] /= R;
    }

    // sorts the odds in ascending order, so the players
    // evaluate the best options first
    std::sort(houseProbs, houseProbs + _pickCount, std::greater<double>());

    // Players then bet or not, according to the given odds
    for(uint j = 0; j < _playerCount; ++j)
        _players[j].bet(houseProbs,_pickCount);

    // gets the winner transformation
    atsp::GreedyAlgorithm greedyAlgorithm(_trsz);

    uint min = std::numeric_limits<uint>::max();
    uint r = 0;
    atsp::Path current = path;
    atsp::Path best = path;
    uint winner = 0;

    for(uint p = 0; p < _pickCount; ++p)
    {
        greedyAlgorithm.setMask( picks[p] );

        r = greedyAlgorithm.run(current, data);

        if ( r < min )
        {
            min = r;
            winner = p;
            best = current;
        }
    }

    // pays the prizes, replaces the broken
    for(uint j = 0; j < _playerCount; ++j)
        service(_players[j], winner, houseProbs);

    // update the best path
    if ( min < atsp::getLength(data, path) )
    {
        path = best;
    }

    return min;
}

}
}
#endif // BETTING_ALGORITHM_H
