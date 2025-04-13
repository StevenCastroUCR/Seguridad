#ifndef USERS_H
#define USERS_H

#include "Encryption.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

class Users : public Encryption {
    void log(const std::string &event);
public:
    Users();
    ~Users();
    bool authentication(bool &isAdmin);
    std::string readInput(const std::string &prompt);
    void createUser();

private:
    bool userExists(const std::string &userVerfication);
    
};

#endif // USERS_H