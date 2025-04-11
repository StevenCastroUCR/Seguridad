#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;


void menu(bool isAdmin);
string textParser();
int precedence(const std::string& op);
int evalPostfix(const std::vector<std::string>& postfix);
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
std::vector<std::string> tokenize(const std::string& expr);
bool authentication(bool& isAdmin);
void createUSer();
string xorCipher(const string& input);
void log(const string& event);

/* void encript(); //Delete this

void encript
   () {
        ifstream in("usersE.txt");
        ofstream out("users.txt");
        string line;
    
        while (getline(in, line)) {
            out << xorDecrypt(line) << endl;
        }
    
        cout << "Encryption complete! Saved" << endl;
    }
*/

int main() {
    
    // encript();
    bool isAdmin= false;

    if (!authentication(isAdmin)) {
        return 1; 
    }
    menu(isAdmin);
    return 0;
}

void menu(bool isAdmin){
    int option;
    while (true) {
        cout << "Laboratorio 01 de seguridad"<<endl;
        std::cout << "Calculadora texto\n" << std::endl;
        if (isAdmin) {
            cout << "1. Crear usuario" << endl;
            cout << "2. Calcular de Texto" << endl;
            cout << "3. salir" << endl;
        } else {
            cout << "1. Calcular de Texto" << endl;
            cout << "2. Salir" << endl;
        }

        cout << "Digite una opcion: ";
        cin >> option;
        
        if  (isAdmin) {
            switch (option) {
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
        } else {
            switch (option) {
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
string textParser() {
    string input;
    cin>> input;
    map<string, string> unidades = {
        {"uno", "1"}, {"dos", "2"}, {"tres", "3"}, {"cuatro", "4"}, {"cinco", "5"},
        {"seis", "6"}, {"siete", "7"}, {"ocho", "8"}, {"nueve", "9"}, {"diez", "10"}
    };

    map<string, string> especiales = {
        {"once", "11"}, {"doce", "12"}, {"trece", "13"}, {"catorce", "14"}, {"quince", "15"},
        {"dieciseis", "16"}, {"diecisiete", "17"}, {"dieciocho", "18"}, {"diecinueve", "19"},
        {"veintiuno", "21"}, {"veintidos", "22"}, {"veintitres", "23"}, {"veinticuatro", "24"},
        {"veinticinco", "25"}, {"veintiseis", "26"}, {"veintisiete", "27"},
        {"veintiocho", "28"}, {"veintinueve", "29"}
    };

    map<string, string> decenas = {
        {"veinte", "20"}, {"treinta", "30"}, {"cuarenta", "40"},
        {"cincuenta", "50"}, {"sesenta", "60"}, {"setenta", "70"},
        {"ochenta", "80"}, {"noventa", "90"}
    };

    vector<size_t> operandPositions;
    for (size_t i = 0; i < input.size(); ++i) {
        if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/')) {
            operandPositions.push_back(i);
        }
    }

    string parsed;
    size_t start = 0;

    for (size_t i = 0; i <= operandPositions.size(); ++i) {
        size_t end = (i < operandPositions.size()) ? operandPositions[i] : input.size();
        string palabra = input.substr(start, end - start);

        string numero;
        if (unidades.count(palabra)) {
            numero = unidades[palabra];
        } else if (especiales.count(palabra)) {
            numero = especiales[palabra];
        } else if (decenas.count(palabra)) {
            numero = decenas[palabra];
        } else {
            numero = "???";
        }

        parsed += numero;

        if (i < operandPositions.size()) {
            parsed += input[operandPositions[i]];
            start = operandPositions[i] + 1;
        }
    }


    auto tokens = tokenize(parsed);
    auto postfix = infixToPostfix(tokens);
    int resultado = evalPostfix(postfix);
    std::cout << "Resultado: " << resultado << std::endl;
    return parsed;
}
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}
std::vector<std::string> tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::string num;

    for (char ch : expr) {
        if (std::isdigit(ch)) {
            num += ch;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
    }

    if (!num.empty())
        tokens.push_back(num);

    return tokens;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> ops;

    for (const std::string& token : tokens) {
        if (isdigit(token[0])) {
            output.push_back(token);
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}




int evalPostfix(const std::vector<std::string>& postfix) {
    std::stack<int> stk;

    for (const std::string& token : postfix) {
        if (isdigit(token[0])) {
            stk.push(std::stoi(token));
        } else {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();

            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else if (token == "/") stk.push(a / b);
        }
    }

    return stk.top();
}

bool authentication(bool& isAdmin) {
    int attempts = 0;
    const int maxAttempts = 3;

    ifstream usersFile("users.txt");

    if (!usersFile) {
            cerr << "Error: No se encontro el archivo" << endl;
            return false;
    }
    
    while (attempts < maxAttempts) {
        string idUser;
        string password;        
        cout << "Digite nombre usuario para continuar: ";
        cin >> idUser;
        cout << "Digite la contrasena: ";
        cin >> password;
        
        string line;

        while (getline(usersFile, line)) {
            isAdmin = false;
            line = xorCipher(line);
            istringstream iss(line);
            string start, user, pass;
            iss >> start;

            if (start == "admin") {
                iss >> user >> pass;
                isAdmin = true;
            } else {
                user = start;
                iss >> pass;
            }

            if (idUser == user && password == pass) {
                log("login successful: " + idUser);
                cout << (isAdmin ? "Cuenta Administrador " : "")
                     << "Bienvenido: " << idUser << "!" << endl;
                return true;
            }
        }
        log("login error: " + idUser);
        cout << "Error: usuario o contrasena invalidos" << endl;
        attempts++;
        if (attempts < maxAttempts) {
            cout << "Intentos restantes: " << (maxAttempts - attempts) << endl;
        }
    }

    cout << "Agotó el numero de intentos" << endl;
    return false;     
};

void createUSer() {
    string idUser, pass;
    string isAdmin;
    while (true) {
        cout << "Digite el nombre Usuario: ";
        if (idUser.length() > 20) {
            cout << " Nombre de usuario excede la longitud permitida(20 letras).\n";
        }
        cin >> idUser;
    }
    
    cout << "Enter label 2: ";
    cin >> pass;
    cout << "Es un usuario administrador ? 1-) Si , 2-) No :";
    cin >> isAdmin;

    string line;
    if (isAdmin == "1" ) {
        line = "admin " + idUser + " " + pass;
    } else {
        line = idUser + " " + pass;
    }

    string encrypt = xorCipher(line);

    ofstream usersFile("users.txt", ios::app); // append mode
    if (!usersFile) {
        cerr << "Error al acceder a archivo!" << endl;
        return;
    }

    usersFile.close();
    log("User added succesfully" + idUser);
    cout << "Usuario añadido correctamente";
};


// Codigo de desencriptamiento usando el cifrado XOR
// https://stackoverflow.com/questions/20365005/c-xor-encryption
string xorCipher(const string& input) {
    char key= 'N';
    string output = input;
    for (char& c: output) {
        c ^= key;
    }
    return output;
}

void xorEncrypt(const string& input) {
    ifstream in(input);
    ofstream out("users.txt");
    string line;
    while (getline(in, line)) {
        out << xorCipher(line) << endl;
    }
}

void log(const string& event) {
    ofstream logFile("log.txt", ios::app);
    if(!logFile) {
        cerr << "Error al abrir archivo" << endl;
        return;
    }

    time_t now = time(0);
    char* dt = ctime(&now);
    if (dt[strlen(dt) - 1] == '\n') {
        dt[strlen(dt) - 1] = '\0';
    }

    logFile << "[" << dt << "] " << event << endl;
}