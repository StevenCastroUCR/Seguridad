#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "../Repositories/IParser.h"
#include "../Repositories/ICalculator.h" 
#include "../Repositories/IUsers.h"
#include "../Repositories/ICalculator.h"

class Controller
{
private:
    IParser *parser;
    ICalculator *calculator;
    IUsers* user;

public:
Controller(IUsers* user,IParser* parser, ICalculator* calculator);
int run();
};

#endif // CONTROLLER_H
