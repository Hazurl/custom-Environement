#ifndef __BASH_AST_FOR__
#define __BASH_AST_FOR__

#include "../Token.h"
#include "Block.h"
#include "Instruction.h"
#include "Ident.h"
#include <string>

namespace bash {

class For : public Instruction {
public:
    For(Token* t = nullptr);
    virtual ~For ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    Ident* var = nullptr;
    ValueNode* from = nullptr;
    ValueNode* to = nullptr;
    ValueNode* step = nullptr;
    Block* then = nullptr;
};

}; // namespace bash

#endif