#include "SyntaxicalAnalyzer.h"

using namespace bash;

SyntaxicalAnalyzer::SyntaxicalAnalyzer(TokenFlow& flow) : flow(flow) {
    parse();
}

SyntaxicalAnalyzer::~SyntaxicalAnalyzer() {
    if (ast)
        delete ast;
}

void SyntaxicalAnalyzer::parse() {
    ast = eatExpression();
}

Expression* SyntaxicalAnalyzer::eatExpression() {
    auto e = new Expression(flow.eat());
    e->expr = new Number(flow.eat(), 42);

    return e;
}

Value* SyntaxicalAnalyzer::eatFactor() {
    return nullptr;
}

Number* SyntaxicalAnalyzer::eatNumber() {
    return nullptr;
}

AST* SyntaxicalAnalyzer::getAST() { return ast; }