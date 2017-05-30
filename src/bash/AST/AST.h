#ifndef __BASH_AST__
#define __BASH_AST__

#include "../Token.h"
#include "../Context.h"
#include <string>
#include <logger.h>

using namespace haz;

namespace bash {

class AST {
public:
    AST (Token* t = nullptr);
    virtual ~AST ();
    virtual std::string to_string() = 0;
    virtual void visit(Context& ctx) = 0;

    Token* token = nullptr;

protected:
    Logger* logger = &Logger::get("#.AST");
};

}; // namespace bash

#endif