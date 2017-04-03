#include "SyntaxicalAnalyzer.h"

using namespace bash;

SyntaxicalAnalyzer::SyntaxicalAnalyzer(TokenFlow& flow) : flow(flow) {
    parse();
}

SyntaxicalAnalyzer::~SyntaxicalAnalyzer() {
    if (ast)
        delete ast;
}

Instruction* SyntaxicalAnalyzer::getAST() { return ast; }

void SyntaxicalAnalyzer::parse() {
    ast = eatInstruction();

    if (ast == nullptr)
        Logger::error("ast is null...");
}

Instruction* SyntaxicalAnalyzer::eatInstruction() {
    Logger::info("eatInstruction");
    if (flow.isType(Token::Type::IF)) {
        Logger::verbose("new if");
        If* iff = new If(flow.eat());

        iff->cond = eatExpression();

        flow.eat(Token::Type::THEN);
        while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::ELSE) && !flow.isType(Token::Type::END))
            iff->thenBlock.push_back(eatInstruction());

        if (flow.isType(Token::Type::ELSE)) {
            Logger::verbose("with an else");
            flow.eat();
            while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::END))
                iff->elseBlock.push_back(eatInstruction());
        }

        return iff;
    }

    return nullptr;
}

Expression* SyntaxicalAnalyzer::eatExpression() {
    Logger::info("eatExpression");
    auto e = new Expression();

    e->expr = eatFactor();

    while (flow.isType(Token::Type::PLUS) || flow.isType(Token::Type::MINUS)) {
        Logger::verbose("new add/minus");
        auto binOp = new BinOp();
        binOp->left = e->expr;
        binOp->token = flow.eat();
        binOp->right = eatFactor();
        e->expr = binOp;
    }

    return e;
}

Value* SyntaxicalAnalyzer::eatFactor() {
    Logger::info("eatFactor");
    Value* node = eatValue();

    while (flow.isType(Token::Type::MUL) || flow.isType(Token::Type::DIV)) {
        Logger::verbose("new mul/div");
        auto binOp = new BinOp();
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatValue();
        node = binOp;
    }

    return node;
}

Value* SyntaxicalAnalyzer::eatValue() {
    if (flow.isType(Token::Type::MINUS)) {
        auto v = new UnOp(flow.eat());
        v->v = eatValue();
        return v;
    }
    if (flow.isType(Token::Type::PARENTHESIS_LEFT)) {
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

