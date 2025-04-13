
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Calculator {
public:
    
    std::string run();

private:
   
    int precedence(const std::string& op);
    std::vector<std::string> tokenize(const std::string& expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);

};

#endif // CALCULATOR_H
