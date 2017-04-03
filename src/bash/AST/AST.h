#ifndef __BASH_AST__
#define __BASH_AST__

#include "../Token.h"
#include <string>

namespace bash {

class AST {
public:
    AST (Token* t = nullptr);
    virtual ~AST ();
    virtual std::string to_string() = 0;
    virtual void visit() = 0;

    Token* token = nullptr;
};

}; // namespace bash

#endif