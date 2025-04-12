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

void menu(bool isAdmin);
string textParser();
int precedence(const std::string &op);
int evalPostfix(const std::vector<std::string> &postfix);
std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens);
std::vector<std::string> tokenize(const std::string &expr);
bool authentication(bool &isAdmin);
void createUSer();
bool userExists(const string &userVerfication);
string xorCipher(const string &input);
void log(const string &event);

//
void xorEncrypt();

int main()
{

    xorEncrypt();

    bool isAdmin = false;

    if (!authentication(isAdmin))
    {
        return 1;
    }
    menu(isAdmin);
    return 0;
}

void menu(bool isAdmin)
{
    int option;
    while (true)
    {
        cout << "Laboratorio 01 de seguridad" << endl;
        std::cout << "Calculadora texto\n"
                  << std::endl;
        if (isAdmin)
        {
            cout << "1. Crear usuario" << endl;
            cout << "2. Calcular de Texto" << endl;
            cout << "3. salir" << endl;
        }
        else
        {
            cout << "1. Calcular de Texto" << endl;
            cout << "2. Salir" << endl;
        }

        cout << "Digite una opcion: ";
        cin >> option;

        if (isAdmin)
        {
            switch (option)
            {
            case 1:
                createUSer();
                break;
            case 2:
                textParser();
                break;
            case 3:
                return;
            default:
                cout << "Opcion invalida\n";
                break;
            }
        }
        else
        {
            switch (option)
            {
            case 1:
                textParser();
                break;
            case 2:
                return;
            default:
                cout << "Opcion invalida\n";
                break;
            }
        }
    }
}

// log("<MENSAJE DE EVENTO>");

string textParser()
{

    while (true)
    {
        cin.ignore();
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
            {"once", 11}, {"doce", 12}, {"trece", 13}, {"catorce", 14}, {"quince", 15}, {"dieciseis", 16}, {"diecisiete", 17}, {"dieciocho", 18}, {"diecinueve", 19}};

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
                            numero = "???";
                        }
                    }
                    else
                    {
                        numero = "???";
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

        cout << "Cadena parseada: " << parsed << endl;
        auto tokens = tokenize(parsed);
        auto postfix = infixToPostfix(tokens);
        int resultado = evalPostfix(postfix);
        std::cout << "Resultado: " << resultado << std::endl;
        int nextStep;
        std::cout << "¿Quiere hacer otra operación?\n1-) Si , 2-) No\n " << std::endl;
        cin >> nextStep;
        std::cin.ignore();
        if (nextStep == 1)
        {
            /* code */
        }
        else if (nextStep == 2)
        {
            break;
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

int evalPostfix(const std::vector<std::string> &postfix)
{
    std::stack<double> stk;

    for (const std::string &token : postfix)
    {
        if (isdigit(token[0]))
        {
            stk.push(std::stoi(token));
        }
        else
        {
            double b = stk.top();
            stk.pop();
            double a = stk.top();
            stk.pop();

            if (token == "+")
                stk.push(a + b);
            else if (token == "-")
                stk.push(a - b);
            else if (token == "*")
                stk.push(a * b);
            else if (token == "/")
                stk.push(a / b);
        }
    }

    return stk.top();
}

bool authentication(bool &isAdmin)
{
    int attempts = 0;
    const int maxAttempts = 3;

    ifstream usersFile("users.txt");

    if (!usersFile)
    {
        cerr << "Error: No se encontro el archivo" << endl;
        return false;
    }

    while (attempts < maxAttempts)
    {
        string idUser;
        string password;
        cout << "Digite nombre usuario para continuar: ";
        cin >> idUser;
        cout << "Digite la contrasena: ";
        cin >> password;

        string line;

        usersFile.clear();
        usersFile.seekg(0, ios::beg);

        while (getline(usersFile, line))
        {
            isAdmin = false;
            line = xorCipher(line);
            istringstream iss(line);
            string start, user, pass;
            iss >> start;

            if (start == "admin")
            {
                iss >> user >> pass;
                isAdmin = true;
            }
            else
            {
                user = start;
                iss >> pass;
            }

            if (idUser == user && password == pass)
            {
                log("login successful: " + idUser);
                cout << (isAdmin ? "Cuenta Administrador " : "")
                     << "Bienvenido: " << idUser << "!" << endl;
                return true;
            }
        }
        log("login error: " + idUser);
        cout << "Error: usuario o contrasena invalidos" << endl;
        attempts++;
        if (attempts < maxAttempts)
        {
            cout << "Intentos restantes: " << (maxAttempts - attempts) << endl;
        }
    }

    cout << "Agoto el numero de intentos" << endl;
    return false;
};

void createUSer()
{
    string idUser, pass;
    int isAdmin;
    string line;

    while (true)
    {
        cout << "Digite el nombre Usuario: ";
        cin >> idUser;
        if (idUser.length() > 20)
        {
            log("Error user creation, invalid user name");
            cout << " Nombre de usuario excede la longitud permitida(20 caracteres).\n";
            continue;
        }
        if (userExists(idUser))
        {
            log("Error user creation, user already in use");
            cout << "Nombre de usuario ya existe\n";
            continue;
        }

        break;
    }

    while (true)
    {
        cout << "Digite la contrasena: ";
        cin >> pass;
        if (pass.length() > 20)
        {
            log("Error user creation, invalid password");
            cout << "Contraseña excede longitud permitida\n";
            continue;
        }
        string cpass;
        cout << "Digite la contrasena nuevamente: ";
        cin >> cpass;
        if (!(pass == cpass))
        {
            log("Error user creation, password mismatch");
            cout << "Las contrasenas no coinciden\n";
        }
    }

    while (true)
        cout << "Es un usuario administrador ? 1-) Si , 2-) No :";
    cin >> isAdmin;

    switch (isAdmin)
    {
    case 1:
        line = "admin " + idUser + " " + pass;
        break;
    case 2:
        line = idUser + " " + pass;
        break;
    default:
        cout << "Opcion invalida\n";
        break;
    }

    string encrypt = xorCipher(line);

    ofstream usersFile("users.txt", ios::app); // append mode
    if (!usersFile)
    {
        cerr << "Error al acceder a archivo!" << endl;
        return;
    }

    usersFile.close();
    log("User added succesfully" + idUser);
    cout << "Usuario añadido correctamente";
};

bool userExists(const string &userVerfication)
{
    ifstream usersFile("users.txt");
    string line;

    while (getline(usersFile, line))
    {
        string decryptedLine = xorCipher(line);
        istringstream iss(decryptedLine);
        string token;

        if (decryptedLine.find("admin") == 0)
        {
            iss >> token;
        }

        string existingLabel1;
        iss >> existingLabel1;

        if (existingLabel1 == userVerfication)
        {
            return true;
        }
    }
    return false;
}

// Codigo de desencriptamiento usando el cifrado XOR
// https://stackoverflow.com/questions/20365005/c-xor-encryption
string xorCipher(const string &input)
{
    char key = 'N';
    string output = input;
    for (char &c : output)
    {
        c ^= key;
    }
    return output;
}

void xorEncrypt()
{
    ifstream in("usersE.txt");
    ofstream out("users.txt");
    string line;

    if (!in.is_open() || !out.is_open())
    {
        cerr << "Error opening files!" << endl;
        return;
    }
    while (getline(in, line))
    {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        out << xorCipher(line) << endl;
    }
}

void log(const string &event)
{
    ofstream logFile("log.txt", ios::app);
    if (!logFile)
    {
        cerr << "Error al abrir archivo" << endl;
        return;
    }

    time_t now = time(0);
    char *dt = ctime(&now);
    if (dt[strlen(dt) - 1] == '\n')
    {
        dt[strlen(dt) - 1] = '\0';
    }

    logFile << "[" << dt << "] " << event << endl;
}