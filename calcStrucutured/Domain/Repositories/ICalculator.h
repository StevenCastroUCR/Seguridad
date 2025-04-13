#ifndef ICALCULATOR_H
#define ICALCULATOR_H

#include <string>
#include <vector>


using namespace std;

class ICalculator {
public:
    virtual ~ICalculator() = default;
    virtual  int evalPostfix(const vector<std::string>& postfix) = 0;
};

#endif // ICALCULATOR_H
