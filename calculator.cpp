#include "calculator.h"


Calculator::Calculator(const std::string &str)
    : _str{str}, _status{0}
{
    execute();
}

double Calculator::getResult()
{
    return _result;
}

int Calculator::getStatus()
{
    return _status;
}

void Calculator::execute()
{
    std::list<IToken*> infix;
    _status = FSM::tokenizer(_str, infix);
    if(_status)
    {
        return clear(infix);
    }
    std::list<IToken*> rpn;
    _status = FSM::infixToRNP(infix, rpn);
    if(_status)
    {
        return clear(infix);
    }
    _status = FSM::executeRPN(rpn, _result);
    if(_status)
    {
        return clear(infix);
    }
}

void Calculator::clear(std::list<IToken*>& list)
{
    for(auto iter = list.begin(); iter != list.end(); iter++)
    {
        delete (*iter);
    }
}
