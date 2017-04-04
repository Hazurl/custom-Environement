#include "Number.h"

using namespace bash;

Number::Number(double v, Token* t) : Value(v, t) {}

Number::~Number() {}

std::string Number::to_string() {
    return std::to_string(value);
}

void Number::visit (Context& ctx) {}