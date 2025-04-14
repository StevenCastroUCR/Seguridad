#include "Domain/Entities/Controller.h"
#include "Domain/Entities/Calculator.h"
#include "Domain/Entities/Parser.h"
#include "Domain/Entities/Users.h"

int main() {
    Users users;
    Calculator calculator;
    Parser parser;

    Controller controller(&users, &parser, &calculator);
    return controller.run(); 
}
