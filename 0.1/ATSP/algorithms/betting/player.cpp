#include "player.h"

namespace
{
    static uint     numCities       = 0;
    static double   minBet          = 0.0;
    static double   initialBankroll = 0.0;
}

using namespace atsp::bet;

Player::Player():rating(_myRating),_played(false)
{
}

double Player::ratePicks(const uint *   p,
                         const uint *   notp,
                         uint           pickCount,
                         const uint *   trPoints,
                         uint           trCount)
{
    double total = 0.0;

    for(uint i = 0; i < pickCount; i++)
    {
        uint bit = 0x1;
        _myRating[i] = 1.0;

        if ( p[i] != 0 )
            for(uint mask = 0; mask < trCount; mask++  )
            {
                if ( bit & p[i] )
                    _myRating[i] *= _myProb[trPoints[mask]];
                bit <<= 1;
            }

        bit = 0x1;

        if ( notp[i] != 0 )
            for(uint mask = 0; mask < trCount; mask++  )
            {
                if ( bit & notp[i] )
                    _myRating[i] *= (1.0-_myProb[trPoints[mask]]);
                bit <<= 1;
            }
        total += _myRating[i];
    }
    return total;
}

void Player::bet(const double * houseProbs, uint pickCount)
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

                const double kelly = (po - 1.0) /
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
       _myProb[i] = base::fast_rand01();
}

bool Player::hasBetOn(uint option)
{
    return _picked[option];
}
void Player::checkOut(uint winner, double odds)
{
    _stats.alive();

    if ( _played )
    {
        _stats.played();

        if ( _picked[winner] )
        {
            _bankroll += _bets[winner] / odds;
            _stats.won();
        }
        else
        {
            _stats.lost();
        }
    }

    if (_bankroll == 0.0)
    {
        _stats.broke();
        reset();
    }
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

const PlayerStats &Player::getStats() const
{
    return _stats;
}

bool Player::operator>(const Player &rhs) const
{
    return _stats > rhs._stats;
}

bool Player::operator<(const Player &rhs) const
{
    return !(*this > rhs);
}

bool Player::operator==(const Player & rhs) const
{
    for (uint i = 0; i < numCities; i++)
        if ( (_myProb[i] - rhs._myProb[i]) > 1e-6 ) return false;

    return true;
}

void Player::getTrPoints(bool trPoints[]) const
{
    for (uint i = 0; i < numCities; ++i)
        if ( _myProb[i] > base::fast_rand01() )
            trPoints[i] = true;
}

//#include <memory>

//uint Player::getUID() const
//{
//    double dId = 0;
//    for (uint i = 0; i < numCities; ++i) {
//        dId += _myProb[i];
//    }
//    uint UID = 0;
//    std::memcpy(&UID,&dId,sizeof(uint));
//    return UID;
//}
