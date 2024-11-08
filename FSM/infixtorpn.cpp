#include "infixtorpn.h"

FSM::_Signal FSM::_RPN::tokenIterToSignal(ListIter iter)
{
    switch ((*iter)->getType()) {
    case IToken::Type::number:
        return number;
    case IToken::Type::openParenthesis:
        return openParenthesis;
    case IToken::Type::closeParenthesis:
        return closeParenthesis;
    case IToken::Type::operation:
        return operation;
    default:
        return maxSignals;
    }
}

int FSM::infixToRNP(const std::list<IToken *> &infix, std::list<IToken *> &rpn)
{
    std::stack<IToken*> buffer;
    ListIter iter{ infix.begin() };
    _RPN::Context context{iter, rpn, buffer};
    for (;iter != infix.end(); iter++)
    {
        if(_RPN::readToken(context))
            return 1;
    }
    return _RPN::readToken(context, end);
}

int FSM::_RPN::readToken(Context &context)
{
    return readToken(context, tokenIterToSignal(context.infixIter));
}

int FSM::_RPN::readToken(Context &context, _Signal signal)
{
    static const std::map<_Signal, int(*)(Context&)> mapInfixToRPN
    {
        {number, readNumber},
        {openParenthesis, readOpenParenthesis},
        {closeParenthesis, startCloseParenthesis},
        {operation, startOperation},
        {end, rpnEnd},
    };
    if(!mapInfixToRPN.count(signal))
        return 1;
    mapInfixToRPN.at(signal)(context);
    return 0;
}

int FSM::_RPN::readNumber(Context& context)
{
    context.rpn.push_back(*context.infixIter);
    return 0;
}

int FSM::_RPN::readOpenParenthesis(Context& context)
{
    context.buffer.push(*context.infixIter);
    return 0;
}

int FSM::_RPN::startCloseParenthesis(Context& context)
{
    while (!context.buffer.empty())
    {
        if (context.buffer.top()->getType() == IToken::openParenthesis)
        {
            context.buffer.pop();
            return 0;
        }
        else
        {
            context.rpn.push_back(context.buffer.top());
            context.buffer.pop();
        }
    }
    return 1;
}

int FSM::_RPN::startOperation(Context& context)
{
    while (!context.buffer.empty())
    {
        if(context.buffer.top()->getPriority() >= (*context.infixIter)->getPriority())
        {
            context.rpn.push_back(context.buffer.top());
            context.buffer.pop();
        }
        else
            break;
    }
    context.buffer.push(*context.infixIter);
    return 0;
}

int FSM::_RPN::rpnEnd(Context& context)
{
    while (!context.buffer.empty())
    {
        if(context.buffer.top()->getType() == IToken::operation)
        {
            context.rpn.push_back(context.buffer.top());
            context.buffer.pop();
        }
        else
        {
            return 1;
        }
    }
    return 0;
}



