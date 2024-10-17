#ifndef POWER_H
#define POWER_H

#include <cmath>

#include "operation.h"

class Power : public Operation
{
public:
    Power() = default;

    int getPriority() const override;
    double execute(double leftOperand, double rightOperand) const override;
};

#endif // POWER_H
