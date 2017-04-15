#ifndef __BASH_AST_VALUE__
#define __BASH_AST_VALUE__

#include "../Token.h"
#include "AST.h"
#include "../Value.h"
#include <string>

namespace bash {

class ValueNode : public AST {
public:
    ValueNode(Value v, Token* t = nullptr);
    virtual ~ValueNode();
    virtual std::string to_string() = 0;
    virtual void visit(Context& ctx) = 0;
    Value getValue(Context& ctx);
    virtual void setValue(Context& ctx, Value v) = 0;

    Value value;
};

}; // namespace bash

#endif