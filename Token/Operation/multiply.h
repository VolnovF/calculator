#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "operation.h"

class Multiply : public Operation
{
public:
    Multiply() = default;

    int getPriority() const override;
    double execute(double leftOperand, double rightOperand) const override;
};

#endif // MULTIPLY_H
