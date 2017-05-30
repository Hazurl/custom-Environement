#include "BinOp.h"

using namespace bash;

using namespace haz;

BinOp::BinOp (Op mode, Token* t) : ConstValueNode(0, t), mode(mode) {}

BinOp::~BinOp() {
    if (left)
        delete left;
    if (right)
        delete right;
}

std::string BinOp::to_string() {
    if (mode == Op::ADD)
        return " ( " + left->to_string() + "+" + right->to_string() + " ) ";
    else if (mode == Op::SUB)
        return " ( " + left->to_string() + "-" + right->to_string() + " ) ";
    else if (mode == Op::MUL)
        return " ( " + left->to_string() + "*" + right->to_string() + " ) ";
    else if (mode == Op::DIV)
        return " ( " + left->to_string() + "/" + right->to_string() + " ) ";
    else if (mode == Op::AND)
        return " ( " + left->to_string() + "&&" + right->to_string() + " ) ";
    else if (mode == Op::OR)
        return " ( " + left->to_string() + "||" + right->to_string() + " ) ";
    else if (mode == Op::EQ)
        return " ( " + left->to_string() + "==" + right->to_string() + " ) ";
    else if (mode == Op::NEQ)
        return " ( " + left->to_string() + "!=" + right->to_string() + " ) ";
    else if (mode == Op::GT_EQ)
        return " ( " + left->to_string() + ">=" + right->to_string() + " ) ";
    else if (mode == Op::GT)
        return " ( " + left->to_string() + ">" + right->to_string() + " ) ";
    else if (mode == Op::LT)
        return " ( " + left->to_string() + "<" + right->to_string() + " ) ";
    else if (mode == Op::LT_EQ)
        return " ( " + left->to_string() + "<=" + right->to_string() + " ) ";

    logger->THROWEXCEPTION(std::runtime_error, "BinOp - operator not allow");
    return ""; // removing warning
}

void BinOp::visit (Context& ctx) {
    logger->ENTERING({"Context&"});
    if (mode == Op::ADD)
        value = left->getValue(ctx) + right->getValue(ctx);
    else if (mode == Op::SUB)
        value = left->getValue(ctx) - right->getValue(ctx);
    else if (mode == Op::MUL)
        value = left->getValue(ctx) * right->getValue(ctx);
    else if (mode == Op::DIV)
        value = left->getValue(ctx) / right->getValue(ctx);
    else if (mode == Op::AND)
        value = (left->getValue(ctx).to_bool() && right->getValue(ctx).to_bool()) ? Value(1) : Value(0);
    else if (mode == Op::OR)
        value = (left->getValue(ctx).to_bool() || right->getValue(ctx).to_bool()) ? Value(1) : Value(0);
    else if (mode == Op::EQ)
        value = (left->getValue(ctx) == right->getValue(ctx)) ? Value(1) : Value(0);
    else if (mode == Op::NEQ)
        value = (left->getValue(ctx) != right->getValue(ctx)) ? Value(1) : Value(0);
    else if (mode == Op::GT_EQ)
        value = (left->getValue(ctx) >= right->getValue(ctx)) ? Value(1) : Value(0);
    else if (mode == Op::GT)
        value = (left->getValue(ctx) > right->getValue(ctx)) ? Value(1) : Value(0);
    else if (mode == Op::LT)
        value = (left->getValue(ctx) < right->getValue(ctx)) ? Value(1) : Value(0);
    else if (mode == Op::LT_EQ)
        value = (left->getValue(ctx) <= right->getValue(ctx)) ? Value(1) : Value(0);
    else
        logger->THROWEXCEPTION(std::runtime_error, "BinOp - operator not allow");
    logger->EXITING("void");
}