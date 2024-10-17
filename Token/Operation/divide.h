#ifndef DIVIDE_H
#define DIVIDE_H

#include "operation.h"

class Divide : public Operation
{
public:
    Divide() = default;

    int getPriority() const override;
    double execute(double leftOperand, double rightOperand) const override;
};

#endif // DIVIDE_H
