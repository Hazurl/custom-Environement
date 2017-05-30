#include "Expression.h"

using namespace bash;

using namespace haz;

Expression::Expression (Token* t) : ConstValueNode(0, t) {}

Expression::~Expression() {
    if (expr)
        delete expr;
}

std::string Expression::to_string() {
    return expr->to_string();
}

void Expression::visit (Context& ctx) {
    logger->ENTERING({"Context&"});
    value = expr->getValue(ctx);
    logger->EXITING("void");
}