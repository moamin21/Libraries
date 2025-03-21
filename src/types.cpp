#include "mylib/types.h"

namespace mylib {

std::string to_string(NumberType type) {
    switch (type) {
        case NumberType::Even: return "Even";
        case NumberType::Odd: return "Odd";
        case NumberType::Positive: return "Positive";
        case NumberType::Negative: return "Negative";
        case NumberType::Zero: return "Zero";
        default: return "Unknown";
    }
}

std::string to_string(PrimeType type) {
    switch (type) {
        case PrimeType::Prime: return "Prime";
        case PrimeType::NotPrime: return "Not Prime";
        default: return "Unknown";
    }
}

} // namespace mylib