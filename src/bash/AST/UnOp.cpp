#include "UnOp.h"

using namespace bash;

using namespace haz;

UnOp::UnOp (Op mode, Token* t) : ConstValueNode(0, t), mode(mode) {}

UnOp::~UnOp() {
    if (v)
        delete v;
}

std::string UnOp::to_string() {
    if (mode == Op::MIN)
        return "- ( " + v->to_string() + " ) ";
    else if (mode == Op::NOT)
        return "! ( " + v->to_string() + " ) ";
    logger->THROWEXCEPTION(std::runtime_error, "UnOp - operator not allow");
    return ""; // removing warning
}

void UnOp::visit (Context& ctx) {
    logger->ENTERING({"Context&"});
    if (mode == Op::MIN)
        value = - v->getValue(ctx);
    else if (mode == Op::NOT)
        value = (!v->getValue(ctx).to_bool()) ? Value(1) : Value(0);
    logger->EXITING("void");
}