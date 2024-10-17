#include "number.h"

Number::Number(double number)
    : _number{number}
{}

IToken::Type Number::getType() const
{
    return number;
}

double Number::execute() const
{
    return _number;
}
