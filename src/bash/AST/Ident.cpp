#include "Ident.h"

using namespace bash;

Ident::Ident (Token* t) : Value(0, t), name(t->content) {}

Ident::~Ident() {}

void Ident::visit() {

}

std::string Ident::to_string() {
    return name;
}