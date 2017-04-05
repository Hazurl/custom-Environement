#ifndef __BASH_AST_IF__
#define __BASH_AST_IF__

#include "../Token.h"
#include "Instruction.h"
#include "Block.h"
#include "Value.h"
#include <string>

namespace bash {

class If : public Instruction {
public:
    If(Token* t = nullptr);
    virtual ~If ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    Value* cond = nullptr;
    Block* then = nullptr;
    Block* elze = nullptr;
};

}; // namespace bash

#endif