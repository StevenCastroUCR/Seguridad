#include "Calculator.h"
#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

/// @brief Evalua una expresion en forma posfija y regresa el resultado,
/// @param postfix Vector de strings que representa la expresion aritmetica
///                 El string puede ser un entero o un operador
/// @return Regresa el valor entero resultante de la expresion posfija
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
