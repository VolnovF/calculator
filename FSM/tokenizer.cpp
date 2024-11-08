#include "tokenizer.h"



int FSM::tokenizer(const std::string &str, std::list<IToken*>& tokens)
{
    _Signal state{ begin };
    StrIter iter{ str.begin() };
    std::string digitsBuffer;
    _Tokenizer::Context context{state, iter, tokens, digitsBuffer};
    for (; iter < str.end(); iter++)
    {
        if(_Tokenizer::changeState(context))
            return 1;
    }
    return _Tokenizer::changeState(context, end);;
}

FSM::_Signal FSM::_Tokenizer::strIterToSignal(StrIter strIter)
{
    switch (IToken::typeOfChar(*strIter)) {
    case IToken::Type::number:
        return number;
    case IToken::Type::negative:
        return negative;
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

int FSM::_Tokenizer::changeState(Context& context)
{
    return changeState(context, strIterToSignal(context.strIter));
}


int FSM::_Tokenizer::changeState(Context& context, _Signal signal)
{
    static const std::map<std::pair<_Signal,_Signal>, void(*)(Context&)> tokenizerMap
    {
        {{begin, number}, readNumber},
        {{begin, openParenthesis}, readOpenParenthesis},
        {{begin, negative}, readNegative},
        {{negative, number}, readNumber},
        {{number, number}, readNumber},
        {{number, operation}, fromNumberToOperation},
        {{number, negative}, fromNumberToOperation},
        {{number, openParenthesis}, fromNumberToOpenParenthesis},
        {{number, closeParenthesis}, fromNumberToCloseParenthesis},
        {{number, end}, commitNumber},
        {{openParenthesis, negative}, readNegative},
        {{openParenthesis, number}, readNumber},
        {{openParenthesis, openParenthesis}, readOpenParenthesis},
        {{closeParenthesis, operation}, readOperation},
        {{closeParenthesis, negative}, readOperation},
        {{closeParenthesis, number}, fromCloseParenthesisToNumber},
        {{closeParenthesis, closeParenthesis}, readCloseParenthesis},
        {{closeParenthesis, openParenthesis}, fromCloseToOpen},
        {{closeParenthesis, end}, empty},
        {{operation, number}, readNumber},
        {{operation, openParenthesis}, readOpenParenthesis}
    };
    if(!tokenizerMap.count({context.state,signal}))
        return 1;
    tokenizerMap.at({context.state,signal})(context);
    return 0;
}

void FSM::_Tokenizer::readNumber(Context& context)
{
    context.digitsBuffer.push_back(*context.strIter);
    context.state = number;
}

void FSM::_Tokenizer::fromNumberToOperation(Context& context)
{
    commitNumber(context);
    context.tokens.push_back(Factory::makeOperation(*context.strIter));
    context.state = operation;
}

void FSM::_Tokenizer::fromNumberToOpenParenthesis(Context &context)
{
    commitNumber(context);
    context.tokens.push_back(new Multiply);
    context.tokens.push_back(new OpenParenthesis);
    context.state = openParenthesis;
}

void FSM::_Tokenizer::fromNumberToCloseParenthesis(Context &context)
{
    commitNumber(context);
    context.tokens.push_back(new CloseParenthesis);
    context.state = closeParenthesis;
}

void FSM::_Tokenizer::readNegative(Context& context)
{
    context.digitsBuffer.push_back(*context.strIter);
    context.state = negative;
}

void FSM::_Tokenizer::readOpenParenthesis(Context& context)
{
    context.tokens.push_back(new OpenParenthesis);
    context.state = openParenthesis;
}

void FSM::_Tokenizer::readOperation(Context& context)
{
    context.tokens.push_back(Factory::makeOperation(*context.strIter));
    context.state = operation;
}

void FSM::_Tokenizer::readCloseParenthesis(Context& context)
{
    context.tokens.push_back(new CloseParenthesis);
    context.state = closeParenthesis;
}

void FSM::_Tokenizer::fromCloseParenthesisToNumber(Context &context)
{
    context.tokens.push_back(new Multiply);
    readNumber(context);
}

void FSM::_Tokenizer::fromCloseToOpen(Context &context)
{
    context.tokens.push_back(new Multiply);
    readOpenParenthesis(context);
}

void FSM::_Tokenizer::empty(Context &context)
{}

void FSM::_Tokenizer::commitNumber(Context& context)
{
    context.tokens.push_back(new Number(std::stod(context.digitsBuffer)));
    context.digitsBuffer.clear();
}









