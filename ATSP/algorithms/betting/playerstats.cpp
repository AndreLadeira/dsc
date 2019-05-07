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

bool PlayerStats::operator>(const PlayerStats & rhs) const
{
    if (_compare == PlayerStats::compareBy::gamesAlive)
    {
        if (_gamesAlive == rhs._gamesAlive)
            return _consecutiveWins > rhs._consecutiveWins;
        else
            return  _gamesAlive > rhs._gamesAlive;
    }
    else
    {
        if ( _consecutiveWins == rhs._consecutiveWins )
            return  _gamesAlive > rhs._gamesAlive;
        else
            return _consecutiveWins > rhs._consecutiveWins;
    }
}

bool PlayerStats::operator<(const PlayerStats &rhs) const
{
    return !( *this > rhs );
}
