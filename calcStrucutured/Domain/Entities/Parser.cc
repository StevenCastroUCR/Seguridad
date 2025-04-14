#include "Parser.h"
#include <iostream>

using namespace std;

map<string, int> unidades = {
    {"uno", 1}, {"dos", 2}, {"tres", 3}, {"cuatro", 4}, {"cinco", 5},
    {"seis", 6}, {"siete", 7}, {"ocho", 8}, {"nueve", 9}, {"diez", 10}};

map<string, int> especiales = {
    {"once", 11}, {"doce", 12}, {"trece", 13}, {"catorce", 14},
    {"quince", 15}, {"dieciseis", 16}, {"diecisiete", 17},
    {"dieciocho", 18}, {"diecinueve", 19}, {"veintiuno", 21},
    {"veintidos", 22}, {"veintitres", 23}, {"veinticuatro", 24},
    {"veinticinco", 25}, {"veintiseis", 26}, {"veintisiete", 27},
    {"veintiocho", 28}, {"veintinueve", 29}};

map<string, int> decenas = {
    {"veinte", 20}, {"treinta", 30}, {"cuarenta", 40}, {"cincuenta", 50},
    {"sesenta", 60}, {"setenta", 70}, {"ochenta", 80}, {"noventa", 90}};


Parser::Parser()
{

}

/// @brief 
/// @return 
string Parser::textParser()
{
    while (true)
    {
        string input;
        cout << "Escriba la operacion:\n";
        getline(cin, input);
        
        string parsed = inputToNumbers(input);
        if (parsed.empty()) {
            continue;
        }

        auto tokens = tokenize(parsed);
        auto postfix = infixToPostfix(tokens);
  
        string nextStep;

        if (!opContinue) {
            return "";
        }        
    }
    return "";
}

string Parser::inputToNumbers(const string& inputToCheck)
{
    string input = "";
    bool skip = false;
    for (char c : inputToCheck)
    {
        if (c != ' ')
        {
            input += tolower(c);
        }
    }

    vector<size_t> operandPositions = getOperandPositions(input);
    
    size_t start = 0;
    string parsed;

    for (size_t i = 0; i <= operandPositions.size(); ++i)
    {
        size_t end = (i < operandPositions.size()) ? operandPositions[i] : input.size();
        string palabra = input.substr(start, end - start);

        string numero =  parseOperand(palabra);
        if (!numero.empty())
        {
            
            skip = true;
            break;
        }

        parsed += numero;

        if (i < operandPositions.size())
        {
            char op = input[operandPositions[i]];
            parsed += op;
            start = operandPositions[i] + 1;
        }
    }
    return skip ? "" : parsed;
}

string Parser::parseOperand(const string& palabra)
{
    string numero;

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
                return "";
            }
        }
        else
        {
            return "";
        }
    }
}

vector<size_t> Parser::getOperandPositions(const string& input)
{
    vector<size_t> positions;
    for (size_t i = 0; i < input.size(); ++i)
    {
        if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*')
            || (input[i] == '/') || (input[i] == '(') || (input[i] == ')'))
        {
            positions.push_back(i);
        }
    }
    return positions;  
}

bool Parser::opContinue() {
    string nextStep;
    while (true)
        {
            cout<< "Quiere hacer otra operacion? 1-) Si , 2-) No:\n";
            getline(cin, nextStep);

            if (stoi(nextStep) == 1)
            {
                break;
            }
            else if (stoi(nextStep) == 2)
            {
                return "";
            }
            else
            {
                std::cout << "Entrada invalida. Por favor escriba 1 o 2.\n";
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
