#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

class Calculator {
public:
    
    std::string run();

private:
   
    int precedence(const std::string& op);
    std::vector<std::string> tokenize(const std::string& expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
    int evalPostfix(const std::vector<std::string>& postfix);


    std::string readInput(const std::string& prompt);
    void log(const std::string& message);
};

#endif // CALCULATOR_H
