#include "If.h"

using namespace bash;

using namespace haz;

If::If (Token* t) : Instruction(t) {}

If::~If() {
    if(cond)
        delete cond;

    if (then)
        delete then;
    
    if (elze)
        delete elze;
}

void If::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    if (cond->getValue(ctx).to_bool())
        then->visit(ctx);
    else if (elze)
        elze->visit(ctx);
    logger->EXITING("void");
}

std::string If::to_string() {
    std::string s = "if " + cond->to_string() + " then ";
    s += then->to_string();

    if (elze)
        s += elze->to_string();

    return s;
}