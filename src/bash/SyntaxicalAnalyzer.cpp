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

    if (ast == nullptr)
        Logger::error("ast is null...");
}

Expression* SyntaxicalAnalyzer::eatExpression() {
    Logger::info("eatExpression");
    auto e = new Expression();

    e->expr = eatFactor();

    auto tok = flow.current();
    while (tok->type == Token::Type::PLUS || tok->type == Token::Type::MINUS) {
        Logger::verbose("new add/minus");
        auto binOp = new BinOp();
        binOp->left = e->expr;
        binOp->token = flow.eat();
        binOp->right = eatFactor();
        e->expr = binOp;

        tok = flow.current();
    }

    return e;
}

Value* SyntaxicalAnalyzer::eatFactor() {
    Logger::info("eatFactor");
    Value* node = eatValue();

    auto tok = flow.current();
    while (tok->type == Token::Type::MUL || tok->type == Token::Type::DIV) {
        Logger::verbose("new mul/div");
        auto binOp = new BinOp();
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatValue();
        node = binOp;

        tok = flow.current();
    }

    return node;
}

Value* SyntaxicalAnalyzer::eatValue() {
    if (flow.current()->type == Token::Type::MINUS) {
        auto v = new UnOp(flow.eat());
        v->v = eatValue();
        return v;
    }
    if (flow.current()->type == Token::Type::PARENTHESIS_LEFT) {
        flow.eat();
        auto e = eatExpression();
        flow.eat(Token::Type::PARENTHESIS_RIGHT);
        return e;
    }

    return eatNumber();
}

Number* SyntaxicalAnalyzer::eatNumber() {
    auto t = flow.eat(Token::Type::NUMBER);
    auto num = new Number(std::stod(t->content), t);
    Logger::info("eatNumber : " + std::to_string(num->value));

    return num;
}

Expression* SyntaxicalAnalyzer::getAST() { return ast; }