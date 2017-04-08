#ifndef __BASH_AST_EXPR__
#define __BASH_AST_EXPR__

#include "../Token.h"
#include "ValueNode.h"
#include <string>

namespace bash {

class Expression : public ValueNode {
public:
    Expression(Token* t = nullptr);
    virtual ~Expression ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* expr = nullptr;
};

}; // namespace bash

#endif