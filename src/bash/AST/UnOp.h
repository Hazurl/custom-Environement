#ifndef __BASH_AST_UNOP__
#define __BASH_AST_UNOP__

#include "../Token.h"
#include "ConstValueNode.h"
#include <string>
#include <stdexcept>

using namespace haz;

namespace bash {

class UnOp : public ConstValueNode {
public:
    enum class Op {
        MIN, NOT
    };

    UnOp(Op mode, Token* t = nullptr);
    virtual ~UnOp ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* v = nullptr;
    Op mode;
};

}; // namespace bash

#endif