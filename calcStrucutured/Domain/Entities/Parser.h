#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include <stack>

class Parser
{
public:
    std::string textParser();

private:
    int precedence(const std::string &op);
    std::vector<std::string> tokenize(const std::string &expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens);

};

#endif // PARSER_H

