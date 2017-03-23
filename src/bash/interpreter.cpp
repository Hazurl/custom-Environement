#include "interpreter.h"

using namespace bash;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {

}

Interpreter::~Interpreter () {

}

void Interpreter::interactive () {
    std::string cmd;

    while (!std::cin.eof()) {
        std::cout << INTERACTIVE_PREFIXE;
		std::getline(std::cin, cmd);

        if (cmd == INTERACTIVE_EXIT_CMD)
            break;

        run(cmd);
	}

    std::cout << std::endl;
}

std::string Interpreter::run(std::string code) {
    if (this->ast)
        delete this->ast;

    this->tokens.clear();

    tokenize(code);
    parse();
    return evaluate();
}

void Interpreter::runTest () {
    std::cout << "TEST" << std::endl;
}

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

    std::string curTokenContent = "";

    for (char& c : code) {
        CharType type = getCharType(c);          
    }
    std::cout << std::endl;
}

void Interpreter::parse () {

}

std::string Interpreter::evaluate () {
    return "";
}
