#ifndef __BASH_AST__
#define __BASH_AST__

#include "../Token.h"
#include "ValueNode.h"
#include <string>

namespace bash {

class ArrayAccess : public ValueNode {
public:
    ArrayAccess (Token* t = nullptr);
    virtual ~ArrayAccess ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* var = nullptr;
};

}; // namespace bash

#endif