#include "Value.h"

using namespace bash;

Value::Value(double v, Token* t) : AST(t), value(v) {}

double Value::getValue(Context& ctx) {
    this->visit(ctx);
    return value;
}
