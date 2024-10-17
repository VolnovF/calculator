#ifndef MINUS_H
#define MINUS_H

#include "operation.h"

class Minus : public Operation
{
public:
    Minus() = default;

    int getPriority() const override;
    double execute(double leftOperand, double rightOperand) const override;
};

#endif // MINUS_H
