#include "Value.h"

using namespace bash;

Value::Value(Token* t, double v) : AST(t), value(v) {}

double Value::getValue() {
    this->visit();
    return value;
}
