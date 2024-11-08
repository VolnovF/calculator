#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <string>
#include <list>
#include <stack>

#include "FSM/tokenizer.h"
#include "FSM/infixtorpn.h"
#include "FSM/executerpn.h"

class Calculator
{
private:
    std::string _str;
    double _result;
    int _status;
public:
    Calculator(const std::string& str);
    double getResult();
    int getStatus();
private:
    void execute();
    void clear(std::list<IToken*>& list);
};

#endif // CALCULATOR_H
