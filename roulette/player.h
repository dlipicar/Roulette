#ifndef PLAYER_H
#define PLAYER_H

#include "betdefs.h"

#include <memory>
#include <list>
#include <string>

class TableRules;

enum class PlayerStatus {
    Idle,
    WaitingToBet,
    WaitingForResult        
};

class Player {

public:

    Player() = delete;
    Player(const std::string &id, BetDefs::BetType betType);

    std::string getId() const;
    PlayerStatus getStatus() const;
    BetDefs::BetType getBetType() const;
    BetDefs::Money getCurrentBet() const;
    BetDefs::Balance getBalance() const;

    // Must be called after adding the player to a table
    bool onAddedToTable(std::shared_ptr<const TableRules> rules);
    // Must be called when a new bet round is started
    bool takeBet(BetDefs::BetType &type, BetDefs::Money &amount);
    // Must be called when the bet results are ready
    bool onBetResult(BetDefs::BetResult status, BetDefs::Money pay);

private:
    void printList() const;
    
    void resetList();
    void calculateNewBet();
    
    void onBetWon();
    void onBetLost();

    const std::string _id;
    const BetDefs::BetType _betType;
    PlayerStatus _playerStatus;

    std::shared_ptr<const TableRules> _rules;

    std::list<BetDefs::Money> _betList;
    BetDefs::Money _currentBet;

    BetDefs::Balance _balance;
};

#endif //PLAYER_H