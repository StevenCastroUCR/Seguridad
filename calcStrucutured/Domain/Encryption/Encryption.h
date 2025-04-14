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

using namespace std;
class Encryption {
 private:
    void encrypt();
 protected:
    string xorCipher(const string &input);
};

#endif 