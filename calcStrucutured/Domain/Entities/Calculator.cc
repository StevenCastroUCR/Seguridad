#include "Calculator.h"
#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

int Calculator::evalPostfix(const vector<string>& postfix) {
    stack<int> evalStack;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            evalStack.push(stoi(token));
        } else {
            int b = evalStack.top(); evalStack.pop();
            int a = evalStack.top(); evalStack.pop();
            if (token == "+") evalStack.push(a + b);
            else if (token == "-") evalStack.push(a - b);
            else if (token == "*") evalStack.push(a * b);
            else if (token == "/") evalStack.push(a / b);
        }
    }

    return evalStack.top();
}
