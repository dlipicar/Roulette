#include <stdio.h>
#include <iostream>

#include "table.h"

static constexpr uint MIN_BET {5};
static constexpr uint MAX_BET{4000};

bool Table::addPlayer(std::shared_ptr<Player> player)
{
    if (!player->setBetLimits(MIN_BET, MAX_BET)) {
        std::cout << "Player cannot sit at this table";
        return false;
    }

    _players.push_back(player);
    return true;
}

void Table::playRound()
{
    _roulette.spin();

    for (auto player : _players) {
        if (_roulette.isBetWinner(player->getBetType())) {
            player->onBetWon();
        } else {
            player->onBetLost();
        }
    }
}

int Table::getTotalBalance() const
{
    int balance = 0;

    for (auto player : _players) {
        balance += player->getBalance();
    }

    return balance;
}
