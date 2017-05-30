#include "While.h"

using namespace bash;

using namespace haz;

While::While (Token* t) : Instruction(t) {}

While::~While() {
    if(cond)
        delete cond;

    if (then)
        delete then;
}

void While::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    while (cond->getValue(ctx).to_bool())
        then->visit(ctx);
    logger->EXITING("void");
}

std::string While::to_string() {
    return "while " + cond->to_string() + " then " + then->to_string();
}