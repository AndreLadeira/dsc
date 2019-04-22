#include "playerstats.h"

using namespace atsp::bet;

PlayerStats::compareBy PlayerStats::_compare =
        PlayerStats::compareBy::gamesAlive;

uint PlayerStats::_roundBroken = 0;
uint PlayerStats::_roundPlayers = 0;
uint PlayerStats::_roundWinners = 0;

PlayerStats::PlayerStats():_gamesAlive(0),_consecutiveWins(0),
    _maxGamesAlive(0),_maxConsecutiveWins(0)
{
}
void PlayerStats::resetRoundStats()
{
    _roundBroken = _roundPlayers = _roundWinners = 0;
}

uint PlayerStats::getRoundPlayers()
{
    return _roundPlayers;
}

uint PlayerStats::getRoundWinners()
{
    return _roundWinners;
}

uint PlayerStats::getRoundBroken()
{
   return _roundBroken;
}
void PlayerStats::alive()
{
    _gamesAlive++;
    if (_gamesAlive > _maxGamesAlive)
        _maxGamesAlive = _gamesAlive;
}

void PlayerStats::played()
{
    _roundPlayers++;
}

void PlayerStats::won()
{
    _consecutiveWins++;
    _roundWinners++;
    if (_consecutiveWins > _maxConsecutiveWins)
        _maxConsecutiveWins = _consecutiveWins;
}

void PlayerStats::lost()
{
    _consecutiveWins = 0;
}

void PlayerStats::broke()
{
    _roundBroken++;
    _gamesAlive = 0;
    _consecutiveWins = 0;
}
uint PlayerStats::getGamesAlive() const
{
    return _gamesAlive;
}

uint PlayerStats::getConsecutiveWins() const
{
   return _consecutiveWins;
}

uint PlayerStats::getMaxGamesAlive() const
{
    return  _maxGamesAlive;
}

uint PlayerStats::getMaxConsecutiveWins() const
{
    return _maxConsecutiveWins;
}

void PlayerStats::setComparisson(PlayerStats::compareBy c)
{
    _compare = c;
}

bool PlayerStats::operator ()(const PlayerStats &a, const PlayerStats &b) const
{
    if (_compare == PlayerStats::compareBy::gamesAlive)
    {
        if (a._gamesAlive == b._gamesAlive)
            return a._consecutiveWins > b._consecutiveWins;
        else
            return  a._gamesAlive > b._gamesAlive;
    }
    else
    {
        if ( a._consecutiveWins == b._consecutiveWins )
            return  a._gamesAlive > b._gamesAlive;
        else
            return a._consecutiveWins > b._consecutiveWins;
    }
}
