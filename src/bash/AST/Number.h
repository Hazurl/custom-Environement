#ifndef __BASH_AST_NUMBER__
#define __BASH_AST_NUMBER__

#include "../Token.h"
#include "ValueNode.h"
#include <string>

namespace bash {

class Number : public ValueNode {
public:
    Number(double v, Token* t = nullptr);
    virtual ~Number ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);
};

}; // namespace bash

#endif