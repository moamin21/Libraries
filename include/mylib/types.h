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

} // namespace mylib

#endif // MYLIB_TYPES_H