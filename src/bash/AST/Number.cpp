#include "Number.h"

using namespace bash;

Number::Number(Token* t, double v) : Value(t, v) {}

Number::~Number() {}

std::string Number::to_string() {
    return std::to_string(value);
}

void Number::visit () {}