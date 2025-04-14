#ifndef USERS_H
#define USERS_H

#include "../Repositories/IUsers.h"
#include "../Encryption/Encryption.h"
#include "Utility.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

class Users : public IUsers, public Encryption {
public:
    Users();
    ~Users();
    bool authentication(bool &isAdmin);
    void createUser();

private:
    bool userExists(const std::string &userVerfication);
    
};

#endif // USERS_H