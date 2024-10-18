#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <functional>
#include <QString>
#include <string>
#include <list>
#include <stack>

#include "Token/factories.h"
#include "Token/itoken.h"
#include "Token/number.h"
#include "Token/openparenthesis.h"
#include "Token/closeparenthesis.h"
#include "Token/Operation/operation.h"

using StrIter = std::string::iterator;
using TokenIter = std::list<IToken*>::iterator;

class Calculator
{
private:
    enum Signal
    {
        number,
        minus,
        openParenthesis,
        closeParenthesis,
        operation,
        end,
        maxSignals
    };
    std::string _str;
    std::list<IToken*> _listTokens;
    std::list<IToken*> _rpnTokens;

    void(Calculator::*_tokenizerState)(StrIter&);
    void(Calculator::*_rpnState)(TokenIter&);

    std::string _digitsBuffer;
    std::stack<IToken*> _tokensBuffer;
    std::stack<double> _numbersBuffer;

    Signal getSignal(StrIter& iter);
    void start(StrIter& iter);
    void readNumber(StrIter& iter);
    void readNegative(StrIter& iter);
    void readOpenParenthesis(StrIter& iter);
    void readCloseParenthesis(StrIter& iter);
    void readOperation(StrIter& iter);
    void error(StrIter& iter);
    void error(TokenIter& iter);

    void rpn(TokenIter& iter);
    void rpnNumber(TokenIter& iter);
    void rpnOpenParenthesis(TokenIter& iter);
    void rpnCloseParenthesis(TokenIter& iter);
    void rpnOperation(TokenIter& iter);
    void rpnEnd(TokenIter& iter);
    void rpnErr(TokenIter& iter);

    void execute(TokenIter& iter);
    void executeNumber(TokenIter& iter);
    void executeOperation(TokenIter& iter);
public:
    Calculator(const std::string& str);
    QString getResult();
};

#endif // CALCULATOR_H
