#include <stdio.h>
#include <iostream>

#include <limits>
#include <array>

#include "player.h"

static constexpr std::array INITIAL_BET_LIST {1, 2, 3, 4};
static constexpr uint INITIAL_BET = INITIAL_BET_LIST.back() + INITIAL_BET_LIST.front();

Player::Player(uint id, BetType betType) :
    _id(id),
    _betType(betType),
    _minBet(0),
    _maxBet(std::numeric_limits<uint>::max()),
    _betList(INITIAL_BET_LIST.begin(), INITIAL_BET_LIST.end()),
    _balance(0)
{
    // Calculate initial bet
    calculateNewBet();
}

BetType Player::getBetType() const
{
    return _betType;
}

bool Player::setBetLimits(const uint minBet, const uint maxBet)
{
    if (INITIAL_BET < minBet) {
        std::cout << "Minimum bet " << minBet << " should not be greater than player's initial bet " << INITIAL_BET << std::endl;
        return false;
    }

    if (INITIAL_BET > maxBet) {
        std::cout << "Maximum bet " << maxBet << " should not be smaller than player's initial bet " << INITIAL_BET << std::endl;
        return false;
    }

    _minBet = minBet;
    _maxBet = maxBet;

    return true;
}

int Player::getBalance() const
{
    return _balance;
}

void Player::onBetLost() {
    if (_betList.size() > 0) {
        _betList.pop_back();
    }

    if (_betList.size() > 0) {
        _betList.pop_front();
    }

    _balance -= _currentBet;

    std::cout << "Player " << _id << " lost " << _currentBet << ". Current balance " << _balance << std::endl;

    calculateNewBet();
}

void Player::onBetWon() {
    _betList.push_back(_currentBet);

    _balance += _currentBet;
    
    std::cout << "Player " << _id << " won " << _currentBet << ". Current balance " << _balance << std::endl;

    calculateNewBet();
}

void Player::resetList()
{
    _betList.assign(INITIAL_BET_LIST.begin(), INITIAL_BET_LIST.end());
}

void Player::calculateNewBet()
{
    bool betValid = false;
    if (_betList.size() != 0) {
        if (_betList.size() == 1) {
            _currentBet = _betList.front();
        } else {
            _currentBet = _betList.front() + _betList.back();
        }
            
        if ((_currentBet >= _minBet) && (_currentBet <= _maxBet)) {
            betValid = true;
        }
    }

    if (!betValid) {
        resetList();
        calculateNewBet();
    }
}