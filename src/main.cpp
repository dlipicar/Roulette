#include <stdio.h>
#include <iostream>

#include "table.h"

#include <array>

static constexpr uint NUMBER_OF_ROUNDS {10000};

int main()
{
    std::cout << "Roulette start" << std::endl;

    Table table;
    const std::array playerBetTypes {BetType::Red, BetType::Black, BetType::Even, BetType::Odd, BetType::Low, BetType::High};

    std::vector<std::shared_ptr<Player> > players;
    for (auto betType : playerBetTypes) {
        auto player = std::make_shared<Player>((uint)betType, betType);
        players.push_back(player);
        table.addPlayer(player);
    }

    for (int i=0; i<NUMBER_OF_ROUNDS; i++) {
        table.playRound();
        
#ifdef DEBUG_MODE
        for (auto player : players) {
            std::cout << "Player balance: " << player->getBalance() << std::endl;
        }
#endif

        std::cout << "Round " << i << " balance: " << table.getTotalBalance() << std::endl;
    }

    std::cout << "Roulette end" << std::endl;
    return 0;
}
