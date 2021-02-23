#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "bettype.h"

class Player {

public:
    Player() = delete;
    Player(uint id, BetType betType);

    bool setBetLimits(const uint minBet, const uint maxBet);

    BetType getBetType() const;
    int getBalance() const;
    void onBetLost();
    void onBetWon();

private:
    void resetList();
    void calculateNewBet();

    const uint _id;
    const BetType _betType;

    uint _maxBet;
    uint _minBet;

    std::list<uint> _betList;
    uint _currentBet;
    int _balance;
};

#endif //PLAYER_H