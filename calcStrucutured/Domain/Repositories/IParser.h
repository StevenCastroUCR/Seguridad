#ifndef IPARSER_H
#define IPARSER_H

#include <string>
#include <vector>

class IParser
{
public:
    virtual ~IParser() = default;

    // Pure virtual method to be implemented by derived classes
    virtual std::string textParser(std::string inputTocheck) = 0;
};

#endif // IPARSER_H