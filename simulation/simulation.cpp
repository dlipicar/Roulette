#include "simulation.h"

#include "table.h"

#include <stdio.h>
#include <iostream>
#include <array>
#include <memory>

using namespace BetDefs;

static constexpr uint NUMBER_OF_ROUNDS {10000};

void simulate()
{
    Table table;

    // Add one player for each BetType to the table
    table.addPlayer(std::make_shared<Player>("A", BetType::Red));
    table.addPlayer(std::make_shared<Player>("B", BetType::Black));
    table.addPlayer(std::make_shared<Player>("C", BetType::High));
    table.addPlayer(std::make_shared<Player>("D", BetType::Low));
    table.addPlayer(std::make_shared<Player>("E", BetType::Even));
    table.addPlayer(std::make_shared<Player>("F", BetType::Odd));

    // Simulate a number of rounds
    for (int i=0; i<NUMBER_OF_ROUNDS; i++) {
        table.playRound();
        std::cout << "Round " << i << " table balance: " << table.getTableBalance() << std::endl;
        std::cout << "Round " << i << " player balance: " << table.getCurrentPlayersBalance() << std::endl;
    }
}