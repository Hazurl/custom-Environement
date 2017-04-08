#ifndef __BASH_AST_UNOP__
#define __BASH_AST_UNOP__

#include "../Token.h"
#include "ValueNode.h"
#include <string>
#include <stdexcept>

namespace bash {

class UnOp : public ValueNode {
public:
    UnOp(Token* t = nullptr);
    virtual ~UnOp ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* v = nullptr;
};

}; // namespace bash

#endif