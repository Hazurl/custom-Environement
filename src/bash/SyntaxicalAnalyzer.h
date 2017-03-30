#ifndef __BASH_SYNTAXICAL__
#define __BASH_SYNTAXICAL__

#include "../../lib/Logger/src/Logger.h"
#include "Token.h"
#include "AST/AST.h"
#include "AST/Value.h"
#include "AST/Expression.h"
#include "AST/BinOp.h"
#include "AST/Number.h"

#include <vector>
#include <string>

namespace bash {

class SyntaxicalAnalyzer {
public:
    SyntaxicalAnalyzer(TokenFlow& flow);
    ~SyntaxicalAnalyzer();

    AST* getAST();

private:
    TokenFlow& flow;
    AST* ast = nullptr;

    void parse();

    // EAT
    Expression* eatExpression();
    Value* eatFactor();
    Value* eatValue();
    Number* eatNumber();

};

}; // namespace bash

#endif