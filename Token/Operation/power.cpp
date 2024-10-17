#include "power.h"

int Power::getPriority() const
{
    return 3;
}

double Power::execute(double leftOperand, double rightOperand) const
{
    return std::pow(leftOperand, rightOperand);
}
