#ifndef PLAYER_H
#define PLAYER_H

#include "base/random.h"

namespace atsp{
namespace bet{

typedef unsigned int uint;

class Player
{
public:

    static const uint buffsz = 512;

public:

    Player();

    // returns the sum of player rate (used to calculate the odds)
    double ratePicks(const uint picks[buffsz], uint count);
    void   bet(const double houseProbs[buffsz], uint count);
    void   reset();
    bool   hasBetOn(uint option);
    void   checkOut(uint winner, double odds);
    bool   hasPlayed();
    bool   broke();

    const double * rating; // access point to player's rating

public:

    static void setGameParameters(uint numCities, double minBet, double initialBankroll );

private:


    double _bankroll;

    double _myProb[buffsz]     = {0.0};    // player's knowlege
    double _myRating[buffsz]    = {0.0};    // player's rating for each given pick
    bool   _picked[buffsz]      = {false};  //
    double _bets[buffsz]        = {0.0};    // player bets
    bool   _played;                         // played or not some round
};


}
}
#endif // PLAYER_H
