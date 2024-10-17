#include "plus.h"

int Plus::getPriority() const
{
    return 1;
}

double Plus::execute(double leftOperand, double rightOperand) const
{
    return leftOperand + rightOperand;
}
