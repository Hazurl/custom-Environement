#ifndef __BASH_AST_IF__
#define __BASH_AST_IF__

#include "../Token.h"
#include "Instruction.h"
#include "Value.h"
#include <string>

namespace bash {

class If : public Instruction {
public:
    If(Token* t = nullptr);
    virtual ~If ();

    virtual std::string to_string();
    virtual void visit();

    Value* cond;
    std::vector<Instruction*> thenBlock;
    std::vector<Instruction*> elseBlock;
};

}; // namespace bash

#endif