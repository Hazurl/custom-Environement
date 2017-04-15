#ifndef __BASH_AST_PRIMITIVE__
#define __BASH_AST_PRIMITIVE__

#include "../Token.h"
#include "ConstValueNode.h"
#include <string>

namespace bash {

class Primitive : public ConstValueNode {
public:
    Primitive(Value v, Token* t = nullptr);
    virtual ~Primitive ();
    virtual std::string to_string();
    virtual void visit(Context& ctx);
};

}; // namespace bash

#endif