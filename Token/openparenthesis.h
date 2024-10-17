#ifndef OPENPARENTHESIS_H
#define OPENPARENTHESIS_H

#include "itoken.h"

class OpenParenthesis : public IToken
{
public:
    OpenParenthesis() = default;

    Type getType() const override;
};

#endif // OPENPARENTHESIS_H
