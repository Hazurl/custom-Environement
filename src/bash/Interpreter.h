#ifndef __BASH_INTERPRETER__
#define __BASH_INTERPRETER__

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <assert.h>
#include "Context.h"
#include "../../lib/Logger/src/Logger.h"
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "SyntaxicalAnalyzer.h"

namespace bash {

#define INTERACTIVE_PREFIXE "~> "
#define INTERACTIVE_EXIT_CMD "$"

class Interpreter {
public: 
                            Interpreter                 ();
                            ~Interpreter                ();

    void                    interactive                 ();
    void                    runTest                     ();
    std::string             run                         (std::string code);
private:  

}; // class Interpreter

}; // namespace bash

#endif