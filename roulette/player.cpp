#include "player.h"

#include "tablerules.h"

#include <stdio.h>
#include <iostream>
#include <limits>
#include <array>
#include <string>

using namespace BetDefs;

static constexpr std::array INITIAL_BET_LIST {1, 2, 3, 4};
static constexpr unsigned int INITIAL_BET = INITIAL_BET_LIST.back() + INITIAL_BET_LIST.front();

Player::Player(const std::string &id, BetType betType) :
    _id(id),
    _betType(betType),
    _playerStatus(PlayerStatus::Idle),
    _betList(INITIAL_BET_LIST.begin(), INITIAL_BET_LIST.end()),
    _balance(0)
{
    // Calculate initial bet
    calculateNewBet();
}

std::string Player::getId() const
{
    return _id;
}

PlayerStatus Player::getStatus() const
{
    return _playerStatus;
}

BetType Player::getBetType() const
{
    return _betType;
}

unsigned int Player::getCurrentBet() const
{
    return _currentBet;
}

bool Player::onAddedToTable(std::shared_ptr<const TableRules> rules)
{
    if (_playerStatus != PlayerStatus::Idle) {
        std::cout << "Player is already on a table" << std::endl;
    }

    if (!rules->checkBet(INITIAL_BET)) {
        std::cout << "Player's strategy unfit for this table" << std::endl;
        return false;
    }

    _rules = rules;
    _playerStatus = PlayerStatus::WaitingToBet;
    return true;
}

int Player::getBalance() const
{
    return _balance;
}

bool Player::takeBet(BetType &type, Money &amount)
{
    if (_playerStatus != PlayerStatus::WaitingToBet) {
        std::cout << "Player not waiting to bet" << std::endl;
        return false;
    }

    type = _betType;
    amount = _currentBet;
    
    _balance -= _currentBet;
    
    _playerStatus = PlayerStatus::WaitingForResult;
    return true;
}

bool Player::onBetResult(BetResult status, Money pay)
{
    if (_playerStatus != PlayerStatus::WaitingForResult) {
        std::cout << "Player not waiting for result" << std::endl;
        return false;
    }

    _balance += pay;

    switch(status) {
        case BetResult::Won:
            onBetWon();
            break;
        case BetResult::Lost:
            onBetLost();
            break;
        case BetResult::Invalid:
            std::cout << "Player " << _id << " invalid bet, resetting list" << std::endl;
            resetList();
            break;
    }
    
    _playerStatus = PlayerStatus::WaitingToBet;
    return true;
}

void Player::onBetLost()
{
    if (_betList.size() > 0) {
        _betList.pop_back();
    }

    if (_betList.size() > 0) {
        _betList.pop_front();
    }

    std::cout << "Player " << _id << " lost. Current balance " << _balance << std::endl;

    calculateNewBet();
}

void Player::onBetWon() {
    _betList.push_back(_currentBet);
    
    std::cout << "Player " << _id << " won. Current balance " << _balance << std::endl;

    calculateNewBet();
}

void Player::resetList()
{
    _betList.assign(INITIAL_BET_LIST.begin(), INITIAL_BET_LIST.end());
    calculateNewBet();
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
            
        if (!_rules || _rules->checkBet(_currentBet)) {
            betValid = true;
        }
    }

    printList();
    if (!betValid) {
        std::cout << "Player " << _id << " has an invalid bet! Resetting..." << std::endl;
        resetList();
    } else {
        std::cout << "Player " << _id << " next bet " << _currentBet << std::endl;
    }
}

void Player::printList() const
{
    std::string listStr = "Player " +_id + " list: ";

    for (const auto num : _betList) {
        listStr += " ";
        listStr += std::to_string(num);
    }

    std::cout << listStr << std::endl;
}