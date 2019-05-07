#include "betting_phase1.h"
#include "greedy/greedy_algorithm.h"
#include "house.h"

using namespace atsp::bet;

BetAlgorithm1::BetAlgorithm1(   uint                    trSize,
                                uint                    trCount,
                                uint                    pickPolicy,
                                Player * const          players,
                                uint                    playerCount):
    _trsz(trSize),_trCount(trCount),_pickPolicy(pickPolicy),
    _players(players),_playerCount(playerCount)
{
}

BetAlgorithm1::~BetAlgorithm1()
{
}

uint BetAlgorithm1::run(Path &       currentPath,
                       const Data &  data)
{
    // Gets new random points of path transformation
    // huge buffer, avoid allocation....
    uint trPoints[512] = {0};
    const uint currPathSz = currentPath.getSize();
    const uint maxPick = currPathSz - _trsz + 1;

    trPoints[0] = static_cast<uint>(base::fast_rand()) % maxPick;

    {
        for(uint i = 1; i < _trCount; ++i)
        {
            back:
            uint attempt = static_cast<uint>(base::fast_rand()) % maxPick;
            for(uint j = 0; j < i; ++j)
            {
                if ( attempt == trPoints[j]) goto back;
            }
            trPoints[i] = attempt;
        }
    }
    //
    //House house(_trCount, House::Policy::Full );
    // House house(_trCount, House::Policy::Single | House::Policy::WithNone );
    House house(_trCount, _pickPolicy );
    uint p[128], notp[128];
    uint numPicks = house.getNumPicks();
    house.getPicks(p,notp);

    // make the players rank each available pick (trPoint)

    // holds the sum of rates of all players on all picks
    // used later to calculate the odds
    double R = 0.0;

    for (uint i = 0; i < _playerCount; ++i)
        R += _players[i].ratePicks(p, notp,numPicks,trPoints,_trCount);

    // calculate the house probabilities,
    // based on player's collective knowledge
    double houseProbs[512] = {0.0};

    for(uint i = 0; i < numPicks; i++)
    {
        for(uint j = 0; j < _playerCount; ++j)
            houseProbs[i] += _players[j].rating[i];
        houseProbs[i] /= R;
    }

    // sorts the odds in ascending order, so the players
    // evaluate the best options first
    std::sort(houseProbs, houseProbs + numPicks);

    // Players then bet or not, according to the given odds
    for(uint j = 0; j < _playerCount; ++j)
        _players[j].bet(houseProbs,numPicks);

    // now, lets run the game

    // setup a greedy algorithm
    atsp::GreedyAlgorithm greedyAlgorithm(_trsz);

    uint currPathCost   = getLength(data,currentPath); //std::numeric_limits<uint>::max();
    Path newPath        = currentPath;
    Path bestPath       = currentPath;
    uint newBestCost    = currPathCost;


    House::resultsVector_t results(_trCount);

    for(uint p = 0; p < _trCount; ++p)
    {
        greedyAlgorithm.setMask( trPoints[p] );

        results.at(p).index = p;
        results.at(p).result =
            greedyAlgorithm.run(newPath, data);
        if ( results.at(p).result < currPathCost ) // improves?
        {
            results.at(p).improved = true;

            if ( results.at(p).result < newBestCost )
            {
                newBestCost = results.at(p).result;
                bestPath = newPath;
            }

        }


    }


    uint winner = house.getWinner(results);

    PlayerStats::resetRoundStats();

    // pays the prizes, replaces the broken
    for(uint j = 0; j < _playerCount; ++j)
       _players[j].checkOut(winner,houseProbs[winner]);

    // update the best path
    // getWinner orders the results vector
    // so if the resut at the first positon improved
    // update the best solution

    if ( results.at(0).improved )
    {
        currentPath = bestPath;

#ifdef __DEBUG__
        assert(getLength(data,currentPath) == newBestCost);
#endif

    }

    return results.at(0).result;

}
