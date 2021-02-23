#ifndef ROULETTE_H
#define ROULETTE_H

#include "bettype.h"

class Roulette {

public:
    Roulette();

    void spin();
    uint getNumber() const;

    bool isBetWinner(BetType bet) const;

private:
    bool isRed(uint number) const;
    bool isBlack(uint number) const;
    bool isEven(uint number) const;
    bool isOdd(uint number) const;
    bool isLow(uint number) const;
    bool isHigh(uint number) const;

    uint _number;
};

#endif //ROULETTE_H