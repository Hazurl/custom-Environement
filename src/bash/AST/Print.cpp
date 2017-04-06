#include "Print.h"

using namespace bash;

Print::Print (Token* t) : Instruction(t) {}

Print::~Print() {
    if (v)
        delete v;
}

void Print::visit(Context& ctx) {
    ctx.print(v->getValue(ctx));
}

std::string Print::to_string() {
    return "print: " + v->to_string();
}
