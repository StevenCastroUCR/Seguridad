#include "Controller.h"
#include <iostream>


Controller::Controller(IUsers* user, IParser* parser, ICalculator* calculator, IUtility* utility)
    : user(user), parser(parser), calculator(calculator), utility(utility) {}
   


int Controller::run() {
    bool isAdmin = false;

    if (!user->authentication(isAdmin)) {
        return 1;
    }

    Menu(isAdmin);
    return 0;
}

void Controller:: Menu(bool isAdmin) {
    std::string option;
    while (true) {
        std::cout << "Laboratorio 01 de seguridad\nCalculadora texto\n\n";

        if (isAdmin) {
            std::cout << "1. Crear usuario\n2. Calcular de Texto\n3. Salir\n";
        } else {
            std::cout << "1. Calcular de Texto\n2. Salir\n";
        }

        option = utility->readInput("Digite una opcion: ");

        try {
            int op = std::stoi(option);
            if (isAdmin) {
                switch (op) {
                    case 1:
                        user->createUser();
                        break;
                    case 2:
                    this->parser->textParser();

                        break;
                    case 3:
                        return;
                    default:
                        std::cout << "Opcion invalida\n";
                        break;
                }
            } else {
                switch (op) {
                    case 1:
                        this->parser->textParser();
                        break;
                    case 2:
                        return;
                    default:
                        std::cout << "Opcion invalida\n";
                        break;
                }
            }
        } catch (...) {
            std::cout << "Entrada no valida, intente de nuevo.\n";
        }
    }
}
