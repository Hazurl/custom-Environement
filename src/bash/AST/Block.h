#ifndef __BASH_AST_BLOCK__
#define __BASH_AST_BLOCK__

#include "../Token.h"
#include "AST.h"
#include "Instruction.h"
#include <string>
#include <vector>

namespace bash {

class Block : public AST {
public:
    Block(Token* t = nullptr);
    virtual ~Block ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    void push(Instruction* i);

private:
    std::vector<Instruction*> instr;
};

}; // namespace bash

#endif