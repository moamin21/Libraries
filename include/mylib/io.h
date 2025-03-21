#ifndef MYLIB_IO_H
#define MYLIB_IO_H

#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

#include "validators.h"

namespace mylib {

// Forward declarations
template<typename T>
T read_value(const std::string& prompt, 
            std::function<bool(const T&)> validator = [](const T&){ return true; },
            const std::string& error_msg = "Invalid input. Please try again.");

template<typename T>
void print_value(const T& value, 
                const std::string& prefix = "", 
                const std::string& suffix = "", 
                bool add_newline = true);

template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_range(T n, 
           const std::string& header = "Range:",
           const std::string& prefix = "", 
           const std::string& suffix = "",
           bool descending = false);

template<typename T = int>
T read_number(const std::string& prompt = "Enter a number: ", 
             T min_value = std::numeric_limits<T>::lowest(),
             T max_value = std::numeric_limits<T>::max());

/**
 * Reads a name from standard input with validation.
 *
 * @param prompt Message to display before reading input
 * @return Validated name string
 */
std::string read_name(const std::string& prompt = "Enter your name: ");

/**
 * Formats and displays a result with a descriptive message.
 *
 * @param value The value to display
 * @param message Description of the value
 * @param prefix Text to prepend to output
 * @param suffix Text to append to output
 */
template<typename T>
void format_result(const T& value, 
                 const std::string& message,
                 const std::string& prefix = "",
                 const std::string& suffix = "");

// Template implementations

/**
 * Reads a value from standard input with validation.
 */
template<typename T>
T read_value(const std::string& prompt, 
            std::function<bool(const T&)> validator,
            const std::string& error_msg) {
    T value;
    bool valid = false;
    
    while (!valid) {
        std::cout << prompt;
        
        // Handle string input differently to accommodate spaces
        if constexpr (std::is_same_v<T, std::string>) {
            std::getline(std::cin, value);
        } else {
            std::cin >> value;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            // Check for failed input
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid " << InputValidator<T>::type_name() << " format. " << error_msg << std::endl;
                continue;
            }
        }
        
        // Run both the type-specific validator and the custom validator
        if (InputValidator<T>::is_valid(value) && validator(value)) {
            valid = true;
        } else {
            std::cout << error_msg << std::endl;
        }
    }
    
    return value;
}

/**
 * Outputs a value to standard output with optional formatting.
 */
template<typename T>
void print_value(const T& value, 
                const std::string& prefix, 
                const std::string& suffix, 
                bool add_newline) {
    std::cout << prefix << value << suffix;
    if (add_newline) {
        std::cout << std::endl;
    }
}

/**
 * Prints a range of integers from 1 to n (or n to 1 if descending).
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_range(T n, 
           const std::string& header,
           const std::string& prefix, 
           const std::string& suffix,
           bool descending) {
    if (!header.empty()) {
        std::cout << header << std::endl;
    }
    
    if (descending) {
        // Print from N down to 1
        for (T i = n; i >= 1; --i) {
            std::cout << prefix << i << suffix << std::endl;
        }
    } else {
        // Print from 1 up to N
        for (T i = 1; i <= n; ++i) {
            std::cout << prefix << i << suffix << std::endl;
        }
    }
}

/**
 * Reads a number within a specified range from standard input.
 */
template<typename T>
T read_number(const std::string& prompt,
             T min_value,
             T max_value) {
    static_assert(std::is_arithmetic_v<T>, "read_number can only be used with numeric types");
    
    // Create a range validator
    auto range_validator = [min_value, max_value](const T& num) {
        return num >= min_value && num <= max_value;
    };
    
    std::ostringstream error_msg;
    error_msg << "Please enter a number between " << min_value << " and " << max_value << ".";
    
    return read_value<T>(prompt, range_validator, error_msg.str());
}

/**
 * Formats and outputs a result with a descriptive message.
 */
template<typename T>
void format_result(const T& value, 
                 const std::string& message,
                 const std::string& prefix,
                 const std::string& suffix) {
    std::ostringstream output;
    output << prefix << message << ": " << value << suffix;
    
    std::cout << output.str() << std::endl;
}

} // namespace mylib

#endif // MYLIB_IO_H