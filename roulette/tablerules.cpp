#include "tablerules.h"

#include <stdio.h>
#include <iostream>

using namespace BetDefs;

TableRules::TableRules(const Money minBet, const Money maxBet)
    :_minBet(minBet),
     _maxBet(maxBet)
{
    
}

bool TableRules::checkBet(const Money betAmount) const
{
    return (betAmount >= _minBet) && (betAmount <= _maxBet);
}