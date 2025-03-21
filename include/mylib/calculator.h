#ifndef MYLIB_CALCULATOR_H
#define MYLIB_CALCULATOR_H

#include <cmath>
#include <stdexcept>

namespace mylib {
namespace calculator {

/**
 * Adds two numbers of potentially different types.
 * 
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 */
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

/**
 * Subtracts second number from first.
 * 
 * @param a First operand
 * @param b Second operand
 * @return Difference a - b
 */
template<typename T, typename U>
auto subtract(T a, U b) -> decltype(a - b) {
    return a - b;
}

/**
 * Multiplies two numbers.
 * 
 * @param a First operand
 * @param b Second operand
 * @return Product of a and b
 */
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

/**
 * Divides first number by second.
 * 
 * @param a Dividend
 * @param b Divisor
 * @return Quotient a / b
 * @throws std::invalid_argument if b is zero
 */
template<typename T, typename U>
auto divide(T a, U b) -> decltype(a / b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

/**
 * Returns half of a number as floating point result.
 * 
 * @param number Input value
 * @return Half of the input value
 */
template<typename T>
auto half(T number) -> decltype(number * 0.5) {
    return number * 0.5;
}

/**
 * Raises base to specified power.
 * 
 * @param base Base value
 * @param exponent Power to raise base to
 * @return base^exponent
 */
template<typename T, typename U>
auto power(T base, U exponent) -> decltype(std::pow(base, exponent)) {
    return std::pow(base, exponent);
}

} // namespace calculator
} // namespace mylib

#endif // MYLIB_CALCULATOR_H