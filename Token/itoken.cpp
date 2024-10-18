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
        {'.', number},
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

bool IToken::isNumber(char ch)
{
    return typeOfChar(ch) == number;
}

bool IToken::isOpenParenthesis(char ch)
{
    return typeOfChar(ch) == openParenthesis;
}

bool IToken::isCloseParenthesis(char ch)
{
    return typeOfChar(ch) == closeParenthesis;
}

bool IToken::isOperation(char ch)
{
    return typeOfChar(ch) == operation;
}





