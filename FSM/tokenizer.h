#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <list>
#include <map>

#include "../Token/factories.h"
#include "../Token/itoken.h"
#include "../Token/number.h"
#include "../Token/openparenthesis.h"
#include "../Token/closeparenthesis.h"
#include "../Token/Operation/operation.h"

namespace FSM
{
    using StrIter = std::string::const_iterator;
    using TokenIter = std::list<IToken*>::iterator;

    enum _Signal
    {
        number,
        negative,
        openParenthesis,
        closeParenthesis,
        operation,
        begin,
        end,
        maxSignals
    };


    int tokenizer(const std::string& str, std::list<IToken*>& tokens);



    namespace _Tokenizer
    {
        struct Context
        {
            _Signal& state;
            StrIter& strIter;
            std::list<IToken*>& tokens;
            std::string& digitsBuffer;
        };

        _Signal strIterToSignal(StrIter strIter);

        int changeState(Context& context, _Signal signal);
        int changeState(Context& context);

        void readNumber(Context& context);
        void fromNumberToOperation(Context& context);
        void fromNumberToOpenParenthesis(Context& context);
        void fromNumberToCloseParenthesis(Context& context);
        void readNegative(Context& context);
        void readOpenParenthesis(Context& context);
        void readCloseParenthesis(Context& context);
        void fromCloseParenthesisToNumber(Context& context);
        void fromCloseToOpen(Context& context);
        void empty(Context& context);
        void readOperation(Context& context);
        void error(Context& context);

        void commitNumber(Context& context);
    }
}

#endif // TOKENIZER_H
