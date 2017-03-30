#ifndef __BASH_AST_NUMBER__
#define __BASH_AST_NUMBER__

#include "../Token.h"
#include "Value.h"
#include <string>

namespace bash {

class Number : public Value {
public:
    Number(double v, Token* t = nullptr);
    virtual ~Number ();
    virtual std::string to_string();
    virtual void visit();
};

}; // namespace bash

#endif