#include "player.h"

using namespace atsp::bet;

namespace
{
    static uint     numCities       = 0;
    static double   minBet          = 0.0;
    static double   initialBankroll = 0.0;
}

Player::Player():rating(_myRating),_played(false)
{
}

double Player::ratePicks(const uint picks[], const uint pickCount)
{
    double total = 0.0;

    // _myRating[pickCount] will hold the probability
    // of no choice result in inprovement

    _myRating[pickCount] = 1.0;

    for(uint p = 0; p < pickCount; ++p)
    {     
        _myRating[pickCount] *= ( 1.0 - _myProb[ picks[p] ] );
        _myRating[p] = _myProb[ picks[p] ];
        total += _myProb[ picks[p] ];
    }
    total += _myRating[pickCount];

    for(uint p = 0; p < pickCount + 1; ++p)
    {
      _myRating[p] /= total;
    }
    return 1.0;
}

void Player::bet(const double houseProbs[buffsz], uint pickCount)
{
    _played = false;

    for(uint pick = 0; pick < pickCount; ++pick)
    {
        // already spent all cash on previous picks
        if ( _bankroll == 0.0 )
        {
            _picked[pick] = false;
            _bets[pick] = 0.0;
        }
        else
        {
            // Is my rating bigger than the house's
            if ( _myRating[pick] > houseProbs[pick] )
            {
                _played = true;
                // kelly = (p*o - 1) / (o - 1)
                // where
                // p = the probability of success, according to player
                // o = howse odd = 1/houseProbs[pick]

                const double p = _myRating[pick];
                const double o = 1/houseProbs[pick];
                const double po = p*o;

                const double kelly = ( po - 1.0) /
                    (o - 1.0);

                double bet = kelly * _bankroll;

                bet = bet > minBet ? bet : minBet;
                bet = bet > _bankroll ? _bankroll : bet;

                _bankroll -= bet;
                _picked[pick] = true;
                _bets[pick] = bet;
            }
            else
            {
                _picked[pick] = false;
                _bets[pick] = 0.0;
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

bool Player::hasBetOn(uint option)
{
    return _picked[option];
}
void Player::checkOut(uint winner, double odds)
{
    if ( _picked[winner] )
    _bankroll += _bets[winner] / odds;
}

bool Player::hasPlayed()
{
    return _played;
}

bool Player::broke()
{
    return _bankroll == 0.0;
}

void Player::setGameParameters(uint numCitiesP, double minBetP, double initialBankrollP)
{
    numCities = numCitiesP;
    minBet = minBetP;
    initialBankroll = initialBankrollP;
}
