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
    Logger::info("cleaning ast/tokens");
    if (this->ast)
        delete this->ast;

    for (Token* t : this->tokens)
        delete t;

    this->tokens.clear();

    Logger::log("Tokenize");
    tokenize(code);
    Logger::info("Tokens : ");
    for (auto t : tokens) {
        Logger::verbose("At pos = " + std::to_string(t->position) + ", " + Token::type_to_string(t->type) + " '" + t->content + "'");
    }

    Logger::log("Parsing");
    parse();
    Logger::log("Evaluate");
    return evaluate();
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

void Interpreter::validToken (std::string content, long pos, bool isFloat) {
    // can only e a number for the moment
    if (true) // (isFloat) for the moment
        tokens.push_back(new Token (content, pos, Token::Type::FLOAT));
    else
        tokens.push_back(new Token (content, pos, Token::Type::INTEGER));
}

void Interpreter::tokenize (std::string code) {

    /*
    std::string curTokenContent = "";
    long pos = -1;

    bool isFloat = false;

    for (char& c : code) {
        CharType type = getCharType(c);
        pos ++;

        switch (type) {
            case CharType::SPACE :
                if (curTokenContent != "") {
                    validToken(curTokenContent, pos, isFloat);
                    curTokenContent = "";
                    isFloat = false;
                }
            break;

            case CharType::NUM :
                curTokenContent += c;
            break;

            case CharType::ALPHA :
                if (curTokenContent != ""){
                    validToken(curTokenContent, pos - 1, isFloat);
                    curTokenContent = "";
                    isFloat = false;
                }

                throw "Unexpected Token";
            break;

            case CharType::OTHER :
                if (c == '.') {
                    if (isFloat)
                        // Already a dot
                        throw "Unexpected token";
                    if (curTokenContent == "")
                        curTokenContent += "0";
                    isFloat = true;
                    curTokenContent += c;
                } else {
                    if (curTokenContent != "") {
                        validToken(curTokenContent, pos - 1, isFloat);
                        curTokenContent = "";
                    }

                    if (c == '+')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::PLUS));
                    else if (c == '-')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::MINUS));
                    else if (c == '/')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::DIV));
                    else if (c == '*')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::MUL));
                    else if (c == '%')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::MOD));

                    else if (c == '(')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::PARENTHESIS_LEFT));
                    else if (c == ')')
                        tokens.push_back(new Token (std::string(1, c), pos, Token::Type::PARENTHESIS_RIGHT));

                    else throw "Unexpected Token";
                }
            break;
        }
    }

    if (curTokenContent != "") {
        validToken(curTokenContent, pos, isFloat);
        curTokenContent = "";
        isFloat = false;
    }*/
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
    }
}

Interpreter::ExpressionNode::~ExpressionNode() {
    delete this->valueNode;
}

void Interpreter::ExpressionNode::visit () {
    if (this->valueNode)
        this->value = this->valueNode->getValue();
}

Interpreter::InstructionNode::~InstructionNode() {
    delete this->expr;
}

void Interpreter::InstructionNode::visit () {
    this->expr->visit();
}

//      =====   PARSER    =====

Interpreter::InstructionNode* Interpreter::eatInstruction () {
    auto ins = new InstructionNode();
    ins->expr = eatExpression();

    return ins;
}

Interpreter::ExpressionNode* Interpreter::eatExpression () {
    auto expr = new ExpressionNode();
    auto vNode = eatTerm();

    auto nextT = getNextToken();
    if (nextT->type == Interpreter::Token::Type::PLUS || nextT->type == Interpreter::Token::Type::MINUS) {
        Logger::verbose("eat a binOp");
        auto opNode = new BinOpNode();
        opNode->leftValue = vNode;
        opNode->token = eat();
        opNode->rightValue = eatTerm();
        expr->valueNode = opNode;
    } else
        expr->valueNode = vNode;

    return expr;
}

Interpreter::ValueNode* Interpreter::eatTerm() {
    auto vnode = new ValueNode();
    vnode->value = std::stod(eat(Token::Type::FLOAT)->content);

    return vnode;
}

Interpreter::Token* Interpreter::eat(Token::Type type) {
    auto t = this->tokens.at(this->tok_pos++);
    Logger::verbose("eat " + Token::type_to_string(type));
    if (t->type != type && type != Interpreter::Token::Type::ALL)
        throw "Unexpected Token";
    else
        return t;
}

Interpreter::Token* Interpreter::getNextToken (unsigned int delta) {
    try {
        auto t = this->tokens.at(this->tok_pos + delta);
        Logger::verbose("next Token : '" + t->content + "'");
        return t;
    } catch (std::exception const& e) {
        this->tokens.push_back(new Token("", -1, Interpreter::Token::Type::END_OF_FILE));
        Logger::verbose("next Token : 'EOF'");
        return this->tokens[this->tokens.size() - 1];
    }
}

void Interpreter::parse () {
    this->tok_pos = 0;
    this->ast = eatInstruction();
}

//      =====   EXECUTE    =====

std::string Interpreter::evaluate () {
    if (this->ast && this->ast->expr)
        return std::to_string(ast->expr->getValue());
    return "wtf ?";
}

//      =====   TOKEN    =====

Interpreter::Token::Token (std::string content, long position, Type type) :
    content(content), position(position), type(type) {}
