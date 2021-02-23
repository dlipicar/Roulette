#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>

#include "bettype.h"
#include "player.h"
#include "roulette.h"

class Table {

public:
    Table() = default;

    bool addPlayer(std::shared_ptr<Player> player);
    void playRound();
    int getTotalBalance() const;

private:
    Roulette _roulette;
    std::vector<std::shared_ptr<Player> > _players;
};

#endif //TABLE_H