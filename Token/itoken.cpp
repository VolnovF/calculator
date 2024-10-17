#include "itoken.h"

int IToken::getPriority() const
{
    return 0;
}

double IToken::execute(double leftOperand, double rightOperand) const
{
    return 0;
}

double IToken::execute() const
{
    return 0;
}

IToken::Type IToken::typeOfChar(char ch)
{
    if(std::isdigit(ch))
        return number;

    static std::map<char, Type> typesMap{
        {'+', operation},
        {'-', operation},
        {'*', operation},
        {'/', operation},
        {'^', operation},
        {'(', openParenthesis},
        {')', closeParenthesis}
    };
    return (typesMap.count(ch)? typesMap.at(ch) : maxTypes);
}





