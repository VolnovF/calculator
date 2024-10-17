#ifndef PLUS_H
#define PLUS_H

#include "operation.h"

class Plus : public Operation
{
public:
    Plus() = default;

    int getPriority() const override;
    double execute(double leftOperand, double rightOperand) const override;
};

#endif // PLUS_H
