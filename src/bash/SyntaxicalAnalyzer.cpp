#include "SyntaxicalAnalyzer.h"

using namespace bash;

SyntaxicalAnalyzer::SyntaxicalAnalyzer(TokenFlow& flow) : flow(flow) {
    parse();
}

SyntaxicalAnalyzer::~SyntaxicalAnalyzer() {
    if (mainBlock)
        delete mainBlock;
}

Block* SyntaxicalAnalyzer::getAST() { return mainBlock; }

void SyntaxicalAnalyzer::parse() {
    mainBlock = new Block();
    while (!flow.isType(Token::Type::END))
        mainBlock->push(eatInstruction());

    mainBlock->token = mainBlock->instr.front()->token;

    if (mainBlock == nullptr)
        Logger::error("mainBlock is null...");
}

Instruction* SyntaxicalAnalyzer::eatInstruction() {
    Logger::info("eatInstruction");
    if (flow.isType(Token::Type::IF))
        return eatIf();

    else if (flow.isType(Token::Type::FOR))
        return eatFor();

    else if (flow.isType(Token::Type::WHILE))
        return eatWhile();
        
    else if (flow.next()->type == Token::Type::EQUAL) 
        return eatAssignment();

    return nullptr;
}

If* SyntaxicalAnalyzer::eatIf() {
    Logger::info("eatIf");
    If* iff = new If(flow.eat());

    iff->cond = eatExpression();

    iff->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::ELSE) && !flow.isType(Token::Type::END))
        iff->then->push(eatInstruction());

    if (flow.isType(Token::Type::ELSE)) {
        Logger::verbose("with an else");
        iff->elze = new Block(flow.eat(Token::Type::ELSE));
        while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::END))
            iff->elze->push(eatInstruction());
        flow.eat(Token::Type::ENDIF);
    }

    return iff;
}

While* SyntaxicalAnalyzer::eatWhile() {
    Logger::info("eatWhile");
    While* wh = new While(flow.eat());

    wh->cond = eatExpression();

    wh->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDWH) && !flow.isType(Token::Type::END))
        wh->then->push(eatInstruction());
    flow.eat(Token::Type::ENDWH);

    return wh;
}

For* SyntaxicalAnalyzer::eatFor() {
    Logger::info("eatFor");
    For* fr = new For(flow.eat());

    fr->var = new Ident(flow.eat(Token::Type::IDENT));

    flow.eat(Token::Type::FROM);
    fr->from = eatNumber();

    flow.eat(Token::Type::TO);
    fr->to = eatNumber();

    if (flow.isType(Token::Type::STEP)) {
        flow.eat(Token::Type::STEP);
        fr->step = eatNumber();
    }

    fr->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDFOR) && !flow.isType(Token::Type::END))
        fr->then->push(eatInstruction());
    flow.eat(Token::Type::ENDFOR);

    return fr;
}

Assignment* SyntaxicalAnalyzer::eatAssignment() {
    Logger::info("eatAssignment");
    Assignment* ass = new Assignment(flow.current());
    ass->var = new Ident(flow.eat(Token::Type::IDENT));
    flow.eat(Token::Type::EQUAL);
    ass->expr = eatExpression();
    
    return ass;
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

