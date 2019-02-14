#include "player.h"

using namespace atsp;

Player::Player(uint gameSize):_size(gameSize)
{
    _totalNoBetProd = 1.0;

    for(uint i = 0; i < _size; ++i )
    {
        _p1[i] = static_cast<double>( base::fast_rand()) / base::rand_max;
        _totalNoBetProd *= (1.0 - _p1[i]);
    }
}
