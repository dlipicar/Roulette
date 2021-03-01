#include "betdefs.h"

namespace BetDefs
{
    unsigned int betPayout(BetType type)
    {
        unsigned int ret = 0;
        switch (type) {
            case BetType::Red: 
            case BetType::Black: 
            case BetType::Even: 
            case BetType::Odd: 
            case BetType::Low: 
            case BetType::High: 
                ret = 1;
                break;
        }

        return ret;
    }

    std::string betTypeToString(BetType type)
    {
        switch (type) {
            case BetType::Red: 
                return "Red";
            case BetType::Black: 
                return "Black";
            case BetType::Even: 
                return "Even";
            case BetType::Odd: 
                return "Odd";
            case BetType::Low: 
                return "Low";
            case BetType::High: 
                return "High";
        }

        return "ERROR";
    }
}