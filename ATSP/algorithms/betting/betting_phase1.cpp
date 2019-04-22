#include "betting_phase1.h"
#include "greedy/greedy_algorithm.h"

using namespace atsp::bet;

BetAlgorithm1::BetAlgorithm1(   uint                    trSize,
                                uint                    pickCount,
                                Player * const   players,
                                uint                    playerCount):
    _trsz(trSize),_pickCount(pickCount),_playerCount(playerCount),_players(players)
{
}

BetAlgorithm1::~BetAlgorithm1()
{
}

uint BetAlgorithm1::run(Path &        path,
                       const Data &  data)
{
    // Gets new random points of path transformation
    // huge buffer, avoid allocation....
    uint picks[512] = {0};
    const uint pathSz = path.getSize();
    const uint maxPick = pathSz - _trsz;

    picks[0] = static_cast<uint>(base::fast_rand()) % maxPick;

    {
        for(uint i = 1; i < _pickCount; ++i)
        {
            back:
            uint attempt = static_cast<uint>(base::fast_rand()) % maxPick;
            for(uint j = 0; j < i; ++j)
            {
                if ( attempt == picks[j]) goto back;
            }
            picks[i] = attempt;
        }
    }


    // make the players rank each available pick (trPoint)

    // holds the sum of rates of all players on all picks
    // used later to calculate the odds
    double R = 0.0;

    for (uint i = 0; i < _playerCount; ++i)
        R += _players[i].ratePicks(picks,_pickCount);

    // calculate the house probabilities,
    // based on player's collective knowledge
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

    // now, lets run the game

    // setup a greedy algorithm
    atsp::GreedyAlgorithm greedyAlgorithm(_trsz);

    uint min = getLength(data,path); //std::numeric_limits<uint>::max();
    atsp::Path current = path;
    atsp::Path best = path;

    // setting the winner equal to pickCount is equivalent
    // to set it to "no option resulted in improvement"

    uint winner = _pickCount;

    // run a gredy transformation for each pick

    for(uint p = 0; p < _pickCount; ++p)
    {
        greedyAlgorithm.setMask( picks[p] );

        uint newPathLen = greedyAlgorithm.run(current, data);

        if ( newPathLen < min )
        {
            min = newPathLen;
            winner = p;
            best = current;
        }
    }

    PlayerStats::resetRoundStats();

    // pays the prizes, replaces the broken
    for(uint j = 0; j < _playerCount; ++j)
       _players[j].checkOut(winner,houseProbs[winner]);

    // update the best path
    if ( min < atsp::getLength(data, path) )
    {
        path = best;
    }

    return min;

}
