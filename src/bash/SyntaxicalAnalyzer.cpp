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
    while (!flow.isType(Token::Type::END)) {
        auto i = eatInstruction();
        if (i == nullptr) {
            Logger::error("Instruction null");
            delete mainBlock;
            mainBlock = nullptr;
            return;
        }
        mainBlock->push(i);
    }

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
        
    else if (flow.next()->type == Token::Type::COLON)
        return eatFuncCall();

    else 
        return eatAssignment();
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
    fr->from = eatExpression();

    flow.eat(Token::Type::TO);
    fr->to = eatExpression();

    if (flow.isType(Token::Type::STEP)) {
        flow.eat(Token::Type::STEP);
        fr->step = eatExpression();
    }

    fr->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDFOR) && !flow.isType(Token::Type::END))
        fr->then->push(eatInstruction());
    flow.eat(Token::Type::ENDFOR);

    return fr;
}

Assignment* SyntaxicalAnalyzer::eatAssignment() {
    Logger::info("eatAssignment");
    Assignment* ass = new Assignment();
    ass->var = eatValueNode();
    ass->token = flow.eat();
    auto tp = ass->token->type;
    if (tp == Token::Type::EQUAL) {
        ass->expr = eatExpression();
    } else if (tp == Token::Type::EQUAL_PLUS) {
        auto binOp = new BinOp(BinOp::Op::ADD, ass->token);
        binOp->left = ass->var;
        binOp->right = eatExpression();
    } else if (tp == Token::Type::EQUAL_MIN) {
        auto binOp = new BinOp(BinOp::Op::SUB, ass->token);
        binOp->left = ass->var;
        binOp->right = eatExpression();
    } else if (tp == Token::Type::EQUAL_MUL) {
        auto binOp = new BinOp(BinOp::Op::MUL, ass->token);
        binOp->left = ass->var;
        binOp->right = eatExpression();
    } else if (tp == Token::Type::EQUAL_DIV) {
        auto binOp = new BinOp(BinOp::Op::DIV, ass->token);
        binOp->left = ass->var;
        binOp->right = eatExpression();
    } else
        throw std::runtime_error("Expected an assignment");
    
    return ass;
}

Expression* SyntaxicalAnalyzer::eatExpression() {
    /* Priority Operator :
    *
    * unary minus
    * not
    * parenthesis
    * multiplication / division
    * addition / substraction
    * comparison ( != == <= >= < > )
    * and ( && )
    * or  ( || )
    *
    */
    Logger::info("eatExpression");

    auto e = new Expression();
    e->expr = eatOr();
    return e;
}

ValueNode* SyntaxicalAnalyzer::eatOr() {
    Logger::info("eatOr");
    ValueNode* node = eatAnd();

    while (flow.isType(Token::Type::OR)) {
        Logger::verbose("new or");
        auto binOp = new BinOp(BinOp::Op::OR);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatAnd();
        node = binOp;
    }

    return node;
}

ValueNode* SyntaxicalAnalyzer::eatAnd() {
    Logger::info("eatAnd");
    ValueNode* node = eatComp();

    while (flow.isType(Token::Type::AND)) {
        Logger::verbose("new and");
        auto binOp = new BinOp(BinOp::Op::AND);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatComp();
        node = binOp;
    }

    return node;
}

ValueNode* SyntaxicalAnalyzer::eatComp() {
    Logger::info("eatComp");
    ValueNode* node = eatAdd();

    auto tp = flow.current()->type;

    while (tp == Token::Type::EQUAL_EQUAL ||
           tp == Token::Type::NOT_EQUAL ||
           tp == Token::Type::LESS ||
           tp == Token::Type::LESS_EQUAL ||
           tp == Token::Type::GREATER ||
           tp == Token::Type::GREATER_EQUAL) {
        Logger::verbose("new Comp");
        BinOp* binOp;
        if (tp == Token::Type::EQUAL_EQUAL)
            binOp = new BinOp(BinOp::Op::EQ);
        else if (tp == Token::Type::NOT_EQUAL)
            binOp = new BinOp(BinOp::Op::NEQ);
        else if (tp == Token::Type::LESS)
            binOp = new BinOp(BinOp::Op::LT);
        else if (tp == Token::Type::LESS_EQUAL)
            binOp = new BinOp(BinOp::Op::LT_EQ);
        else if (tp == Token::Type::GREATER)
            binOp = new BinOp(BinOp::Op::GT);
        else if (tp == Token::Type::GREATER_EQUAL)
            binOp = new BinOp(BinOp::Op::GT_EQ);
         
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatAdd();
        node = binOp;
        tp = flow.current()->type;
    }

    return node;
}

ValueNode* SyntaxicalAnalyzer::eatAdd() {
    Logger::info("eatAdd");
    ValueNode* node = eatMul();

    while (flow.isType(Token::Type::PLUS) || flow.isType(Token::Type::MINUS)) {
        Logger::verbose("new add/sub");
        auto binOp = new BinOp(flow.isType(Token::Type::PLUS) ? BinOp::Op::ADD : BinOp::Op::SUB);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatMul();
        node = binOp;
    }

    return node;
}


ValueNode* SyntaxicalAnalyzer::eatMul() {
    Logger::info("eatMul");
    ValueNode* node = eatValueNode();

    while (flow.isType(Token::Type::MUL) || flow.isType(Token::Type::DIV)) {
        Logger::verbose("new mul/div");
        auto binOp = new BinOp(flow.isType(Token::Type::MUL) ? BinOp::Op::MUL : BinOp::Op::DIV);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatValueNode();
        node = binOp;
    }

    return node;
}

ValueNode* SyntaxicalAnalyzer::eatValueNode() {
    Logger::info("eatValueNode");
    if (flow.isType(Token::Type::MINUS)) {
        auto v = new UnOp(UnOp::Op::MIN, flow.eat());
        v->v = eatValueNode();
        return v;
    }
    if (flow.isType(Token::Type::NOT)) {
        auto v = new UnOp(UnOp::Op::NOT, flow.eat());
        v->v = eatValueNode();
        return v;
    }
    if (flow.isType(Token::Type::PARENTHESIS_LEFT)) {
        flow.eat();
        auto e = eatExpression();
        flow.eat(Token::Type::PARENTHESIS_RIGHT);
        if (flow.isType(Token::Type::BRACKET_LEFT))
            return eatArrayAccess(e);
        return e;
    }
    if (flow.isType(Token::Type::IDENT)) {
        auto i = eatIdent();
        if (flow.isType(Token::Type::BRACKET_LEFT))
            return eatArrayAccess(i);
        return i;
    }

    auto p = eatPrimitive();
    if (flow.isType(Token::Type::BRACKET_LEFT))
        return eatArrayAccess(p);
    return p;
}

Ident* SyntaxicalAnalyzer::eatIdent() {
    auto ident = new Ident(flow.eat(Token::Type::IDENT));
    Logger::info("eatIdent : " + ident->name);
    return ident;
}

Primitive* SyntaxicalAnalyzer::eatNumber() {
    auto t = flow.eat(Token::Type::NUMBER);
    auto prm = new Primitive(std::stod(t->content), t);
    Logger::info("eatNumber : " + prm->value.to_string());
    return prm;
}

Primitive* SyntaxicalAnalyzer::eatString() {
    auto t = flow.eat(Token::Type::STRING);
    auto prm = new Primitive(t->content, t);
    Logger::info("eatString : " + prm->value.to_string());
    return prm;
}

Array* SyntaxicalAnalyzer::eatArray() {
    Logger::info("eatArray");
    auto a = new Array(flow.eat(Token::Type::BRACKET_LEFT));
    while (!flow.isType(Token::Type::BRACKET_RIGHT)) {
        a->push(eatExpression());

        if (flow.isType(Token::Type::COMMA))
            flow.eat();
    }

    flow.eat();

    return a;
}

Primitive* SyntaxicalAnalyzer::eatPrimitive() {
    Logger::info("eatPrimitive");
    Token::Type t = flow.current()->type;
    if (t == Token::Type::NUMBER)
        return eatNumber();
    if (t == Token::Type::STRING)
        return eatString();
    if (t == Token::Type::BRACKET_LEFT)
        return eatArray();

    throw std::runtime_error("Expected a primitive value");
}

ArrayAccess* SyntaxicalAnalyzer::eatArrayAccess(ValueNode* var) {
    Logger::info("eatArrayAccess");
    if (!var)
        var = eatValueNode();

    ArrayAccess* a = new ArrayAccess(flow.eat(Token::Type::BRACKET_LEFT));
    a->var = var;
    a->key = eatExpression();
    flow.eat(Token::Type::BRACKET_RIGHT);

    while (flow.isType(Token::Type::BRACKET_LEFT)) {
        ArrayAccess* a_ = new ArrayAccess(flow.eat());
        a_->var = a;
        a_->key = eatExpression();
        a = a_;
        flow.eat(Token::Type::BRACKET_RIGHT);
    }

    return a;
}

FuncCall* SyntaxicalAnalyzer::eatFuncCall() {
    Logger::info("eatFuncCall");
    auto f = new FuncCall();
    f->func = eatIdent();
    f->token = flow.eat(Token::Type::COLON);
    while (!flow.isType(Token::Type::SEMICOLON) && !flow.isType(Token::Type::END)) {
        f->args.push_back(eatExpression());

        if (flow.isType(Token::Type::COMMA))
            flow.eat();
    }
    flow.eat(Token::Type::SEMICOLON);
    return f;
}