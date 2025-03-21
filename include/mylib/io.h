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

template<typename CharT>
typename std::enable_if<std::is_same<CharT, char>::value || 
                         std::is_same<CharT, wchar_t>::value>::type
print_char_range(CharT start, 
                CharT end, 
                const std::string& header = "",
                const std::string& prefix = "", 
                const std::string& suffix = "",
                bool descending = false);

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

/**
 * Prints a range of characters from start to end (inclusive).
 */
template<typename CharT>
typename std::enable_if<std::is_same<CharT, char>::value || 
                         std::is_same<CharT, wchar_t>::value>::type
print_char_range(CharT start, 
                CharT end, 
                const std::string& header,
                const std::string& prefix, 
                const std::string& suffix,
                bool descending) {
    if (!header.empty()) {
        std::cout << header << std::endl;
    }
    
    if (descending) {
        // Print from end down to start
        for (CharT c = end; c >= start; --c) {
            std::cout << prefix << c << suffix << std::endl;
        }
    } else {
        // Print from start up to end
        for (CharT c = start; c <= end; ++c) {
            std::cout << prefix << c << suffix << std::endl;
        }
    }
}

/**
 * Prints a multiplication table of specified dimensions.
 * 
 * @tparam T Type of numbers to use in the table
 * @param rows Number of rows in the table
 * @param columns Number of columns in the table
 * @param title Optional title for the table
 */
template<typename T = int>
typename std::enable_if<std::is_arithmetic<T>::value>::type
print_multiplication_table(T rows = 10, 
                          T columns = 10, 
                          const std::string& title = "Multiplication Table") {
    // Print title
    std::cout << "\n\n\t\t\t " << title << "\n\n";
    
    // Print column headers
    std::cout << "\t";
    for (T j = 1; j <= columns; ++j) {
        std::cout << j << "\t";
    }
    
    // Print separator
    std::cout << "\n";
    for (T j = 0; j <= columns; ++j) {
        std::cout << "________";
    }
    std::cout << "\n";
    
    // Print multiplication table
    for (T i = 1; i <= rows; ++i) {
        // Print row identifier with proper formatting
        std::cout << " " << i;
        if (i < 10) {
            std::cout << " |";
        } else {
            std::cout << " |";
        }
        std::cout << "\t";
        
        // Print row values
        for (T j = 1; j <= columns; ++j) {
            // Use the multiply function from calculator.h
            std::cout << calculator::multiply(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}

/**
 * Prints prime numbers within a specified range.
 * 
 * @tparam T Type of the numbers (must be integral)
 * @param start Starting number (inclusive)
 * @param end Ending number (inclusive)
 * @param header Optional header message
 * @param prefix Text to prepend to each prime number
 * @param suffix Text to append to each prime number
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_prime_numbers(T start, 
                   T end,
                   const std::string& header = "Prime Numbers:",
                   const std::string& prefix = "", 
                   const std::string& suffix = "") {
    if (start < 1) {
        start = 1;  // Adjust start to a valid value if needed
    }
    
    if (end < start) {
        throw std::invalid_argument("End value must be greater than or equal to start value");
    }
    
    if (!header.empty()) {
        std::cout << header << std::endl;
    }
    
    for (T i = start; i <= end; ++i) {
        if (calculator::is_prime<T>(i) == PrimeType::Prime) {
            std::cout << prefix << i << suffix << std::endl;
        }
    }
}

} // namespace mylib

#endif // MYLIB_IO_H