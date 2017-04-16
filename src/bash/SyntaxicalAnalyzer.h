#ifndef __BASH_SYNTAXICAL__
#define __BASH_SYNTAXICAL__

#include "../../lib/Logger/src/Logger.h"
#include "Token.h"
#include "AST/AST.h"
#include "AST/Block.h"
#include "AST/Instruction.h"
#include "AST/FuncCall.h"
#include "AST/Assignment.h"
#include "AST/For.h"
#include "AST/While.h"
#include "AST/ValueNode.h"
#include "AST/ConstValueNode.h"
#include "AST/ArrayAccess.h"
#include "AST/If.h"
#include "AST/Expression.h"
#include "AST/BinOp.h"
#include "AST/UnOp.h"
#include "AST/Ident.h"
#include "AST/Primitive.h"
#include "AST/Array.h"

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
    Assignment* eatAssignment();
    If* eatIf();
    While* eatWhile();
    For* eatFor();

    Expression* eatExpression();
    ValueNode* eatOr();
    ValueNode* eatAnd();
    ValueNode* eatComp();
    ValueNode* eatAdd();
    ValueNode* eatMul();
    ValueNode* eatValueNode();

    Ident* eatIdent();
    Primitive* eatNumber();
    Primitive* eatString();
    Array* eatArray();
    FuncCall* eatFuncCall();
    Primitive* eatPrimitive();
    ArrayAccess* eatArrayAccess(ValueNode* var = nullptr);
};

}; // namespace bash

#endif