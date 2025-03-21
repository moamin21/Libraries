#include "mylib/io.h"
#include <algorithm>

namespace mylib {

std::string read_name(const std::string& prompt) {
    // Validate that name is not empty and contains only letters and spaces
    auto name_validator = [](const std::string& name) {
        if (name.empty()) return false;
        
        return std::all_of(name.begin(), name.end(), [](char c) {
            return std::isalpha(c) || std::isspace(c) || c == '-' || c == '\'';
        });
    };
    
    return read_value<std::string>(prompt, name_validator, 
                                 "Name should contain only letters, spaces, hyphens, and apostrophes.");
}

} // namespace mylib