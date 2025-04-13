#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "ICalculator.h"
#include <string>
#include <vector>

class Calculator :public ICalculator {
public:
    

private:
   
  
    int evalPostfix(const std::vector<std::string>& postfix);


};

#endif // CALCULATOR_H
