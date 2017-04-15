#ifndef __BASH_AST_IDENT__
#define __BASH_AST_IDENT__

#include "../Token.h"
#include "ValueNode.h"
#include <string>

namespace bash {

class Ident : public ValueNode {
public:
    Ident(Token* t = nullptr);
    virtual ~Ident ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);
    virtual void setValue(Context& ctx, Value v);

    std::string name;
};

}; // namespace bash

#endif