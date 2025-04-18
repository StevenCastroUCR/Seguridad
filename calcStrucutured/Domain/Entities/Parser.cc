#include "Parser.h"
#include <iostream>

using namespace std;



Parser::Parser()
{

}

/// @brief Procesa una operacion matematica escrita en palabras, convierte las palabras a numeros,
///        realiza la operacion y muestra el resultado.
///        El ciclo se repite mientras el usuario desee continuar.
/// @return Una cadena vacía despues de terminar las operaciones.
string Parser::textParser()
{
    while (true)
    {
        string input;
        cout << "Escriba la operacion:\n";
        getline(cin, input);
     
        string inputToCheck;
        for (char c : input)
        {
            if (c != ' ')
            {
                inputToCheck += std::tolower(c);
            }
        }
        string parsed = inputToNumbers(inputToCheck);
        cout << "Cadena parseada: " << parsed << endl;

        
        bool validInput = true;
        for (char c : parsed) {
            if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')') {
                cout << "Error: La entrada contiene caracteres no válidos." << endl;
                validInput = false;
                break;
            }
        }

        if (!validInput || parsed.empty()) {
            cout << "Por favor, ingrese una operación válida.\n";
            continue;
        }


        if (parsed.empty()) {
            continue;
        }
        try {
            auto tokens = tokenize(parsed);

            auto postfix = infixToPostfix(tokens);
            double result = evalPostfix(postfix);
            cout << "Resultado: " << result << endl;
        } catch (const std::exception& e) {
            cout << "Error al procesar la operación: " << e.what() << endl;
        }

        if (!opContinue()) {
            return "";
        }        
    }
    return "";
}

/// @brief Convierte una cadena de entrada con numeros en forma de palabra 
///        en una expresion matematica con numeros y operadores aritmeticos.
/// @param input Cadena de texto que contiene una operacion matematica con numeros escritos en palabras.
/// @return Cadena convertida que contiene numeros y operadores listos para ser evaluados.
string Parser::inputToNumbers(const string& input)
{
    bool skip =false;
    string parsed;
    vector<size_t> operandPositions;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') ||
            (input[i] == '(') || (input[i] == ')'))
        {
            operandPositions.push_back(i);
        }
    }

    size_t start = 0;

    for (size_t i = 0; i <= operandPositions.size(); ++i)
    {
        size_t end = (i < operandPositions.size()) ? operandPositions[i] : input.size();
        string palabra = input.substr(start, end - start);

        string numero;
        if (!palabra.empty())
        {
            if (especiales.count(palabra))
            {
                numero = to_string(especiales[palabra]);
            }
            else if (decenas.count(palabra))
            {
                numero = to_string(decenas[palabra]);
            }
            else if (unidades.count(palabra))
            {
                numero = to_string(unidades[palabra]);
            }
            else
            {
                size_t y_pos = palabra.find("y");
                if (y_pos != string::npos)
                {
                    string parte1 = palabra.substr(0, y_pos);
                    string parte2 = palabra.substr(y_pos + 1);

                    int valor1 = 0, valor2 = 0;
                    if (decenas.count(parte1))
                    {
                        valor1 = decenas[parte1];
                    }
                    if (unidades.count(parte2))
                    {
                        valor2 = unidades[parte2];
                    }

                    if (valor1 > 0 && valor2 > 0)
                    {
                        numero = to_string(valor1 + valor2);
                    }
                    else
                    {
                       // skip = true;
                        //break;
                    }
                }
                else
                {
                  //  skip = true;
                   // break;
                }
            }
         
            parsed += numero;
        }

        if (i < operandPositions.size())
        {
            char op = input[operandPositions[i]];
            parsed += op;
            start = operandPositions[i] + 1;
        }
    }

    return parsed;
}

/// @brief Pregunta al usuario si desea realizar otra operacion.
/// @return `true` si el usuario desea continuar, `false` si desea salir.
bool Parser::opContinue() {
    string nextStep;
    while (true)
    {
        cout<< "Quiere hacer otra operacion? 1-) Si , 2-) No: \n";
        nextStep = utility.readInput("", 1);

        try {
            int option = stoi(nextStep);
            if (option == 1)
            {
                return true;
            }
            else if (option == 2)
            {
                return false;
            }
            else
            {
                cout << "Entrada invalida. Por favor escriba 1 o 2.\n";
            }
        } catch (const std::exception& e) {
            cout << "Entrada invalida. Por favor escriba 1 o 2.\n";
        }
    }
}

/// @brief Regresa el precedente de cualquier operador indicando el nivel de
///         presedencia mediante un entero
/// @param op String que representa el operador al que se le determina la pres
/// @return Regresa entero que representa la presedencia 0 si no se reconoce
int Parser::precedence(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

/// @brief "tokeniza" una expresopm matematica en componentes individuales
///         Operadores y operandos
/// @param expr Expresion a "tokenizar"
/// @return Regresa vector de strings donde cada string es un "token" de un
///         componente individual
std::vector<std::string> Parser::tokenize(const std::string &expr)
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

/// @brief Convierte una expresion infija a su notacion posfija
/// @param tokens   Vector de strings que representan la expresion infija a
///                 convetir cada string sera un entero, un operador +,-,/,*(,)
/// @return Regresa un vector de strings que representa el equivalente posfijo
std::vector<std::string> Parser::infixToPostfix(const std::vector<std::string> &tokens)
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
                ops.pop(); // quitar el parentesis izquierdo
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


/// @brief Evalua una expresion en forma posfija y regresa el resultado,
/// @param postfix Vector de strings que representa la expresion aritmetica
///                 El string puede ser un entero o un operador
/// @return Regresa el valor entero resultante de la expresion posfija
double Parser::evalPostfix(const vector<string>& postfix) {
    stack<double> evalStack;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            evalStack.push(stoi(token));
        } else {
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();
            if (token == "+") evalStack.push(a + b);
            else if (token == "-") evalStack.push(a - b);
            else if (token == "*") evalStack.push(a * b);
            else if (token == "/") evalStack.push(a / b);
        }
    }

    return evalStack.top();
}
