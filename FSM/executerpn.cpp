#include "executerpn.h"


int FSM::executeRPN(std::list<IToken *>& rpn, double &result)
{
    std::stack<double> buffer;
    ListIter iter{ rpn.begin() };
    _execute::Context context{iter, result, buffer};
    for (;iter != rpn.end(); iter++)
    {
        if(_execute::readToken(context))
            return 1;
    }
    return _execute::readToken(context, end);;
}

int FSM::_execute::readToken(Context &context)
{
    return readToken(context, _RPN::tokenIterToSignal(context.iter));
}

int FSM::_execute::readToken(Context &context, _Signal signal)
{
    static const std::map<_Signal, int(*)(Context&)> executeMap
    {
        {number, readNumber},
        {operation, executeOperation},
        {end, checkBuffer},
    };
    if(!executeMap.count(signal))
        return 1;
    executeMap.at(signal)(context);
    return 0;
}

int FSM::_execute::readNumber(Context &context)
{
    context.buffer.push((*context.iter)->execute());
    return 0;
}

int FSM::_execute::executeOperation(Context &context)
{
    if(context.buffer.size() < 2)
        return 1;
    double rightOperand = context.buffer.top();
    context.buffer.pop();
    double leftOperand = context.buffer.top();
    context.buffer.pop();
    context.buffer.push( (*context.iter)->execute(leftOperand, rightOperand) );
    return 0;
}

int FSM::_execute::checkBuffer(Context &context)
{
    context.result = context.buffer.top();
    return context.buffer.size() == 1;
}
