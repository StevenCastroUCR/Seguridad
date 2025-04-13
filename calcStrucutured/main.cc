#include "Calculator.h"
#include "Users.h"

using namespace std;

int main(int argc, char* argv[])
{
    Calculator calc;
    Users user;
    bool isAdmin = false;

    if (!user.authentication(isAdmin))
    {
        return 1;
    }
    menu(isAdmin, calc, user);
    
    return 0;
}

void menu(bool isAdmin, Calculator calc, Users user)
{
    string option;
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

        option = user.readInput("Digite una opcion: ");

        if (isAdmin)
        {
            switch (stoi(option))
            {
            case 1:
                user.createUser();
                break;
            case 2:
                //textParser();
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
            switch (stoi(option))
            {
            case 1:
                //textParser();
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