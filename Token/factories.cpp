#include "factories.h"

Operation *Factory::makeOperation(char ch)
{
    switch (ch) {
    case '+':
        return new Plus();
    case '-':
        return new Minus();
    case '*':
        return new Multiply();
    case '/':
        return new Divide();
    case '^':
        return new Power();
    default:
        return nullptr;
    }
}

IToken *Factory::makeOneLetterToken(char ch)
{
    switch (IToken::typeOfChar(ch)) {
    case IToken::operation:
        return makeOperation(ch);
    case IToken::openParenthesis:
        return new OpenParenthesis();
    case IToken::closeParenthesis:
        return new CloseParenthesis();
    default:
        return nullptr;
    }
}
