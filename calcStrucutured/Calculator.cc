#include "Calculator.h"
#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

string Calculator::readInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

void Calculator::log(const string& message) {
    cout << message << endl;
}

int Calculator::precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

vector<string> Calculator::tokenize(const string& expr) {
    vector<string> tokens;
    string number;
    for (char ch : expr) {
        if (isspace(ch)) continue;

        if (isdigit(ch)) {
            number += ch;
        } else {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(string(1, ch));
        }
    }
    if (!number.empty()) {
        tokens.push_back(number);
    }
    return tokens;
}

vector<string> Calculator::infixToPostfix(const vector<string>& tokens) {
    vector<string> postfix;
    stack<string> operators;

    for (const string& token : tokens) {
        if (isdigit(token[0])) {
            postfix.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                postfix.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // pop '('
        } else {
            while (!operators.empty() && precedence(token) <= precedence(operators.top())) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }

    return postfix;
}

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

string Calculator::run() {
    string expression = readInput("Ingrese la operación: ");
    vector<string> tokens = tokenize(expression);
    vector<string> postfix = infixToPostfix(tokens);
    int result = evalPostfix(postfix);
    log("Resultado: " + to_string(result));
    return to_string(result);
}
