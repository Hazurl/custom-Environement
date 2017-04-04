#ifndef __BASH_AST_VALUE__
#define __BASH_AST_VALUE__

#include "../Token.h"
#include "AST.h"
#include <string>

namespace bash {

class Value : public AST {
public:
    Value(double v, Token* t = nullptr);
    virtual std::string to_string() = 0;
    virtual void visit(Context& ctx) = 0;
    double getValue(Context& ctx);

    double value = 0.0;
};

}; // namespace bash

#endif