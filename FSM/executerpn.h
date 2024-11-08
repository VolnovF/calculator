#ifndef EXECUTERPN_H
#define EXECUTERPN_H

#include <string>
#include <stack>
#include <list>
#include <map>

#include "../Token/itoken.h"
#include "tokenizer.h"
#include "infixtorpn.h"

namespace FSM
{
    int executeRPN(std::list<IToken*>& rpn, double& result);

    namespace _execute
    {
        struct Context
        {
            ListIter& iter;
            double& result;
            std::stack<double>& buffer;
        };

        int readToken(Context& context, _Signal signal);
        int readToken(Context& context);

        int readNumber(Context& context);
        int executeOperation(Context& context);
        int checkBuffer(Context& context);
    }
}
#endif // EXECUTERPN_H
