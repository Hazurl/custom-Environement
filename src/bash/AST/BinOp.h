#ifndef __BASH_AST_BINOP__
#define __BASH_AST_BINOP__

#include "../Token.h"
#include "ConstValueNode.h"
#include <string>
#include <stdexcept>

namespace bash {

class BinOp : public ConstValueNode {
public:
    enum class Op {
        AND, OR,
        NEQ, EQ, GT_EQ, GT, LT, LT_EQ,
        ADD, SUB,
        MUL, DIV
    };

    BinOp(Op mode, Token* t = nullptr);
    virtual ~BinOp ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* left = nullptr;
    ValueNode* right = nullptr;
    Op mode;
};

}; // namespace bash

#endif