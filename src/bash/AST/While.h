#ifndef __BASH_AST_WHILE__
#define __BASH_AST_WHILE__

#include "../Token.h"
#include "Instruction.h"
#include "Block.h"
#include "ValueNode.h"
#include <string>

using namespace haz;

namespace bash {

class While : public Instruction {
public:
    While(Token* t = nullptr);
    virtual ~While ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* cond = nullptr;
    Block* then = nullptr;
};

}; // namespace bash

#endif