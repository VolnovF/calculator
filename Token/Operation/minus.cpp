#include "minus.h"

int Minus::getPriority() const
{
    return 1;
}

double Minus::execute(double leftOperand, double rightOperand) const
{
    return leftOperand - rightOperand;
}
