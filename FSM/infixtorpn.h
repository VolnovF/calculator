#ifndef INFIXTORPN_H
#define INFIXTORPN_H

#include <list>
#include <stack>

#include "../Token/itoken.h"
#include "../Token/number.h"
#include "../Token/openparenthesis.h"
#include "../Token/closeparenthesis.h"
#include "../Token/Operation/operation.h"
#include "tokenizer.h"

namespace FSM
{
    using ListIter = std::list<IToken*>::const_iterator;

    int infixToRNP(const std::list<IToken*>& infix, std::list<IToken*>& rpn);

    namespace _RPN
    {
        struct Context
        {
            //_State& state;
            ListIter& infixIter;
            std::list<IToken*>& rpn;
            std::stack<IToken*>& buffer;
        };

        _Signal tokenIterToSignal(ListIter iter);

        int readToken(Context& context, _Signal signal);
        int readToken(Context& context);

        int readNumber(Context& context);
        int readOpenParenthesis(Context& context);
        int startCloseParenthesis(Context& context);
        int startOperation(Context& context);
        int rpnEnd(Context& context);
    }
}

#endif // INFIXTORPN_H
