#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "../Repositories/IUtility.h"

using namespace std;


class Utility : public IUtility{
    public:
        Utility();
        ~Utility();
// Function to read input from the user with validation
string readInput(const string &prompt);

// Function to log events to a file
void log(const string &event);
        
    };




#endif // UTILITY_H
