#include "Controller.h"
#include <iostream>


Controller::Controller(IUsers* user, IParser* parser, ICalculator* calculator, IUtility* utility)
    : user(user), parser(parser), calculator(calculator), utility(utility) {}
   

/// @brief Ejecuta el programa principal del controlador. Realiza la autenticacion del usuario
///        y posteriormente despliega el menu principal segun el tipo de usuario (administrador o regular).
/// @return Retorna 0 si el programa se ejecuta correctamente, 1 si falla la autenticacion.
int Controller::run() {
    bool isAdmin = false;

    while (true) {
        if (!user->authentication(isAdmin)) {
            return 1;
        }

        Menu(isAdmin);
    }
    return 0;
}

/// @brief Muestra el menu principal del sistema dependiendo del tipo de usuario.
///        Si el usuario es administrador, se habilita la opcion de crear nuevos usuarios.
/// @param isAdmin Valor booleano que indica si el usuario autenticado tiene privilegios de administrador.
void Controller:: Menu(bool isAdmin) {
    std::string option;
    while (true) {
        std::cout << "Laboratorio 01 de seguridad\nCalculadora texto\n\n";

        if (isAdmin) {
            std::cout << "1. Crear usuario\n2. Calcular de Texto\n3. Cerrar Sesion\n4. Salir\n";
        } else {
            std::cout << "1. Calcular de Texto\n2. Cerrar Sesion\n3. Salir\n";
        }

        option = utility->readInput("Digite una opcion: ", 1);

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
                        std::cout << "Cerrando Sesion.\n";
                        return;
                    case 4:
                        exit(0);
                    default:
                        std::cout << "Opcion invalida\n";
                        continue;
                }
            } else {
                switch (op) {
                    case 1:
                        this->parser->textParser();
                        break;
                    case 2:
                        std::cout << "Cerrando Sesion.\n";
                        return;
                    case 3:
                        exit(0);
                    default:
                        std::cout << "Opcion invalida\n";
                        continue;
                }
            }
        } catch (...) {
            std::cout << "Entrada no valida, intente de nuevo.\n";
        }
    }
}
