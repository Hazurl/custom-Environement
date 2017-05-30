#ifndef __BASH_AST_INSTR__
#define __BASH_AST_INSTR__

#include "../Token.h"
#include "AST.h"
#include <string>

using namespace haz;

namespace bash {

class Instruction : public AST {
public:
    Instruction(Token* t = nullptr);
    virtual ~Instruction ();
};

}; // namespace bash

#endif