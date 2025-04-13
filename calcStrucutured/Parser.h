
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>

class Calculator {
public:
    
    std::string run();
    Calculator();
    ~Calculator();

private:
   
    int precedence(const std::string& op);
    std::vector<std::string> tokenize(const std::string& expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);

};

#endif // CALCULATOR_H
