#ifndef __BASH_AST_FOR__
#define __BASH_AST_FOR__

#include "../Token.h"
#include "Instruction.h"
#include "Ident.h"
#include "Number.h"
#include <string>

namespace bash {

class For : public Instruction {
public:
    For(Token* t = nullptr);
    virtual ~For ();

    virtual std::string to_string();
    virtual void visit();

    Ident* var = nullptr;
    Number* from = nullptr;
    Number* to = nullptr;
    Number* step = nullptr;
    std::vector<Instruction*> block;
};

}; // namespace bash

#endif