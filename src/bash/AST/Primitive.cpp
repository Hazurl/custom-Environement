#include "Primitive.h"

using namespace bash;

Primitive::Primitive(Value v, Token* t) : ConstValueNode(v, t) {}

Primitive::~Primitive() {}

std::string Primitive::to_string() {
    return value.to_string();
}

void Primitive::visit (Context&) {}