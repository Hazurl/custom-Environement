#include "SyntaxicalAnalyzer.h"

using namespace bash;

using namespace haz;

SyntaxicalAnalyzer::SyntaxicalAnalyzer(TokenFlow& flow) : flow(flow) {
    logger->setLevel(Level::WARNING);
    parse();
}

SyntaxicalAnalyzer::~SyntaxicalAnalyzer() {
    if (mainBlock)
        delete mainBlock;
}

Block* SyntaxicalAnalyzer::getAST() { return mainBlock; }

void SyntaxicalAnalyzer::parse() {
    logger->ENTERING({});
    if (mainBlock)
        delete mainBlock;
    mainBlock = new Block();
    while (!flow.isType(Token::Type::END)) {
        auto i = eatInstruction();
        if (i == nullptr) {
            logger->ERROR("Instruction null");
            delete mainBlock;
            mainBlock = nullptr;
            return logger->RET("void");
        }
        mainBlock->push(i);
    }

    mainBlock->token = mainBlock->instr.front()->token;

    if (mainBlock == nullptr)
        logger->ERROR("mainBlock is null...");
    logger->EXITING("void");
}

Instruction* SyntaxicalAnalyzer::eatInstruction() {
    logger->ENTERING({});
    if (flow.isType(Token::Type::IF))
        return logger->RET("If* as Instruction*", eatIf());

    else if (flow.isType(Token::Type::FOR))
        return logger->RET("For* as Instruction*", eatFor());

    else if (flow.isType(Token::Type::WHILE))
        return logger->RET("While* as Instruction*", eatWhile());
        
    else if (flow.next()->type == Token::Type::COLON)
        return logger->RET("FuncCall* as Instruction*", eatFuncCall());

    else
        return logger->RET("Assignment* as Instruction*", eatAssignment());
}

If* SyntaxicalAnalyzer::eatIf() {
    logger->ENTERING({});
    If* iff = new If(flow.eat());

    iff->cond = eatExpression();

    iff->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::ELSE) && !flow.isType(Token::Type::END))
        iff->then->push(eatInstruction());

    if (flow.isType(Token::Type::ELSE)) {
        logger->DEBUG("with an else");
        iff->elze = new Block(flow.eat(Token::Type::ELSE));
        while(!flow.isType(Token::Type::ENDIF) && !flow.isType(Token::Type::END))
            iff->elze->push(eatInstruction());
        flow.eat(Token::Type::ENDIF);
    }

    return logger->RET("If*", iff);
}

While* SyntaxicalAnalyzer::eatWhile() {
    logger->ENTERING({});
    While* wh = new While(flow.eat());

    wh->cond = eatExpression();

    wh->then = new Block(flow.eat(Token::Type::THEN));
    while(!flow.isType(Token::Type::ENDWH) && !flow.isType(Token::Type::END))
        wh->then->push(eatInstruction());
    flow.eat(Token::Type::ENDWH);

    return logger->RET("While*", wh);
}

For* SyntaxicalAnalyzer::eatFor() {
    logger->ENTERING({});
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

    return logger->RET("For*", fr);
}

Assignment* SyntaxicalAnalyzer::eatAssignment() {
    logger->ENTERING({});
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
        logger->THROWEXCEPTION(std::runtime_error, "Expected an assignment");
    
    return logger->RET("Assignment*", ass);
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
    logger->ENTERING({});

    auto e = new Expression();
    e->expr = eatOr();
    return logger->RET("Expression*", e);
}

ValueNode* SyntaxicalAnalyzer::eatOr() {
    logger->ENTERING({});
    ValueNode* node = eatAnd();

    while (flow.isType(Token::Type::OR)) {
        logger->DEBUG("new or");
        auto binOp = new BinOp(BinOp::Op::OR);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatAnd();
        node = binOp;
    }
    return logger->RET("ValueNode*", node);
}

ValueNode* SyntaxicalAnalyzer::eatAnd() {
    logger->ENTERING({});
    ValueNode* node = eatComp();

    while (flow.isType(Token::Type::AND)) {
        logger->DEBUG("new and");
        auto binOp = new BinOp(BinOp::Op::AND);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatComp();
        node = binOp;
    }
    return logger->RET("ValueNode*", node);
}

ValueNode* SyntaxicalAnalyzer::eatComp() {
    logger->ENTERING({});
    ValueNode* node = eatAdd();

    auto tp = flow.current()->type;

    while (tp == Token::Type::EQUAL_EQUAL ||
           tp == Token::Type::NOT_EQUAL ||
           tp == Token::Type::LESS ||
           tp == Token::Type::LESS_EQUAL ||
           tp == Token::Type::GREATER ||
           tp == Token::Type::GREATER_EQUAL) {
        logger->DEBUG("new Comp");
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
    return logger->RET("ValueNode*", node);
}

ValueNode* SyntaxicalAnalyzer::eatAdd() {
    logger->ENTERING({});
    ValueNode* node = eatMul();

    while (flow.isType(Token::Type::PLUS) || flow.isType(Token::Type::MINUS)) {
        logger->DEBUG("new add/sub");
        auto binOp = new BinOp(flow.isType(Token::Type::PLUS) ? BinOp::Op::ADD : BinOp::Op::SUB);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatMul();
        node = binOp;
    }

    return logger->RET("ValueNode*", node);
}


ValueNode* SyntaxicalAnalyzer::eatMul() {
    logger->ENTERING({});
    ValueNode* node = eatValueNode();

    while (flow.isType(Token::Type::MUL) || flow.isType(Token::Type::DIV)) {
        logger->DEBUG("new mul/div");
        auto binOp = new BinOp(flow.isType(Token::Type::MUL) ? BinOp::Op::MUL : BinOp::Op::DIV);
        binOp->left = node;
        binOp->token = flow.eat();
        binOp->right = eatValueNode();
        node = binOp;
    }
    return logger->RET("ValueNode*", node);
}

ValueNode* SyntaxicalAnalyzer::eatValueNode() {
    logger->ENTERING({});
    if (flow.isType(Token::Type::MINUS)) {
        auto v = new UnOp(UnOp::Op::MIN, flow.eat());
        v->v = eatValueNode();
        return logger->RET("UnOp* as ValueNode*", v);
    }
    if (flow.isType(Token::Type::NOT)) {
        auto v = new UnOp(UnOp::Op::NOT, flow.eat());
        v->v = eatValueNode();
        return logger->RET("UnOp* as ValueNode*", v);
    }
    if (flow.isType(Token::Type::PARENTHESIS_LEFT)) {
        flow.eat();
        auto e = eatExpression();
        flow.eat(Token::Type::PARENTHESIS_RIGHT);
        if (flow.isType(Token::Type::BRACKET_LEFT))
            return logger->RET("ArrayAccess* as ValueNode*", eatArrayAccess(e));

        return logger->RET("Expression* as ValueNode*", e);
    }
    if (flow.isType(Token::Type::IDENT)) {
        auto i = eatIdent();
        if (flow.isType(Token::Type::BRACKET_LEFT))
            return logger->RET("ArrayAccess* as ValueNode*", eatArrayAccess(i));

        return logger->RET("Ident* as ValueNode*", i);
    }

    auto p = eatPrimitive();
    if (flow.isType(Token::Type::BRACKET_LEFT))
        return logger->RET("ArrayAccess* as ValueNode*", eatArrayAccess(p));

    return logger->RET("Primitive* as ValueNode*", p);
}

Ident* SyntaxicalAnalyzer::eatIdent() {
    logger->ENTERING({});
    auto ident = new Ident(flow.eat(Token::Type::IDENT));
    logger->INFO("eatIdent : " + ident->name);
    return logger->RET("Ident*", ident);
}

Primitive* SyntaxicalAnalyzer::eatNumber() {
    logger->ENTERING({});
    auto t = flow.eat(Token::Type::NUMBER);
    auto prm = new Primitive(std::stod(t->content), t);
    logger->INFO("eatNumber : " + prm->value.to_string());
    return logger->RET("Primitive*", prm);
}

Primitive* SyntaxicalAnalyzer::eatString() {
    logger->ENTERING({});
    auto t = flow.eat(Token::Type::STRING);
    auto prm = new Primitive(t->content, t);
    logger->INFO("eatString : " + prm->value.to_string());
    return logger->RET("Primitive*", prm);
}

Array* SyntaxicalAnalyzer::eatArray() {
    logger->ENTERING({});
    auto a = new Array(flow.eat(Token::Type::BRACKET_LEFT));
    while (!flow.isType(Token::Type::BRACKET_RIGHT)) {
        a->push(eatExpression());

        if (flow.isType(Token::Type::COMMA))
            flow.eat();
    }

    flow.eat();

    return logger->RET("Array*", a);
}

Primitive* SyntaxicalAnalyzer::eatPrimitive() {
    logger->ENTERING({});
    Token::Type t = flow.current()->type;
    if (t == Token::Type::NUMBER)
        return logger->RET("Array*", eatNumber());
    if (t == Token::Type::STRING)
        return logger->RET("Array*", eatString());
    if (t == Token::Type::BRACKET_LEFT)
        return logger->RET("Array*", eatArray());

    logger->THROWEXCEPTION(std::runtime_error, "Expected a primitive value");
    return nullptr;
}

ArrayAccess* SyntaxicalAnalyzer::eatArrayAccess(ValueNode* var) {
    logger->ENTERING({ (var ? "ValueNode* (nullptr)" : "ValueNode*") });
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

    return logger->RET("ArrayAccess*", a);
}

FuncCall* SyntaxicalAnalyzer::eatFuncCall() {
    logger->ENTERING({});
    auto f = new FuncCall();
    f->func = eatIdent();
    f->token = flow.eat(Token::Type::COLON);
    while (!flow.isType(Token::Type::SEMICOLON) && !flow.isType(Token::Type::END)) {
        f->args.push_back(eatExpression());

        if (flow.isType(Token::Type::COMMA))
            flow.eat();
    }

    if (flow.isType(Token::Type::SEMICOLON))
        flow.eat(Token::Type::SEMICOLON);
    return logger->RET("FuncCall*", f);
}