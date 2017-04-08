#include "Number.h"

using namespace bash;

Number::Number(Value v, Token* t) : ValueNode(v, t) {}

Number::~Number() {}

std::string Number::to_string() {
    return value.to_string();
}

void Number::visit (Context&) {}