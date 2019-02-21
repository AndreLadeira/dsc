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
    void   gamble(const double odds[buffsz], uint count);
    void   reset(uint numCities = 0, double startCash = 0.0);

    const double * rates; // access point;

private:


    double _bankroll;

    double _knowledge[buffsz]   = {0.0};    // player's knowlege
    double _myOdds[buffsz]      = {0.0};    // how it rates each given pick
    bool   _picked[buffsz]      = {false};  //
    double _bets[buffsz]        = {0.0};    // its bets

    friend void service(Player p, uint winner, double odds[Player::buffsz] );

    static double minbet;


};

void service(Player p, uint winner, double odds[Player::buffsz] );

}
}
#endif // PLAYER_H
