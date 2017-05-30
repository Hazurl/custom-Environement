#include "Interpreter.h"

using namespace bash;

using namespace haz;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {
    logger->setLevel(Level::CONFIG);
    initStdFunc();
}

Interpreter::~Interpreter () {}

void Interpreter::initStdFunc() {
    stdFuncs.insert( {"print", &std_bash_func::print} );
}

void Interpreter::interactive () {
    logger->ENTERING({});
    std::string cmd;
    Context ctx(&stdFuncs, "BASH", {});

    while (!std::cin.eof()) {
        std::cout << INTERACTIVE_PREFIXE;
		std::getline(std::cin, cmd);

        if (cmd == INTERACTIVE_EXIT_CMD)
            break;
        else if (cmd == INTERACTIVE_PRT_CTX)
            std::cout << ctx.to_string() << std::endl;
        else
            run(cmd, ctx);
	}
    logger->EXITING("void");
}

void Interpreter::run(std::string code, Context& ctx) {
    logger->ENTERING({"Context*"});
    logger->CONFIG("Running code : " + code);

    logger->TRACE("Tokenize");
    auto l = LexicalAnalyzer(code);            


    logger->TRACE("Parser");
    auto s = SyntaxicalAnalyzer(l);
    if (s.getAST() != nullptr)
        logger->DEBUG("To_string : " + s.getAST()->to_string());

    logger->TRACE("Evaluate");
    if (s.getAST() == nullptr)
        logger->ERROR("AST is null");
    else
        s.getAST()->visit(ctx);
    logger->EXITING("void");
}

void Interpreter::runTest () {
    logger->DEBUG("Run Test (Nothing)");
}

