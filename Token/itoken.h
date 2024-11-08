#ifndef ITOKEN_H
#define ITOKEN_H

#include <cctype>
#include <map>

class IToken
{
protected:
    IToken() = default;
public:
    enum Type{
        number,
        negative,
        operation,
        openParenthesis,
        closeParenthesis,
        //function,
        maxTypes
    };

    virtual Type getType() const = 0;
    virtual int getPriority() const;
    virtual double execute(double leftOperand, double rightOperand) const;
    virtual double execute() const;
    //virtual double execute(double operand) const;

    virtual ~IToken() {}
public:
    static Type typeOfChar(char ch);
    static bool isNumber(char ch);
    static bool isOpenParenthesis(char ch);
    static bool isCloseParenthesis(char ch);
    static bool isNegative(char ch);
    static bool isOperation(char ch);
};

#endif // ITOKEN_H
