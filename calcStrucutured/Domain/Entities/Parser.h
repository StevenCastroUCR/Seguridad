#ifndef PARSER_H
#define PARSER_H

#include "../Repositories/IParser.h"
#include  "Utility.h"
#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Parser :public IParser
{
public:
    Utility utility;
    Parser();
    string textParser() ;

private:
    int precedence(const std::string &op);
    std::vector<std::string> tokenize(const std::string &expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens);

    string inputToNumbers(const string& inputToCheck);
    double evalPostfix(const std::vector<std::string>& postfix);

    bool opContinue();


    map<string, int> unidades = {
        {"cero", 0},{"uno", 1}, {"dos", 2}, {"tres", 3}, {"cuatro", 4}, {"cinco", 5},
        {"seis", 6}, {"siete", 7}, {"ocho", 8}, {"nueve", 9}, {"diez", 10}};
    
    map<string, int> especiales = {
        {"once", 11}, {"doce", 12}, {"trece", 13}, {"catorce", 14},
        {"quince", 15}, {"dieciseis", 16}, {"diecisiete", 17},
        {"dieciocho", 18}, {"diecinueve", 19}, {"veintiuno", 21},
        {"veintidos", 22}, {"veintitres", 23}, {"veinticuatro", 24},
        {"veinticinco", 25}, {"veintiseis", 26}, {"veintisiete", 27},
        {"veintiocho", 28}, {"veintinueve", 29}};
    
    map<string, int> decenas = {
        {"veinte", 20}, {"treinta", 30}, {"cuarenta", 40}, {"cincuenta", 50},
        {"sesenta", 60}, {"setenta", 70}, {"ochenta", 80}, {"noventa", 90}};
    
};

#endif // PARSER_H

