#include "Domain/Entities/Controller.h"
#include "Domain/Entities/Calculator.h"
#include "Domain/Entities/Parser.h"
#include "Domain/Entities/Users.h"
#include "Domain/Entities/Utility.h" 

int main() {
    Users users;
    Calculator calculator;
    Parser parser;
    Utility utility; 
    Controller controller(&users, &parser, &calculator,&utility);
    return controller.run(); 
}
