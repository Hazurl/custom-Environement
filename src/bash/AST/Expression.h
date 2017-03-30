#ifndef __BASH_AST_EXPR__
#define __BASH_AST_EXPR__

#include "../Token.h"
#include "Value.h"
#include <string>

namespace bash {

class Expression : public Value {
public:
    Expression(Token* t);
    virtual ~Expression ();
    virtual std::string to_string();
    virtual void visit();

    Value* expr = nullptr;
};

}; // namespace bash

#endif