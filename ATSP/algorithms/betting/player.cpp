#include "player.h"

using namespace atsp::bet;

Player::Player()
{
}

double Player::ratePicks(const uint picks[], uint count)
{
    double total = 0.0;
    for(uint p = 0; p < count; ++p)
    {
        _myOdds[p] = _knowledge[ picks[p] ];
        for(uint q = 0; q < count; ++q)
        {
            if (p==q) continue;
            _myOdds[p] *= ( 1.0 - _knowledge[ picks[q] ] );
        }
        total += _myOdds[p];
    }
    return total;
}

void Player::gamble(const double odds[], uint count)
{
    for(uint pick = 0; pick < count; ++pick)
    {
        if ( odds[pick] > _myOdds[pick] )
        {
            const double kelly =
                    ( 1.0 / _myOdds[pick] * odds[pick] - 1.0) /
                    (odds[pick] - 1.0) * _bankroll;

            _bets[pick] = kelly > minbet ? kelly : minbet;

            if ( _bets[pick] >= _bankroll ) // cacife zero
            {
                _bets[pick] = _bankroll;
                _bankroll = 0.0;
            }
            else
            {
                _bankroll -= _bets[pick];
            }
            _picked[pick] = true;
        }
        else {
            _picked[pick] = false;
        }

    }
}

void Player::reset(uint numCitiesParam, double startCash)
{
    static uint numCities;

    if ( numCitiesParam )
    {
        numCities = numCitiesParam;
    }
    if ( startCash > 0.0 )
    {
        _bankroll = startCash;
    }

    for (uint i = 0; i < numCities; ++i)
    {
       _knowledge[i] = base::fast_rand01();
    }
}

void atsp::bet::service(Player p, uint winner, double odds[])
{
    if ( p._picked[winner] )
    {
        p._bankroll += p._bets[winner] /= odds[winner];
    }
    else if ( p._bankroll == 0.0 )
    {
        p.reset();
    }
}
