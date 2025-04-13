#include "Parser.h"
#include <iostream>
using namespace std;

string textParser()
{

    while (true)
    {
        bool skip = false;
        //cin.ignore();
        string parsed;
        string inputToCheck;
        string input;
        std::cout << "Escriba la operacion:\n";
        std::getline(std::cin, inputToCheck);
        for (char c : inputToCheck)
        {
            if (c != ' ')
            {
                input += std::tolower(c);
            }
        }

        map<string, int> unidades = {
            {"uno", 1}, {"dos", 2}, {"tres", 3}, {"cuatro", 4}, {"cinco", 5}, {"seis", 6}, {"siete", 7}, {"ocho", 8}, {"nueve", 9}, {"diez", 10}};

        map<string, int> especiales = {
            {"once", 11}, {"doce", 12}, {"trece", 13}, {"catorce", 14}, {"quince", 15}, {"dieciseis", 16}, {"diecisiete", 17}, {"dieciocho", 18}, {"diecinueve", 19}, {"veintiuno", 21}, {"veintidos", 22}, {"veintitres", 23}, {"veinticuatro", 24}, {"veinticinco", 25}, {"veintiseis", 26}, {"veintisiete", 27}, {"veintiocho", 28}, {"veintinueve", 29}};

        map<string, int> decenas = {
            {"veinte", 20}, {"treinta", 30}, {"cuarenta", 40}, {"cincuenta", 50}, {"sesenta", 60}, {"setenta", 70}, {"ochenta", 80}, {"noventa", 90}};

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
                            skip = true;
                            break;
                        }
                    }
                    else
                    {
                        skip = true;
                        break;
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

        if (skip == true)
        {
       
            continue;
        }

        auto tokens = tokenize(parsed);
        auto postfix = infixToPostfix(tokens);
  
        string nextStep;

        while (true)
        {
            cout<< "Quiere hacer otra operacion? 1-) Si , 2-) No:\n";
            

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
    return "";
}

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
