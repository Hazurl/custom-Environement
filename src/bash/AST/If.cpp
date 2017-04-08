#include "If.h"

using namespace bash;

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
    if (cond->getValue(ctx).to_bool())
        then->visit(ctx);
    else if (elze)
        elze->visit(ctx);
}

std::string If::to_string() {
    std::string s = "if " + cond->to_string() + " then ";
    s += then->to_string();

    if (elze)
        s += elze->to_string();

    return s;
}