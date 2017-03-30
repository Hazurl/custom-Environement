#include "interpreter.h"

using namespace bash;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {

}

Interpreter::~Interpreter () {
    if (this->ast)
        delete this->ast;

    for (Token* t : this->tokens)
        delete t;
}

void Interpreter::interactive () {
    std::string cmd;

    while (!std::cin.eof()) {
        std::cout << INTERACTIVE_PREFIXE;
		std::getline(std::cin, cmd);

        if (cmd == INTERACTIVE_EXIT_CMD)
            break;

        std::cout << run(cmd) << std::endl;
	}

    std::cout << std::endl;
}

std::string Interpreter::run(std::string code) {

    Logger::log("Running code : " + code);

    Logger::beginSection("Tokenize", Logger::Info);

        auto l = LexicalAnalyzer(code);

        bash::Token* t;
        while((t = l.eat())->type != bash::Token::Type::END)
            Logger::verbose( t->to_string(true) );

    Logger::endSection("Tokenize");

    Logger::beginSection("Parser", Logger::Info);

        auto s = SyntaxicalAnalyzer(l);
        Logger::log("To_string : " + s.getAST()->to_string());

    Logger::endSection("Parser");
    
    Logger::beginSection("Evaluate", Logger::Info);

        //auto ret = evaluate();

    Logger::endSection("Evaluate");
    return "";
}

void Interpreter::runTest () {
    Logger::log("Run Test");
}

//      =====   TOKENIZE    =====

Interpreter::CharType Interpreter::getCharType (char c) {
    if (c >= '0' && c <= '9')
        return CharType::NUM;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return CharType::ALPHA;
    if (c == ' ' || c == '\t' || c == '\n')
        return CharType::SPACE;

    return CharType::OTHER;
}

void Interpreter::tokenize (std::string code) {

    std::string curContent = "";
    long size = code.length();
    char curChar;
    CharType curType;

    long startPos = 0;
    bool number = false;

    for (long pos = 0; pos < size; ++pos) {
        curChar = code[pos];
        curType = getCharType(curChar);

        if (curType == CharType::SPACE) {
            if (curContent != "") {
                if (number)
                    tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
                else
                    throw std::runtime_error("Can't put a type on this token : " + curContent);
                curContent = "";
                number = false;
            }
            startPos = pos + 1;
        } else if (curType == CharType::NUM) {
            // eat a number float or integer
            if (!number && curContent != "")
                throw std::runtime_error("digit is not allowed here (" + std::to_string(pos) + ")");
            
            curContent += curChar;
            number = true;
        } else if (curType == CharType::OTHER) {
            if (curChar == '.') {
                // float
                if (!number && curContent != "")
                    throw std::runtime_error("digit is not allowed here (" + std::to_string(pos) + ")");
                
                if (curContent == "") 
                    curContent = "0";
                curContent += curChar;
                number = true;
            } else if (curChar == '+') {
                if (curContent != "") {
                    if (number)
                        tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
                    else
                        throw std::runtime_error("Can't put a type on this token : " + curContent);
                    curContent = "";
                    number = false;
                    startPos = pos;
                }
                tokens.push_back(new Token ("+", startPos, Token::Type::PLUS));
                startPos = pos + 1;
            } else if (curChar == '-') {
                if (curContent != "") {
                    if (number)
                        tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
                    else
                        throw std::runtime_error("Can't put a type on this token : " + curContent);
                    curContent = "";
                    number = false;
                    startPos = pos;
                }
                tokens.push_back(new Token ("-", startPos, Token::Type::MINUS));
                startPos = pos + 1;
            } else if (curChar == '*') {
                if (curContent != "") {
                    if (number)
                        tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
                    else
                        throw std::runtime_error("Can't put a type on this token : " + curContent);
                    curContent = "";
                    number = false;
                    startPos = pos;
                }
                tokens.push_back(new Token ("*", startPos, Token::Type::MUL));
                startPos = pos + 1;
            } else if (curChar == '/') {
                if (curContent != "") {
                    if (number)
                        tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
                    else
                        throw std::runtime_error("Can't put a type on this token : " + curContent);
                    curContent = "";
                    number = false;
                    startPos = pos;
                }
                tokens.push_back(new Token ("/", startPos, Token::Type::DIV));
                startPos = pos + 1;
            } else
                throw std::runtime_error("'" + std::string(1, curChar) + "' is not supported");
        } else
            throw std::runtime_error("Alpha characters are not supported");
    }

    if (curContent != "") {
        if (number)
            tokens.push_back(new Token (curContent, startPos, Token::Type::FLOAT)); // for the moment only float
        else
            throw std::runtime_error("Can't put a type on this token : " + curContent);
    }
}

//      =====   AST    =====

Interpreter::AST::~AST() {}

float Interpreter::ValueNode::getValue () {
    visit();
    return this->value;
}

Interpreter::ValueNode::~ValueNode() {}

void Interpreter::ValueNode::visit () {
    Logger::verbose("Visit a value ( " + std::to_string(this->value) + " )");
    return;
}

void Interpreter::ValueNode::print (std::ostream& os) {
    os << this->value;
}

Interpreter::BinOpNode::~BinOpNode() {
    delete this->leftValue;
    delete this->rightValue;
}

void Interpreter::BinOpNode::visit () {
    switch (this->token->type) {
        case Token::Type::PLUS :
            this->value = this->leftValue->getValue() + this->rightValue->getValue();
        break;

        case Token::Type::MINUS :
            this->value = this->leftValue->getValue() - this->rightValue->getValue();
        break;

        case Token::Type::DIV :
            this->value = this->leftValue->getValue() / this->rightValue->getValue();
        break;

        case Token::Type::MUL :
            this->value = this->leftValue->getValue() * this->rightValue->getValue();
        break;

        case Token::Type::MOD :
            this->value = 0.0;// float cannot be use with % //this->leftValue->getValue() % this->rightValue->getValue();
        break;

        default:
            throw std::runtime_error("BinOpNode::visit : this operation is not allowed");
        break;
    }
}

void Interpreter::BinOpNode::print (std::ostream& os) {
    os << "("; 
    this->leftValue->print(os);
    switch (this->token->type) {
        case Token::Type::PLUS :
            os << "+";
        break;

        case Token::Type::MINUS :
            os << "-";
        break;

        case Token::Type::DIV :
            os << "/";
        break;

        case Token::Type::MUL :
            os << "*";
        break;

        case Token::Type::MOD :
            os << "%";
        break;
        
        default:
            throw std::runtime_error("BinOpNode::visit : this operation is not allowed");
        break;
    }
    this->rightValue->print(os);
    os << ")";
}

Interpreter::ExpressionNode::~ExpressionNode() {
    delete this->valueNode;
}

void Interpreter::ExpressionNode::visit () {
    if (this->valueNode)
        this->value = this->valueNode->getValue();
}

void Interpreter::ExpressionNode::print (std::ostream& os) {
    this->valueNode->print(os);
}

Interpreter::InstructionNode::~InstructionNode() {
    delete this->expr;
}

void Interpreter::InstructionNode::visit () {
    this->expr->visit();
}

void Interpreter::InstructionNode::print (std::ostream& os) {
    this->expr->print(os);
}

//      =====   PARSER    =====

Interpreter::InstructionNode* Interpreter::eatInstruction () {
    Logger::info("eatInstruction");
    auto ins = new InstructionNode();
    ins->expr = eatExpression();

    return ins;
}

Interpreter::ExpressionNode* Interpreter::eatExpression () {
    Logger::info("eatExpression");
    auto expr = new ExpressionNode();

    expr->valueNode = eatTerm();

    auto tok_0 = getNextToken(0);
    while (tok_0->type == Interpreter::Token::Type::PLUS || tok_0->type == Interpreter::Token::Type::MINUS) {
        Logger::verbose("new add/minus");
        auto binOp = new BinOpNode();
        binOp->leftValue = expr->valueNode;
        binOp->token = eat();
        binOp->rightValue = eatTerm();
        expr->valueNode = binOp;
        tok_0 = getNextToken(0);
    }

    return expr;
}

Interpreter::BinOpNode* Interpreter::eatBinOpLow() {
    Logger::info("eatBinOpLow");
    auto opNode = new BinOpNode();
    opNode->rightValue = eatTerm();
    assert(getNextToken()->type == Interpreter::Token::Type::PLUS || getNextToken()->type == Interpreter::Token::Type::MINUS);
    opNode->token = eat();

    auto tok_1 = getNextToken(1);
    if (tok_1->type == Interpreter::Token::Type::PLUS || tok_1->type == Interpreter::Token::Type::MINUS)
        opNode->leftValue = eatBinOpLow();
    else
        opNode->leftValue = eatTerm();

    return opNode;
}

Interpreter::BinOpNode* Interpreter::eatBinOpHigh() {
    Logger::info("eatBinOpHigh");
    auto opNode = new BinOpNode();
    opNode->leftValue = eatNumber();
    assert(getNextToken()->type == Interpreter::Token::Type::MUL || getNextToken()->type == Interpreter::Token::Type::DIV);
    opNode->token = eat();

    auto tok_1 = getNextToken(1);
    if (tok_1->type == Interpreter::Token::Type::DIV || tok_1->type == Interpreter::Token::Type::MUL)
        opNode->rightValue = eatBinOpHigh();
    else
        opNode->rightValue = eatNumber();

    return opNode;
}

Interpreter::ValueNode* Interpreter::eatTerm() {
    Logger::info("eatTerm");
    ValueNode* node = eatNumber();

    auto tok_0 = getNextToken(0);
    while (tok_0->type == Interpreter::Token::Type::MUL || tok_0->type == Interpreter::Token::Type::DIV) {
        Logger::verbose("new mul/div");
        auto binOp = new BinOpNode();
        binOp->leftValue = node;
        binOp->token = eat();
        binOp->rightValue = eatNumber();
        node = binOp;
        tok_0 = getNextToken(0);
    }

    return node;

}

Interpreter::ValueNode* Interpreter::eatNumber() {
    Logger::verbose("I want a number");
    auto vnode = new ValueNode();
    vnode->value = std::stod(eat(Token::Type::FLOAT)->content);
    Logger::info("eatNumber : " + std::to_string(vnode->value));

    return vnode;
}

Interpreter::Token* Interpreter::eat(Token::Type type) {
    try {
        auto t = this->tokens.at(this->tok_pos++);
        Logger::warning("eat " + Token::type_to_string(type));
        Logger::warning("next token type is : " + Token::type_to_string(getNextToken(0)->type));
        if (t->type != type && type != Interpreter::Token::Type::ALL)
            throw std::runtime_error("Unexpected Token");
        else
            return t;
    } catch (std::exception const& e) {
        Logger::error("try to eat a '" + Token::type_to_string(type) + "' there is no one more");
        throw e;
    }
}

Interpreter::Token* Interpreter::getNextToken (unsigned int delta) {
    try {
        auto t = this->tokens.at(this->tok_pos + delta);
        Logger::verbose("next Token (d += " + std::to_string(delta) + ") : '" + t->content + "'");
        return t;
    } catch (std::exception const& e) {
        this->tokens.push_back(new Token("", -1, Interpreter::Token::Type::END_OF_FILE));
        Logger::verbose("next Token (d += " + std::to_string(delta) + ") : 'EOF'");
        return this->tokens[this->tokens.size() - 1];
    }
}

void Interpreter::parse () {
    this->tok_pos = 0;
    Logger::info("begin Parse -- tok_pos = 0");
    this->ast = eatInstruction();

    Logger::info("PRINT");
    this->ast->print(Logger::getInfoStream());
    Logger::getInfoStream() << std::endl;
}

//      =====   EXECUTE    =====

std::string Interpreter::evaluate () {
    if (this->ast && this->ast->expr)
        return std::to_string(ast->expr->getValue());
    throw std::runtime_error("evaluate failed");
}

//      =====   TOKEN    =====

Interpreter::Token::Token (std::string content, long position, Type type) :
    content(content), position(position), type(type) {}
