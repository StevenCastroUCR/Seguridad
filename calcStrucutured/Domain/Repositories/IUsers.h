#ifndef IUSERS_H
#define IUSERS_H

#include <string>

class IUsers {
 public:
    virtual ~IUsers() = default; 
    virtual bool authentication(bool &isAdmin) = 0;
    virtual void createUser() = 0;
};

#endif