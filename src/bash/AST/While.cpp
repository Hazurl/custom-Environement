#include "While.h"

using namespace bash;

While::While (Token* t) : Instruction(t) {}

While::~While() {
    if(cond)
        delete cond;

    if (then)
        delete then;
}

void While::visit(Context& ctx) {
    while (cond->getValue(ctx))
        then->visit(ctx);
}

std::string While::to_string() {
    return "while " + cond->to_string() + " then " + then->to_string();
}