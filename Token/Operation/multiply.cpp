#include "multiply.h"

int Multiply::getPriority() const
{
    return 2;
}

double Multiply::execute(double leftOperand, double rightOperand) const
{
    return leftOperand * rightOperand;
}
