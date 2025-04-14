#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "../Repositories/IParser.h"
#include "../Repositories/ICalculator.h" 
#include "../Repositories/IUsers.h"
#include "../Repositories/IUtility.h"
#include "../Repositories/ICalculator.h"
#include "Users.h"

class Controller
{
private:
    IParser *parser;
    ICalculator *calculator;
    IUsers* user;
    IUtility* utility;

public:
Controller(IUsers* user,IParser* parser, ICalculator* calculator,IUtility* utility);
int run();
void Menu(bool isAdmin);
};

#endif // CONTROLLER_H
