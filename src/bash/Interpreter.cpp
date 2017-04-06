#include "Interpreter.h"

using namespace bash;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {}

Interpreter::~Interpreter () {}

void Interpreter::interactive () {
    std::string cmd;
    Context ctx;

    while (!std::cin.eof()) {
        std::cout << INTERACTIVE_PREFIXE;
		std::getline(std::cin, cmd);

        if (cmd == INTERACTIVE_EXIT_CMD)
            break;

        run(cmd, ctx);
        std::cout << ctx.to_string() << std::endl;
	}

    std::cout << std::endl;
}

void Interpreter::run(std::string code, Context& ctx) {

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
    else
        s.getAST()->visit(ctx);

    Logger::section_end("Evaluate");
}

void Interpreter::runTest () {
    Logger::log("Run Test (Nothing)");
}

