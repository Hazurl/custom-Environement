#ifndef __BASH_AST_IDENT__
#define __BASH_AST_IDENT__

#include "../Token.h"
#include "Value.h"
#include <string>

namespace bash {

class Ident : public Value {
public:
    Ident(Token* t = nullptr);
    virtual ~Ident ();

    virtual std::string to_string();
    virtual void visit();

    std::string name;
};

}; // namespace bash

#endif