#include "Ident.h"

using namespace bash;

Ident::Ident (Token* t) : ValueNode(0, t), name(t->content) {}

Ident::~Ident() {}

void Ident::visit(Context& ctx) {
    value = ctx.getVar(name);
}

std::string Ident::to_string() {
    return name;
}