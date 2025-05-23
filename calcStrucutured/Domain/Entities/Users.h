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
Utility utility;
    Users();
    ~Users();
    bool authentication(bool &isAdmin);
    void createUser();

private:
    bool userExists(const std::string &userVerfication);
    bool getUserData(ifstream &usersFile, string &userType
        , string &user, string &pass, int &attempts);
    void updateUserAttempts(const string &username, int newAttempts);
    string readHiddenPassword(const string &prompt, size_t maxLength);
};

#endif // USERS_H