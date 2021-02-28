#ifndef ROULETTE_H
#define ROULETTE_H

#include "betdefs.h"

class Roulette {

public:
    Roulette();

    // Spin the roulette to get a new number
    void spin();
    
    // Get the current number
    unsigned int getNumber() const;

    // Check a BetType against the current number
    bool isBetWinner(BetDefs::BetType bet) const;

#ifdef TEST
    unsigned int _number;
#endif

private:
    bool isRed(unsigned int number) const;
    bool isBlack(unsigned int number) const;
    bool isEven(unsigned int number) const;
    bool isOdd(unsigned int number) const;
    bool isLow(unsigned int number) const;
    bool isHigh(unsigned int number) const;

#ifndef TEST
    unsigned int _number;
#endif
};

#endif //ROULETTE_H