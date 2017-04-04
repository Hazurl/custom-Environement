#include "Assignment.h"

using namespace bash;

Assignment::Assignment (Token* t) : Instruction(t) {}

Assignment::~Assignment() {
    if (var)
        delete var;

    if (expr)
        delete expr;
}

void Assignment::visit(Context& ctx) {
    ctx.setVar(var->name, expr->getValue(ctx));
}

std::string Assignment::to_string() {
    return var->to_string() + " = " + expr->to_string();
}