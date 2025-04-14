#include "Controller.h"
#include "../Entities/Users.h"
#include <iostream>

void menu(bool isAdmin, Users user);

int Controller::run() {
    Users user;
    bool isAdmin = false;

    if (!user.authentication(isAdmin)) {
        return 1;
    }

    menu(isAdmin, user);
    return 0;
}

void menu(bool isAdmin, Users user) {
    std::string option;
    while (true) {
        std::cout << "Laboratorio 01 de seguridad\nCalculadora texto\n\n";

        if (isAdmin) {
            std::cout << "1. Crear usuario\n2. Calcular de Texto\n3. Salir\n";
        } else {
            std::cout << "1. Calcular de Texto\n2. Salir\n";
        }

        option = user.readInput("Digite una opcion: ");

        try {
            int op = std::stoi(option);
            if (isAdmin) {
                switch (op) {
                    case 1:
                        user.createUser();
                        break;
                    case 2:
                        textParser();
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
                        textParser();
                        break;
                    case 2:
                        return;
                    default:
                        std::cout << "Opcion invalida\n";
                        break;
                }
            }
        } catch (...) {
            std::cout << "Entrada no válida, intente de nuevo.\n";
        }
    }
}
