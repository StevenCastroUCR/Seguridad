#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <ctime>

class Encryption {
 private:
    void encrypt();
 protected:
    std::string xorCipher(const std::string &input);
};

#endif 