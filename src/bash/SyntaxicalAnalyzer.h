#ifndef __BASH_SYNTAXICAL__
#define __BASH_SYNTAXICAL__

#include "../../lib/Logger/src/Logger.h"
#include "Token.h"
#include "AST/AST.h"
#include "AST/Block.h"
#include "AST/Instruction.h"
#include "AST/Print.h"
#include "AST/Assignment.h"
#include "AST/For.h"
#include "AST/While.h"
#include "AST/Value.h"
#include "AST/If.h"
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

    Block* getAST();

private:
    TokenFlow& flow;
    Block* mainBlock = nullptr;

    void parse();

    // EAT
    Instruction* eatInstruction();
    Expression* eatExpression();
    Assignment* eatAssignment();
    If* eatIf();
    While* eatWhile();
    For* eatFor();
    Value* eatFactor();
    Value* eatValue();
    Value* eatNumber();
    Print* eatPrint();

};

}; // namespace bash

#endif