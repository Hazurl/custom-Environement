#ifndef __BASH_AST_BINOP__
#define __BASH_AST_BINOP__

#include "../Token.h"
#include "ValueNode.h"
#include <string>
#include <stdexcept>

namespace bash {

class BinOp : public ValueNode {
public:
    BinOp(Token* t = nullptr);
    virtual ~BinOp ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* left = nullptr;
    ValueNode* right = nullptr;
};

}; // namespace bash

#endif