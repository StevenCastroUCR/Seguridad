#ifndef PARSER_H
#define PARSER_H

#include "../Repositories/IParser.h"
#include <string>
#include <vector>
#include <map>
#include <stack>

class Parser :public IParser
{
public:
    Parser();
    std::string textParser(string inputToCheck) ;

private:
    int precedence(const std::string &op);
    std::vector<std::string> tokenize(const std::string &expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens);

    string inputToNumbers(const string& inputToCheck);
    string parseOperand(const string& palabra);
    vector<size_t> getOperandPositions(const string& input);

    bool opContinue();


    std::map<std::string, int> unidades;
    std::map<std::string, int> especiales;
    std::map<std::string, int> decenas;

};

#endif // PARSER_H

