#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    std::cout << "Calculadora texto" << std::endl;

    menu(authentication());

    return 0;
}

void menu(bool isAdmin){
    int option;
    while (true) {
        cout << "Laboratorio 01 de seguridad"<<endl;
        if (isAdmin) {
            cout << "1. Crear usuario" << endl;
            cout << "2. Calculadora de Texto" << endl;
            cout << "3. salir" << endl;
        } else {
            cout << "1. Calculadora de Texto" << endl;
            cout << "2. Salir" << endl;
        }

        cout << "Digite una opcion: ";
        cin >> option;
        
        if  (isAdmin) {
            switch (option) {
                case 1:
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

int textParser(){

    std::string input;

    std::string parsedInput;
    
    vector<int> operandsPositions;

    map<string, string> unidades ={

        {"uno", "1"},
        {"dos", "2"},
        {"tres", "3"},
        {"cuatro", "4"},
        {"cinco", "5"},
        {"seis", "6"},
        {"siete", "7"},
        {"ocho", "8"},
        {"nueve", "9"},
        {"diez", "10"}
    };
    
    map<string, string> especiales = {
        {"once", "11"},
        {"doce", "12"},
        {"trece", "13"},
        {"catorce", "14"},
        {"quince", "15"},
        {"dieciséis", "16"},
        {"diecisiete", "17"},
        {"dieciocho", "18"},
        {"diecinueve", "19"}
    };

    map<string, string> decenas = {
        {"veinte", "20"},
        {"veintiuno", "21"},
        {"veintidos", "22"},
        {"veintitres", "23"},
        {"veinticuatro", "24"},
        {"veinticinco", "25"},
        {"veintiseis", "26"},
        {"veintisiete", "27"},
        {"veintiocho", "28"},
        {"veintinueve", "29"},
        {"treinta", "30"},
        {"cuarenta", "40"},
        {"cincuenta", "50"},
        {"sesenta", "60"},
        {"setenta", "70"},
        {"ochenta", "80"},
        {"noventa", "90"}

    };



    
    std::cin >> input;
    size_t start = 0;

    string parsed;
    for (size_t i = 0; i < input.size(); i++)
    {
        char c= input[i];
        if (c == '+' || c == '-' || c == '*' || c == '/'){
            operandsPositions.push_back(i);
    }
   
    for (size_t i = 0; i < operandsPositions.size(); i++)
    {
         parsed += input.substr(start, operandsPositions[i]-start);
         parsed += input[operandsPositions[i]];
         parsed +=
    }
    
}
    cout<< parsed<< endl;

}

bool authentication() {
    string idUser;
    string password;
    cout << "Digite nombre usuario para continuar:" ;
    cin >> idUser;
    cout<< "Digite la contrasena:";
    cin >> password;

    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Error: No se encontro el archivo" << endl;
        return;
    }

    string line;
    bool match = false;
    bool isAdmin = false;

    while (getline(usersFile, line)) {
        istringstream iss(line);
        string admin, user, pass;
        iss >> admin;

        if (admin == "admin") {
            iss >> user >> pass;
            if((idUser == user && password == pass)) {
                match = true;
                isAdmin = true;
                break;
            }
        }
        else {
            user = admin;
            iss >> pass;

            if((idUser == user && password == pass)) {
                match = true;
                break;
            }
        }
    }

    if (match) {
        if (isAdmin)
            cout << "Cuenta Administrador ";
        cout << "Bienvenido!" << endl;
    } else {
        cout << "Error: usuario o contrasena invalidos" << endl;
    }
    return isAdmin;
};

