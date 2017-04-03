#ifndef __BASH_AST_WHILE__
#define __BASH_AST_WHILE__

#include "../Token.h"
#include "Instruction.h"
#include "Value.h"
#include <string>

namespace bash {

class While : public Instruction {
public:
    While(Token* t = nullptr);
    virtual ~While ();

    virtual std::string to_string();
    virtual void visit();

    Value* cond = nullptr;
    std::vector<Instruction*> block;
};

}; // namespace bash

#endif