#include "table.h"

#include <tuple>
#include <stdio.h>
#include <iostream>

using namespace BetDefs;

static constexpr unsigned int MIN_BET {5};
static constexpr unsigned int MAX_BET {4000};

Table::Table()
    :_balance(0)
    ,_rules(std::make_shared<TableRules>(MIN_BET, MAX_BET))
{
    
}

bool Table::addPlayer(std::shared_ptr<Player> player)
{
    if (!player->onAddedToTable(_rules)) {
        std::cout << "Player cannot sit at this table" << std::endl;
        return false;
    }

    _players.push_back(player);
    return true;
}

void Table::playRound()
{    
    _roulette.spin();

    for (auto player : _players) {
        BetType betType;
        Money betAmount;
        if (!player->takeBet(betType, betAmount)) {
            std::cout << "Player cannot bet at this time" << std::endl;
            continue;
        }
        
        BetResult result = BetResult::Invalid;
        Money payout = betAmount;

        if (!_rules->checkBet(betAmount)) {
            std::cout << "Invalid bet amount, rejecting bet" << std::endl;
        } else {
            if (_roulette.isBetWinner(betType)) {
                result = BetResult::Won;
                payout = betAmount * (1 + betPayout(betType));
            } else {
                result = BetResult::Lost;
                payout = 0;
            }
        }

        player->onBetResult(result, payout);
        _balance += betAmount - payout;
    }
}

Balance Table::getTableBalance() const
{
    return _balance;
}

Balance Table::getCurrentPlayersBalance() const
{
    Balance balance = 0;

    for (const auto player : _players) {
        balance += player->getBalance();
    }

    return balance;
}