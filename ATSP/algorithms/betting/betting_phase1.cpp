#include "betting_phase1.h"

using namespace atsp;
using namespace bet;


//BetAgorithm1::BetAgorithm1(bet::uint trSize,
//                           bet::uint trCount,
//                           bet::Player * const players,
//                           bet::uint playerCount)
//{

//}

BetAgorithm1::BetAgorithm1(uint trSize, uint pickCount, Player * const players, uint playerCount):
    _trsz(trSize),_pickCount(pickCount),_players(players),_playerCount(playerCount)
{
}
