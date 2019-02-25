#include "player.h"

using namespace atsp::bet;

namespace
{
    static uint     numCities       = 0;
    static double   minBet          = 0.0;
    static double   initialBankroll = 0.0;
}

Player::Player():rating(_myRating)
{
}

double Player::ratePicks(const uint picks[], const uint pickCount)
{
    double total = 0.0;
    for(uint p = 0; p < pickCount; ++p)
    {
        _myRating[p] = _myProb[ picks[p] ];
        for(uint q = 0; q < pickCount; ++q)
        {
            if (p==q) continue;
            _myRating[p] *= ( 1.0 - _myProb[ picks[q] ] );
        }
        total += _myRating[p];
    }
    return total;
}

void Player::bet(const double houseProbs[buffsz], uint pickCount)
{
    for(uint pick = 0; pick < pickCount; ++pick)
    {
        // already spent all cash on previous picks
        if ( _bankroll == 0.0 )
        {
            _picked[pick] = false;
        }
        else
        {
            // Is my rating bigger than the house's
            if ( _myRating[pick] > houseProbs[pick] )
            {
                // kelly = (p*o - 1) / (o - 1)
                // where
                // p = the probability of success, according to player
                // o = howse odd = 1/houseProbs[pick]

                const double p = _myRating[pick];
                const double o = 1/houseProbs[pick];
                const double po = p*o;

                const double kelly = ( po - 1.0) /
                    (o - 1.0);

                const double bet = kelly * _bankroll;

                _bets[pick] = bet > minBet ? bet : minBet;

                if ( _bets[pick] >= _bankroll )
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
            else
            {
                _picked[pick] = false;
            }
        }
    }
}

void Player::reset()
{
    _bankroll = initialBankroll;

    for (uint i = 0; i < numCities; ++i)
    {
       _myProb[i] = base::fast_rand01();
    }
}

void Player::setGameParameters(uint numCitiesP, double minBetP, double initialBankrollP)
{
    numCities = numCitiesP;
    minBet = minBetP;
    initialBankroll = initialBankrollP;
}

void atsp::bet::service(Player p, uint winner, double houseProbs[])
{
    if ( p._picked[winner] )
    {
        p._bankroll += p._bets[winner] /= houseProbs[winner]; // checar!!
    }
    else if ( p._bankroll == 0.0 )
    {
        p.reset();
    }
}
