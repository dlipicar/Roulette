#include <stdio.h>
#include <iostream>

#include <random>
#include <array>
#include <algorithm>

#include <roulette.h>

static constexpr uint MIN_ROULETTE_NUMBER {0};
static constexpr uint MAX_ROULETTE_NUMBER {36};
static constexpr std::array RED_NUMBER_LIST {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

Roulette::Roulette()
{
    // Initialize with valid random initial value
    spin();
}

void Roulette::spin()
{
    // Roulette has a uniform probability distribution
    std::random_device r;
    std::default_random_engine eng(r());
    std::uniform_int_distribution<uint> uniform_dist(MIN_ROULETTE_NUMBER, MAX_ROULETTE_NUMBER);

    _number = uniform_dist(eng);
    
    std::cout << "New number: " << _number << std::endl;
#ifdef DEBUG_MODE
    std::cout << "isRed: " << isRed(_number) << std::endl;
    std::cout << "isBlack: " << isBlack(_number) << std::endl;
    std::cout << "isEven: " << isEven(_number) << std::endl;
    std::cout << "isOdd: " << isOdd(_number) << std::endl;
    std::cout << "isLow: " << isLow(_number) << std::endl;
    std::cout << "isHigh: " << isHigh(_number) << std::endl;
#endif
}

uint Roulette::getNumber() const
{
    return _number;
}

bool Roulette::isBetWinner(BetType bet) const
{
    bool win = false;

    switch (bet) {
        case BetType::Red:
            win = isRed(_number);
            break;
        case BetType::Black:
            win = isBlack(_number);
            break;
        case BetType::Even:
            win = isEven(_number);
            break;
        case BetType::Odd:
            win = isOdd(_number);
            break;
        case BetType::Low:
            win = isLow(_number);
            break;
        case BetType::High:
            win = isHigh(_number);
            break;
    }

    return win;
}

bool Roulette::isRed(uint number) const
{
    return (number != 0) && (std::find(RED_NUMBER_LIST.begin(), RED_NUMBER_LIST.end(), number) != RED_NUMBER_LIST.end());
}

bool Roulette::isBlack(uint number) const
{
    return (number != 0) && !isRed(number);
}

bool Roulette::isEven(uint number) const
{
    return (number != 0) && (number % 2 == 0);
}

bool Roulette::isOdd(uint number) const
{
    return (number != 0) && !isEven(number);
}

bool Roulette::isLow(uint number) const
{
    return (number != 0) && (number <= MAX_ROULETTE_NUMBER/2);
}

bool Roulette::isHigh(uint number) const
{
    return (number != 0) && !isLow(number);
}
