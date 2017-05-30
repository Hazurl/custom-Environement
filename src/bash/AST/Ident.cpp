#include "Ident.h"

using namespace bash;

using namespace haz;

Ident::Ident (Token* t) : ValueNode(0, t), name(t->content) {}

Ident::~Ident() {}

void Ident::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    value = ctx.getVar(name);
    logger->EXITING("void");
}

std::string Ident::to_string() {
    return name;
}

void Ident::setValue(Context& ctx, Value v) {
    ctx.setVar(name, v);
}