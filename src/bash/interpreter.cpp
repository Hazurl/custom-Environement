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

    return "";

    Logger::section("Evaluate", Logger::ALL, Logger::INFO);

    if (s.getAST() == nullptr)
        Logger::error("AST is null");
    else;
        //auto ret = s.getAST()->getValue();

    Logger::section_end("Evaluate");
    return "";//std::to_string(ret);
}

void Interpreter::runTest () {
    Logger::log("Run Test");
    std::cout << "./5 : " << run("./5") << std::endl;
    std::cout << "1+1 : " << run("1+1") << std::endl;
    std::cout << "\t5/2 + 1 : " << run("\t5/2 + 1") << std::endl;
    std::cout << "2+2*8 : " << run("2+2*8") << std::endl;
    std::cout << "5+(((5*2+(2) ))) : " << run("5+(((5*2+(2) )))") << std::endl;
    std::cout << "1-1+1*2 : " << run("1-1+1*2") << std::endl;
    std::cout << ".+.-.+1 : " << run(".+.-.+1") << std::endl;
}

