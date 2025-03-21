#ifndef MYLIB_VALIDATORS_H
#define MYLIB_VALIDATORS_H

#include <concepts>
#include <cmath>
#include <string>
#include <type_traits>

namespace mylib {

/**
 * Generic input validation template.
 * 
 * Provides default validation and type naming for arbitrary types.
 */
template<typename T, typename = void>
struct InputValidator {
    static bool is_valid(const T&) {
        return true; // Default validator accepts all values
    }
    
    static std::string type_name() {
        return "value";
    }
};

/**
 * Input validator specialization for integral types.
 */
template<typename T>
struct InputValidator<T, std::enable_if_t<std::is_integral<T>::value>> {
    static bool is_valid(const T&) {
        return true;
    }
    
    static std::string type_name() {
        return "integer";
    }
};

/**
 * Input validator specialization for floating-point types.
 * 
 * Performs validation to ensure finite values.
 */
template<typename T>
struct InputValidator<T, std::enable_if_t<std::is_floating_point<T>::value>> {
    static bool is_valid(const T& value) {
        return !std::isnan(value) && !std::isinf(value);
    }
    
    static std::string type_name() {
        return "number";
    }
};

/**
 * Input validator specialization for string.
 */
template<>
struct InputValidator<std::string> {
    static bool is_valid(const std::string& value) {
        return !value.empty();
    }
    
    static std::string type_name() {
        return "text";
    }
};

} // namespace mylib

#endif // MYLIB_VALIDATORS_H