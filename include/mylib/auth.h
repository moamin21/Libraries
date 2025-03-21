#ifndef MYLIB_AUTH_H
#define MYLIB_AUTH_H

#include <functional>
#include <string>
#include "io.h"

namespace mylib {
namespace auth {

/**
 * Authentication result with status and error message.
 */
struct AuthResult {
    bool success;
    std::string message;
    
    AuthResult(bool success, const std::string& message = "") 
        : success(success), message(message) {}
    
    operator bool() const { return success; }
};

/**
 * Authenticates user with a PIN code.
 * 
 * @param correctPin The PIN to validate against
 * @param prompt Message to display when requesting PIN
 * @param maxAttempts Maximum number of attempts (0 for unlimited)
 * @param failureMsg Message to display on authentication failure
 * @return AuthResult with authentication status
 */
AuthResult authenticate_with_pin(
    const std::string& correctPin,
    const std::string& prompt = "Please enter PIN code: ",
    size_t maxAttempts = 0,
    const std::string& failureMsg = "Wrong PIN"
) {
    std::string enteredPin;
    size_t attempts = 0;
    
    // PIN validator function
    auto pinValidator = [](const std::string& pin) {
        // Basic validation - ensure PIN isn't empty
        // Could be extended with format validation if needed
        return !pin.empty();
    };
    
    while (maxAttempts == 0 || attempts < maxAttempts) {
        // Read PIN with validation
        enteredPin = read_value<std::string>(
            prompt, 
            pinValidator,
            "Invalid PIN format. Please try again."
        );
        
        // Increment attempt counter
        attempts++;
        
        // Check PIN
        if (enteredPin == correctPin) {
            return AuthResult(true, "Authentication successful");
        }
        
        // Display failure message if not the last attempt
        if (maxAttempts == 0 || attempts < maxAttempts) {
            std::cout << failureMsg << std::endl;
        }
    }
    
    return AuthResult(false, "Maximum authentication attempts exceeded");
}

/**
 * Authenticates user with username and password.
 * 
 * @param validator Function to validate credentials
 * @param usernamePrompt Message to display when requesting username
 * @param passwordPrompt Message to display when requesting password
 * @param maxAttempts Maximum number of attempts (0 for unlimited)
 * @param failureMsg Message to display on authentication failure
 * @return AuthResult with authentication status
 */
AuthResult authenticate_with_credentials(
    std::function<bool(const std::string&, const std::string&)> validator,
    const std::string& usernamePrompt = "Username: ",
    const std::string& passwordPrompt = "Password: ",
    size_t maxAttempts = 0,
    const std::string& failureMsg = "Invalid credentials"
) {
    std::string username, password;
    size_t attempts = 0;
    
    // Input validator
    auto inputValidator = [](const std::string& input) {
        return !input.empty();
    };
    
    while (maxAttempts == 0 || attempts < maxAttempts) {
        // Read username and password
        username = read_value<std::string>(
            usernamePrompt, 
            inputValidator,
            "Username cannot be empty"
        );
        
        password = read_value<std::string>(
            passwordPrompt, 
            inputValidator,
            "Password cannot be empty"
        );
        
        // Increment attempt counter
        attempts++;
        
        // Validate credentials
        if (validator(username, password)) {
            return AuthResult(true, "Authentication successful");
        }
        
        // Display failure message if not the last attempt
        if (maxAttempts == 0 || attempts < maxAttempts) {
            std::cout << failureMsg << std::endl;
        }
    }
    
    return AuthResult(false, "Maximum authentication attempts exceeded");
}

} // namespace auth
} // namespace mylib

#endif // MYLIB_AUTH_H