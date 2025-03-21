#ifndef MYLIB_TYPES_H
#define MYLIB_TYPES_H

#include <string>
#include <vector>

namespace mylib {

/**
 * Enumeration of number properties.
 */
enum class NumberType { 
    Even = 0,
    Odd = 1,
    Positive = 2,
    Negative = 3,
    Zero = 4
};

/**
 * Converts a NumberType enum value to its string representation.
 *
 * @param type The NumberType to convert
 * @return String representation of the NumberType
 */
std::string to_string(NumberType type);

/**
 * Analyzes a number and returns its properties.
 * 
 * For integral types, checks even/odd status.
 * For all numeric types, determines sign.
 */
template<typename T>
std::vector<NumberType> analyze_number(T number) {
    static_assert(std::is_arithmetic_v<T>, "analyze_number can only be used with numeric types");
    
    std::vector<NumberType> properties;
    
    // Check if even or odd (integral types only)
    if constexpr (std::is_integral_v<T>) {
        properties.push_back((number % 2 == 0) ? NumberType::Even : NumberType::Odd);
    }
    
    // Check sign
    if (number > 0) {
        properties.push_back(NumberType::Positive);
    } else if (number < 0) {
        properties.push_back(NumberType::Negative);
    } else {
        properties.push_back(NumberType::Zero);
    }
    
    return properties;
}

/**
 * Outputs the properties of a number to standard output.
 */
template<typename T>
void print_number_properties(T number) {
    std::vector<NumberType> properties = analyze_number(number);
    
    std::cout << "Number " << number << " is: ";
    for (size_t i = 0; i < properties.size(); ++i) {
        std::cout << to_string(properties[i]);
        if (i < properties.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

/**
 * Enumeration for prime number properties.
 */
enum class PrimeType {
    Prime = 1,
    NotPrime = 2
};

/**
 * Converts a PrimeType enum value to its string representation.
 *
 * @param type The PrimeType to convert
 * @return String representation of the PrimeType
 */
std::string to_string(PrimeType type);

/**
 * Enumeration for perfect number status.
 */
enum class PerfectNumberType {
    Perfect = 1,
    NotPerfect = 2
};

/**
 * Converts a PerfectNumberType enum value to its string representation.
 */
std::string to_string(PerfectNumberType type);

/**
 * Checks if a number is a perfect number.
 * A perfect number is equal to the sum of its proper divisors.
 * 
 * @tparam T Type of the number (must be integral)
 * @param number The number to check
 * @return PerfectNumberType::Perfect if the number is perfect, 
 *         PerfectNumberType::NotPerfect otherwise
 * @throws std::invalid_argument if number is less than or equal to 0
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value, PerfectNumberType>::type
is_perfect_number(T number) {
    if (number <= 0) {
        throw std::invalid_argument("Number must be positive");
    }
    
    T sum = 0;
    
    // Find all proper divisors and sum them
    for (T i = 1; i < number; ++i) {
        if (number % i == 0) {
            sum += i;
        }
    }
    
    return (sum == number) ? PerfectNumberType::Perfect : PerfectNumberType::NotPerfect;
}

} // namespace mylib

#endif // MYLIB_TYPES_H