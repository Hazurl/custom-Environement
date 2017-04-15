#ifndef __BASH_AST_ASSIGN__
#define __BASH_AST_ASSIGN__

#include "../Token.h"
#include "Instruction.h"
#include "Expression.h"
#include "Ident.h"
#include "ValueNode.h"
#include <string>

namespace bash {

class Assignment : public Instruction {
public:
    Assignment(Token* t = nullptr);
    virtual ~Assignment ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);

    ValueNode* var = nullptr;
    Expression* expr = nullptr;
};

}; // namespace bash

#endif