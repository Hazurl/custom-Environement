#ifndef __BASH_AST_BINOP__
#define __BASH_AST_BINOP__

#include "../Token.h"
#include "Value.h"
#include <string>
#include <stdexcept>

namespace bash {

class BinOp : public Value {
public:
    BinOp(Token* t = nullptr);
    virtual ~BinOp ();
    virtual std::string to_string();
    virtual void visit();

    Value* left = nullptr;
    Value* right = nullptr;
};

}; // namespace bash

#endif