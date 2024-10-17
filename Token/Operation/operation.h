#ifndef OPERATION_H
#define OPERATION_H

#include "../itoken.h"

class Operation : public IToken
{
protected:
    Operation() = default;
public:
    Type getType() const override;
};

#endif // OPERATION_H
