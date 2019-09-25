#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

// statistics class
typedef unsigned int uint;

namespace atsp{
namespace bet {

class PlayerStats
{
public:

    PlayerStats();

    uint getGamesAlive() const;
    uint getConsecutiveWins() const;
    uint getMaxGamesAlive() const;
    uint getMaxConsecutiveWins() const;

    static void resetRoundStats();
    static uint getRoundPlayers();
    static uint getRoundWinners();
    static uint getRoundBroken();

    // sets what weights more when comparing player's
    // performance: games alive or recent performance

    enum compareBy
    {
        gamesAlive, recentPerformance
    };

    static void setComparisson(compareBy);
    bool operator>(const PlayerStats &)const;
    bool operator<(const PlayerStats &)const;

    void alive();  // call every round
    void played(); // call when player bets
    void won();    // call when they bet and win
    void lost();   // call when they bet and lose.
    void broke();  // call when a player is cashed out

private:

    uint _gamesAlive;
    uint _consecutiveWins;
    uint _maxGamesAlive;
    uint _maxConsecutiveWins;

    static compareBy _compare;

    // # players that bet since last resetRoundStats;
    static uint _roundPlayers;
    static uint _roundWinners;
    static uint _roundBroken;

};

}
}
#endif // PLAYERSTATS_H
