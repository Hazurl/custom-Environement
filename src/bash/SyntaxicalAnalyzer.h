#ifndef __BASH_SYNTAXICAL__
#define __BASH_SYNTAXICAL__

#include "../../lib/Logger/src/Logger.h"
#include "Token.h"
#include "AST/AST.h"
#include "AST/Instruction.h"
#include "AST/If.h"
#include "AST/For.h"
#include "AST/While.h"
#include "AST/Value.h"
#include "AST/Expression.h"
#include "AST/BinOp.h"
#include "AST/UnOp.h"
#include "AST/Ident.h"
#include "AST/Number.h"

#include <vector>
#include <string>

namespace bash {

class SyntaxicalAnalyzer {
public:
    SyntaxicalAnalyzer(TokenFlow& flow);
    ~SyntaxicalAnalyzer();

    Instruction* getAST();

private:
    TokenFlow& flow;
    Instruction* ast = nullptr;

    void parse();

    // EAT
    Instruction* eatInstruction();
    Expression* eatExpression();
    Value* eatFactor();
    Value* eatValue();
    Number* eatNumber();

};

}; // namespace bash

#endif