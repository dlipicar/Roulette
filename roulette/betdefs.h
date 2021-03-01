#ifndef BETDEFS_H
#define BETDEFS_H

#include <string>

namespace BetDefs
{
    // Type for actual money
    using Money = unsigned int;

    // Type for accumulated profit/loss
    using Balance = int;

    // Enum for allowed bet types
    enum class BetType {
        Red,
        Black,
        Even,
        Odd,
        Low,
        High
    };

    // Enum containing possible bet results
    enum class BetResult {
        Won,
        Lost,
        Invalid
    };

    // Returns how many times a certain winning BetType is paid
    unsigned int betPayout(BetType type);

    // Returns a string representing the BetType
    std::string betTypeToString(BetType type);
}

#endif //BETDEFS_H
