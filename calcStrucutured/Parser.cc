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


int precedence(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

std::vector<std::string> tokenize(const std::string &expr)
{
    std::vector<std::string> tokens;
    std::string num;

    for (char ch : expr)
    {
        if (std::isdigit(ch))
        {
            num += ch;
        }
        else
        {
            if (!num.empty())
            {
                tokens.push_back(num);
                num.clear();
            }

            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
            {
                tokens.push_back(std::string(1, ch));
            }
        }
    }

    if (!num.empty())
        tokens.push_back(num);

    return tokens;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens)
{
    std::vector<std::string> output;
    std::stack<std::string> ops;

    for (const std::string &token : tokens)
    {
        if (isdigit(token[0]))
        {
            output.push_back(token);
        }
        else if (token == "(")
        {
            ops.push(token);
        }
        else if (token == ")")
        {
            while (!ops.empty() && ops.top() != "(")
            {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty() && ops.top() == "(")
            {
                ops.pop(); // quitar el paréntesis izquierdo
            }
        }
        else
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token))
            {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty())
    {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}
