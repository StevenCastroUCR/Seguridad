#include "Utility.h"
#include <iostream>

string readInput(const string &prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        istringstream iss(input);
        string word, leftover;
        iss >> word >> leftover;

        if (word.empty())
        {
            log("Error information not entered");
            cout << "Error no ha digitado.\n";
        }
        else if (!leftover.empty())
        {
            log("Error invalid input");
            cout << "La entrada no es valida intelo de nuevo\n";
        }
        else
        {
            return word;
        }
    }
}

void log(const string &event)
{
    ofstream logFile("log.txt", ios::app);
    if (!logFile)
    {
        cerr << "Error al abrir archivo" << endl;
        return;
    }

    time_t now = time(0);
    char *dt = ctime(&now);
    if (dt[strlen(dt) - 1] == '\n')
    {
        dt[strlen(dt) - 1] = '\0';
    }

    logFile << "[" << dt << "] " << event << endl;
}