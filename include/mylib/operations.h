#ifndef MYLIB_OPERATIONS_H
#define MYLIB_OPERATIONS_H

#include <functional>
#include <stdexcept>

namespace mylib {

/**
 * Swaps two values using move semantics.
 */
template<typename T>
void swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

/**
 * Evaluates whether data meets specified criteria.
 *
 * @param data The data to evaluate
 * @param predicate Function that defines the criteria
 * @return true if data meets criteria, false otherwise
 * @throws std::invalid_argument if predicate is null
 */
template <typename T>
bool meets_criteria(const T& data, const std::function<bool(const T&)>& predicate) {
    if (!predicate) {
        throw std::invalid_argument("Predicate function cannot be null");
    }
    return predicate(data);
}

/**
 * Applies a transformation operation to a value.
 *
 * @param value The input value
 * @param operation The transformation function
 * @return The transformed result
 * @throws std::invalid_argument if operation is null
 */
template<typename T, typename R>
R apply_operation(const T& value, const std::function<R(const T&)>& operation) {
    if (!operation) {
        throw std::invalid_argument("Operation function cannot be null");
    }
    return operation(value);
}

} // namespace mylib

#endif // MYLIB_OPERATIONS_H