#ifndef TABLE_H
#define TABLE_H

#include "betdefs.h"
#include "player.h"
#include "roulette.h"
#include "tablerules.h"

#include <tuple>
#include <list>
#include <memory>

class Table {
    // Player State containing Player reference, whether their bet was taken, their bet type and the bet amount
    using PlayerState = std::tuple<std::shared_ptr<Player>, bool, BetDefs::BetType, BetDefs::Money>;

public:
    Table();

    // Add a player to the table
    bool addPlayer(std::shared_ptr<Player> player);
    
    // Play a round (spin + take bets + distribute earnings)
    void playRound();

    // Returns the table's total balance since the beginning
    BetDefs::Balance getTableBalance() const;
    
    // Returns the accumulated balance of the currently sitting players
    BetDefs::Balance getCurrentPlayersBalance() const;

private:
    bool checkBet(BetDefs::BetType type); 

    std::shared_ptr<TableRules> _rules;
    Roulette _roulette;
    std::list<PlayerState> _playerStateList;
    BetDefs::Balance _balance;
};

#endif //TABLE_H