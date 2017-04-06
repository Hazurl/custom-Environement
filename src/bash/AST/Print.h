#ifndef __BASH_PRINT__
#define __BASH_PRINT__

#include "../Token.h"
#include "AST.h"
#include "Value.h"
#include "Instruction.h"
#include <string>

namespace bash {

class Print : public Instruction {
public:
    Print(Token* t = nullptr);
    virtual ~Print ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    Value* v = nullptr;
};

}; // namespace bash

#endif