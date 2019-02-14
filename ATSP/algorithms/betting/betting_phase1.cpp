#include "betting_phase1.h"

using namespace atsp;

BettingPhase1::BettingPhase1(uint numPlayers, uint gsize, uint msksz):
    _numPlayers(numPlayers),_msksz(msksz)//, _player(nullptr)
{
    _player.reserve(_numPlayers);
    for (uint i = 0; i < _numPlayers; i++)
        _player.push_back( Player(gsize) );
}

BettingPhase1::~BettingPhase1()
{
}

void BettingPhase1::setMask(uint mask)
{
   _mask = mask;
}
