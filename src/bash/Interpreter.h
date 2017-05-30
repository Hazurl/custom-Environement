#ifndef __BASH_INTERPRETER__
#define __BASH_INTERPRETER__

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <assert.h>

#include <logger.h>
#include "StandardFunc.h"
#include "Context.h"
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "SyntaxicalAnalyzer.h"

using namespace haz;

namespace bash {

#define INTERACTIVE_PREFIXE ">> "
#define INTERACTIVE_EXIT_CMD "$"
#define INTERACTIVE_PRT_CTX "£"

class Interpreter {
public: 
                            Interpreter                 ();
                            ~Interpreter                ();

    void                    interactive                 ();
    void                    runTest                     ();
    void                    run                         (std::string code, Context& ctx);
private:  

    Logger* logger = &Logger::get("#.Interpreter");

    void                    initStdFunc                 ();

    std::map<std::string, void (*) (Context&)> stdFuncs;

}; // class Interpreter

}; // namespace bash

#endif