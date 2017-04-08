#include "UnOp.h"

using namespace bash;

UnOp::UnOp (Token* t) : ValueNode(0, t) {}

UnOp::~UnOp() {
    if (v)
        delete v;
}

std::string UnOp::to_string() {
    if (v) {
        if (token->type == Token::Type::MINUS)
            return "- ( " + v->to_string() + " ) ";
        throw std::runtime_error("UnOp - operator not allow");
    } else 
        return "<empty unary operation>";
}

void UnOp::visit (Context& ctx) {
    if (token->type == Token::Type::MINUS)
        value = - v->getValue(ctx);
}