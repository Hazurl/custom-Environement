#ifndef __BASH_AST_UNOP__
#define __BASH_AST_UNOP__

#include "../Token.h"
#include "Value.h"
#include <string>
#include <stdexcept>

namespace bash {

class UnOp : public Value {
public:
    UnOp(Token* t = nullptr);
    virtual ~UnOp ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    Value* v = nullptr;
};

}; // namespace bash

#endif