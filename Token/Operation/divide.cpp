#include "divide.h"

int Divide::getPriority() const
{
    return 2;
}

double Divide::execute(double leftOperand, double rightOperand) const
{
    return leftOperand / rightOperand;
}
