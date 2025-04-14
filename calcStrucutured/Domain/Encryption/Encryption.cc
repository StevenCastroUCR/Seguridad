#include "Encryption.h"

using namespace std;

// Codigo de desencriptamiento usando el cifrado XOR
// https://stackoverflow.com/questions/20365005/c-xor-encryption
string Encryption::xorCipher(const string &input)
{
    char key = 'N';
    string output = input;
    for (char &c : output)
    {
        c ^= key;
    }
    return output;
}


void Encryption::encrypt()
{
    ifstream in("usersE.txt");
    ofstream out("users.txt", ios::out | ios::binary);
    string line;

    if (!in.is_open() || !out.is_open())
    {
        cerr << "Error opening files!" << endl;
        return;
    }
    while (getline(in, line))
    {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        out << xorCipher(line) << endl;
    }
    in.close();
    out.close();
        
}