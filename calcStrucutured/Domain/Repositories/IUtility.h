#ifndef IUTILITY_H
#define IUTILITY_H

#include <string>

class IUtility {
public:
    virtual ~IUtility() = default;

    // Pure virtual function to read input from the user with validation
    virtual std::string readInput(const std::string &prompt) = 0;

    // Pure virtual function to log events to a file
    virtual void log(const std::string &event) = 0;
};

#endif // IUTILITY_H