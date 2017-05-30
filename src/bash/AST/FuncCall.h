#ifndef __BASH_FUNC_CALL__
#define __BASH_FUNC_CALL__

#include "../Token.h"
#include "Ident.h"
#include "Instruction.h"
#include <string>

using namespace haz;

namespace bash {

class FuncCall : public Instruction {
public:
    FuncCall(Token* t = nullptr);
    virtual ~FuncCall ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    Ident* func = nullptr;
    std::vector<ValueNode*> args;
};

}; // namespace bash

#endif