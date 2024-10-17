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
        break;
    }
}
