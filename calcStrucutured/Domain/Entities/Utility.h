#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>

#include "../Repositories/IUtility.h"

using namespace std;


class Utility : public IUtility{
    public:
        Utility();
        ~Utility();
        string readInput(const string &prompt, size_t maxLength);
        string sanitizeInput(const string &input);

        void log(const string &event);
};
#endif // UTILITY_H
