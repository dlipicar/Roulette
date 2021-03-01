#include "table.h"

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

    // Bet will be taken on the first round
    _playerStateList.push_back(PlayerState(player, false, BetType::Red, 0));
    return true;
}

void Table::playRound()
{   
    // Take all the bets
    for (auto &playerState : _playerStateList) {
        auto &player = std::get<0>(playerState);
        bool &betTaken = std::get<1>(playerState);
        BetType &betType = std::get<2>(playerState);
        Money &betAmount = std::get<3>(playerState);

        if (!player->takeBet(betType, betAmount)) {
            std::cout << "Player cannot bet at this time" << std::endl;
            betTaken = false;
            continue;
        }

        if (!_rules->checkBet(betAmount)) {
            std::cout << "Invalid bet amount, returning bet money" << std::endl;
            betTaken = false;
            player->onBetResult(BetResult::Invalid, betAmount);
            continue;
        }

        betTaken = true;
    }

    // Spin the roulette
    _roulette.spin();

    // Distribute earnings
    for (auto &playerState : _playerStateList) {
        auto &player = std::get<0>(playerState);
        bool &betTaken = std::get<1>(playerState);
        const BetType &betType = std::get<2>(playerState);
        const Money &betAmount = std::get<3>(playerState);

        if (!betTaken) {
            continue;
        }

        BetResult result = BetResult::Lost;
        Money payout = 0;
        if (_roulette.isBetWinner(betType)) {
            // Player won, pay original amount plus prize
            result = BetResult::Won;
            payout = betAmount * (1 + betPayout(betType));
        } else {
            // Player lost, pay nothing
        }

        player->onBetResult(result, payout);
        betTaken = false;
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

    for (const auto &playerState : _playerStateList) {
        balance += std::get<0>(playerState)->getBalance();
    }

    return balance;
}