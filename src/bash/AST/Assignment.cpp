#include "Assignment.h"

using namespace bash;

using namespace haz;

Assignment::Assignment (Token* t) : Instruction(t) {}

Assignment::~Assignment() {
    if (var)
        delete var;

    if (expr)
        delete expr;
}

void Assignment::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    var->setValue(ctx, expr->getValue(ctx));
    logger->EXITING("void");
}

std::string Assignment::to_string() {
    return var->to_string() + " = " + expr->to_string();
}