#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include <cctype>

#include "../Repositories/IUtility.h"

using namespace std;
namespace fs = std::filesystem;

class Utility : public IUtility
{
public:
    Utility();
    ~Utility();
    string readInput(const string &prompt, size_t maxLength);
    string sanitizeInput(const string &input);

    void log(const string &event);

private:
    const string LOG_FILE = "log.txt";
    const string BACKUP_FILE = "log_old.txt";
    const uintmax_t MAX_LOG_SIZE = 5 * 1024 * 1024;
};
#endif // UTILITY_H
