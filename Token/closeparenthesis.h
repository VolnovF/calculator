#ifndef CLOSEPARENTHESIS_H
#define CLOSEPARENTHESIS_H

#include "itoken.h"

class CloseParenthesis : public IToken
{
public:
    CloseParenthesis() = default;

    Type getType() const;
};

#endif // CLOSEPARENTHESIS_H
