#ifndef MYLIB_DATA_CONTAINER_H
#define MYLIB_DATA_CONTAINER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "io.h"

namespace mylib {

/**
 * Container class for structured heterogeneous data with named fields.
 * 
 * Provides type-safe access to fields through template methods.
 */
template<typename... Fields>
class DataContainer {
public:
    /**
     * Constructs container with specified field names.
     * 
     * @param names Vector of field names
     * @throws std::invalid_argument if names count doesn't match field count
     */
    explicit DataContainer(const std::vector<std::string>& names);
    
    /**
     * Sets field value at specified index.
     * 
     * @tparam Index Zero-based field index
     * @param value New value for the field
     */
    template<size_t Index>
    void set_field(const std::tuple_element_t<Index, std::tuple<Fields...>>& value);
    
    /**
     * Gets field value at specified index.
     * 
     * @tparam Index Zero-based field index
     * @return Const reference to field value
     */
    template<size_t Index>
    const std::tuple_element_t<Index, std::tuple<Fields...>>& get_field() const;
    
    /**
     * Gets field name at specified index.
     * 
     * @param index Zero-based field index
     * @return Const reference to field name
     * @throws std::out_of_range if index is out of bounds
     */
    const std::string& get_field_name(size_t index) const;
    
    /**
     * Returns number of fields in container.
     * 
     * @return Field count
     */
    constexpr size_t size() const;

private:
    std::tuple<Fields...> data;
    std::vector<std::string> field_names;
};

/**
 * Reads user input for a single field and sets it in the container.
 * 
 * @tparam Index Field index
 * @tparam Fields Field types
 * @param container Container to modify
 */
template<size_t Index, typename... Fields>
void read_and_set_field(DataContainer<Fields...>& container);

/**
 * Helper function to read all fields in a DataContainer.
 * 
 * @tparam Fields Field types
 * @tparam Indices Parameter pack of indices
 * @param container Container to populate
 * @param indices Indices sequence
 */
template<typename... Fields, size_t... Indices>
void read_data_container_helper(DataContainer<Fields...>& container, std::index_sequence<Indices...>);

/**
 * Creates and populates a DataContainer with user input.
 * 
 * @tparam Fields Field types
 * @param field_names Names for container fields
 * @return Populated DataContainer
 */
template<typename... Fields>
DataContainer<Fields...> read_data_container(const std::vector<std::string>& field_names);

/**
 * Prints a single field from a DataContainer.
 * 
 * @tparam Index Field index
 * @tparam Fields Field types
 * @param container Container to read from
 */
template<size_t Index, typename... Fields>
void print_field(const DataContainer<Fields...>& container);

/**
 * Helper function to print all fields in a DataContainer.
 * 
 * @tparam Fields Field types
 * @tparam Indices Parameter pack of indices
 * @param container Container to print
 * @param indices Indices sequence
 */
template<typename... Fields, size_t... Indices>
void print_data_container_helper(const DataContainer<Fields...>& container, std::index_sequence<Indices...>);

/**
 * Prints all fields in a DataContainer.
 * 
 * @tparam Fields Field types
 * @param container Container to print
 * @param header Optional header text
 */
template<typename... Fields>
void print_data_container(const DataContainer<Fields...>& container, const std::string& header = "");

// Template implementations

/**
 * DataContainer constructor implementation.
 */
template<typename... Fields>
DataContainer<Fields...>::DataContainer(const std::vector<std::string>& names) : field_names(names) {
    if (names.size() != sizeof...(Fields)) {
        throw std::invalid_argument("Number of field names must match number of fields");
    }
}

/**
 * Implementation of field setter.
 */
template<typename... Fields>
template<size_t Index>
void DataContainer<Fields...>::set_field(const std::tuple_element_t<Index, std::tuple<Fields...>>& value) {
    std::get<Index>(data) = value;
}

/**
 * Implementation of field getter.
 */
template<typename... Fields>
template<size_t Index>
const std::tuple_element_t<Index, std::tuple<Fields...>>& DataContainer<Fields...>::get_field() const {
    return std::get<Index>(data);
}

/**
 * Implementation of field name getter.
 */
template<typename... Fields>
const std::string& DataContainer<Fields...>::get_field_name(size_t index) const {
    if (index >= field_names.size()) {
        throw std::out_of_range("Field index out of range");
    }
    return field_names[index];
}

/**
 * Implementation of container size getter.
 */
template<typename... Fields>
constexpr size_t DataContainer<Fields...>::size() const {
    return sizeof...(Fields);
}

/**
 * Implementation of field input function.
 */
template<size_t Index, typename... Fields>
void read_and_set_field(DataContainer<Fields...>& container) {
    using FieldType = std::tuple_element_t<Index, std::tuple<Fields...>>;
    
    // Create prompt using field name
    std::string prompt = "Enter " + container.get_field_name(Index) + ": ";
    
    // Read the value and set it in the container
    FieldType value = read_value<FieldType>(prompt);
    container.template set_field<Index>(value);
}

/**
 * Helper implementation for reading all container fields.
 */
template<typename... Fields, size_t... Indices>
void read_data_container_helper(DataContainer<Fields...>& container, std::index_sequence<Indices...>) {
    // Expand parameter pack to set each field
    (read_and_set_field<Indices, Fields...>(container), ...);
}

/**
 * Implementation of container reader function.
 */
template<typename... Fields>
DataContainer<Fields...> read_data_container(const std::vector<std::string>& field_names) {
    DataContainer<Fields...> container(field_names);
    
    // Use fold expression with index sequence to populate all fields
    read_data_container_helper(container, std::make_index_sequence<sizeof...(Fields)>{});
    
    return container;
}

/**
 * Implementation of single field printer.
 */
template<size_t Index, typename... Fields>
void print_field(const DataContainer<Fields...>& container) {
    std::cout << container.get_field_name(Index) << ": " 
              << container.template get_field<Index>() << std::endl;
}

/**
 * Helper implementation for printing all container fields.
 */
template<typename... Fields, size_t... Indices>
void print_data_container_helper(const DataContainer<Fields...>& container, std::index_sequence<Indices...>) {
    // Expand parameter pack to print each field
    (print_field<Indices, Fields...>(container), ...);
}

/**
 * Implementation of container printer function.
 */
template<typename... Fields>
void print_data_container(const DataContainer<Fields...>& container, const std::string& header) {
    if (!header.empty()) {
        std::cout << header << std::endl;
    }
    
    // Print all fields using parameter pack expansion
    print_data_container_helper(container, std::make_index_sequence<sizeof...(Fields)>{});
}

} // namespace mylib

#endif // MYLIB_DATA_CONTAINER_H