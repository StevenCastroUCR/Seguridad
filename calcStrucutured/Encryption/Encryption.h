#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

class Encryption {
 private:
    void encrypt();
 protected:
    std::string xorCipher(const std::string &input);
};

#endif 