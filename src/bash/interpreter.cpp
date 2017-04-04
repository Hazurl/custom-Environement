#include "interpreter.h"

using namespace bash;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {}

Interpreter::~Interpreter () {}

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

    Logger::section("Tokenize", Logger::ALL, Logger::INFO);

        auto l = LexicalAnalyzer(code);            

    Logger::section_end("Tokenize");

    Logger::section("Parser", Logger::ALL, Logger::INFO);

        auto s = SyntaxicalAnalyzer(l);
        Logger::log("To_string : " + s.getAST()->to_string());

    Logger::section_end("Parser");

    Logger::section("Evaluate", Logger::ALL, Logger::INFO);

    if (s.getAST() == nullptr)
        Logger::error("AST is null");
    else {
        Context ctx;
        s.getAST()->visit(ctx);
        Logger::section_end("Evaluate");
        return ctx.to_string();
    }

    Logger::section_end("Evaluate");
    return "";
}

void Interpreter::runTest () {
    Logger::log("Run Test (Nothing)");
}

