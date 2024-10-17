#ifndef NUMBER_H
#define NUMBER_H

#include "itoken.h"

class Number : public IToken
{
private:
    double _number;
public:
    Number(double number);

    Type getType() const override;
    double execute() const override;
};

#endif // NUMBER_H
