#ifndef TABLERULES_H
#define TABLERULES_H

#include "betdefs.h"

class TableRules {

public:
    TableRules() = delete;
    TableRules(const BetDefs::Money minBet, const BetDefs::Money maxBet);

    // Checks if a certain bet follows the table's rules
    bool checkBet(const BetDefs::Money betAmount) const;

private:
    const BetDefs::Money _minBet;
    const BetDefs::Money _maxBet;
};

#endif //TABLRULESE_H