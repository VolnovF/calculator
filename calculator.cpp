#include "calculator.h"

Calculator::Signal Calculator::getSignal(StrIter &iter)
{
    if (iter >= _str.end())
        return end;
    if (IToken::isNumber(*iter))
        return number;
    if (*iter == '-')
        return minus;
    if (IToken::isOpenParenthesis(*iter))
        return openParenthesis;
    if (IToken::isCloseParenthesis(*iter))
        return closeParenthesis;
    if (IToken::isOperation(*iter))
        return operation;
    return end;
}

void Calculator::start(StrIter &iter)
{
    static void(Calculator::*script[maxSignals])(StrIter&)
    {
        &Calculator::readNumber,
        &Calculator::readNegative,
        &Calculator::readOpenParenthesis,
        &Calculator::error,
        &Calculator::error,
        &Calculator::error
    };
    _tokenizerState = script[getSignal(iter)];
}

void Calculator::readNumber(StrIter& iter)
{
    static void(Calculator::*script[maxSignals])(StrIter&)
    {
        &Calculator::readNumber,
        &Calculator::readOperation,
        &Calculator::readOperation,
        &Calculator::readCloseParenthesis,
        &Calculator::readOperation,
        &Calculator::error
    };

    while (IToken::isNumber(*iter))
    {
        _digitsBuffer.push_back(*iter);
        iter++;
        if(iter >= _str.end())
            break;
    }
    _listTokens.push_back(new Number(std::stod(_digitsBuffer)));
    _digitsBuffer.clear();
    _tokenizerState = script[getSignal(iter)];
}

void Calculator::readNegative(StrIter &iter)
{
    _digitsBuffer.push_back(*iter);
    iter++;
    _tokenizerState = &Calculator::readNumber;
}

void Calculator::readOpenParenthesis(StrIter &iter)
{
    static void(Calculator::*script[maxSignals])(StrIter&)
    {
        &Calculator::readNumber,
        &Calculator::readNegative,
        &Calculator::readOpenParenthesis,
        &Calculator::readCloseParenthesis,
        &Calculator::error,
        &Calculator::error
    };
    _listTokens.push_back(new OpenParenthesis);
    iter++;
    _tokenizerState = script[getSignal(iter)];
}

void Calculator::readCloseParenthesis(StrIter &iter)
{
    static void(Calculator::*script[maxSignals])(StrIter&)
    {
        &Calculator::readNumber,
        &Calculator::readOperation,
        &Calculator::readOperation,
        &Calculator::readCloseParenthesis,
        &Calculator::readOperation,
        &Calculator::error
    };
    _listTokens.push_back(new CloseParenthesis);
    iter++;
    _tokenizerState = script[getSignal(iter)];
}

void Calculator::readOperation(StrIter &iter)
{
    static void(Calculator::*script[maxSignals])(StrIter&)
    {
        &Calculator::readNumber,
        &Calculator::error,
        &Calculator::readOpenParenthesis,
        &Calculator::error,
        &Calculator::error,
        &Calculator::error
    };
    if(*iter == '(')
    {
        _listTokens.push_back(new Multiply);
        _tokenizerState = &Calculator::readOpenParenthesis;
        return;
    }
    _listTokens.push_back(Factory::makeOperation(*iter));
    iter++;
    _tokenizerState = script[getSignal(iter)];
}

void Calculator::error(StrIter &iter)
{
    iter = _str.end();
    ;
}

void Calculator::rpn(TokenIter &iter)
{
    static void(Calculator::*script[IToken::Type::maxTypes])(TokenIter&)
    {
        &Calculator::rpnNumber,
        &Calculator::rpnOperation,
        &Calculator::rpnOpenParenthesis,
        &Calculator::rpnCloseParenthesis
    };
    _rpnState = script[(*iter)->getType()];
}

void Calculator::rpnNumber(TokenIter &iter)
{
    _rpnTokens.push_back(*iter);
    iter++;
    _rpnState = &Calculator::rpn;
}

void Calculator::rpnOpenParenthesis(TokenIter &iter)
{
    _tokensBuffer.push(*iter);
    iter++;
    _rpnState = &Calculator::rpn;
}

void Calculator::rpnCloseParenthesis(TokenIter &iter)
{
    while (!_tokensBuffer.empty())
    {
        if (_tokensBuffer.top()->getType() == IToken::openParenthesis)
        {
            _tokensBuffer.pop();
            break;
        }
        else
        {
            _rpnTokens.push_back(_tokensBuffer.top());
            _tokensBuffer.pop();
        }
    }
    iter++;
    _rpnState = &Calculator::rpn;
}

void Calculator::rpnOperation(TokenIter &iter)
{
    while (!_tokensBuffer.empty())
    {
        if(_tokensBuffer.top()->getPriority() >= (*iter)->getPriority())
        {
            _rpnTokens.push_back(_tokensBuffer.top());
            _tokensBuffer.pop();
        }
        else
            break;
    }
    _tokensBuffer.push(*iter);
    iter++;
    _rpnState = &Calculator::rpn;
}

void Calculator::rpnEnd(TokenIter &iter)
{
    while (!_tokensBuffer.empty())
    {
        if(_tokensBuffer.top()->getType() == IToken::operation)
        {
            _rpnTokens.push_back(_tokensBuffer.top());
            _tokensBuffer.pop();
        }
        else
        {
            ;
        }
    }
}

void Calculator::rpnErr(TokenIter &iter)
{
    iter = _listTokens.end();
}

void Calculator::execute(TokenIter &iter)
{
    switch ((*iter)->getType()) {
    case IToken::number:
        _rpnState = &Calculator::executeNumber;
        return;
    case IToken::operation:
        _rpnState = &Calculator::executeOperation;
        return;
    default:
        break;
    }
}

void Calculator::executeNumber(TokenIter &iter)
{
    _numbersBuffer.push((*iter)->execute());
    iter++;
    _rpnState = &Calculator::execute;
}

void Calculator::executeOperation(TokenIter &iter)
{
    if( _numbersBuffer.size() >= 2 )
    {
        double rightOperand = _numbersBuffer.top();
        _numbersBuffer.pop();
        double leftOperand = _numbersBuffer.top();
        _numbersBuffer.pop();
        _numbersBuffer.push((*iter)->execute(leftOperand, rightOperand));

    }
    else
    {
        ;
    }
    iter++;
    _rpnState = &Calculator::execute;
}

Calculator::Calculator(const std::string &str)
    : _str{str}
{}

QString Calculator::getResult()
{
    _tokenizerState = &Calculator::start;
    for (auto iter = _str.begin(); iter < _str.end();)
    {
        (*this.*_tokenizerState)(iter);
    };

    _rpnState = &Calculator::rpn;
    auto iter = _listTokens.begin();
    for (;iter != _listTokens.end();)
    {
        (*this.*_rpnState)(iter);
    };
    _rpnState = &Calculator::rpnEnd;
    (*this.*_rpnState)(iter);

    _rpnState = &Calculator::execute;
    iter = _rpnTokens.begin();
    for (;iter != _rpnTokens.end();)
    {
        (*this.*_rpnState)(iter);
    };
    if( _numbersBuffer.size() == 1 )
    {
        return QString::number(_numbersBuffer.top());
    }
    else
    {
        return "Ошибка арифметики";
    }
}
