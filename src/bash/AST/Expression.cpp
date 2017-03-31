#include "Expression.h"

using namespace bash;

Expression::Expression (Token* t) : Value(0, t) {}

Expression::~Expression() {
    if (expr)
        delete expr;
}

std::string Expression::to_string() {
    return expr ? expr->to_string() : "<empty expression>";
}

void Expression::visit () {
    if (expr)
        value = expr->getValue();
    else
        Logger::error("no expr");
}