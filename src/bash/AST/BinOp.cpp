#include "BinOp.h"

using namespace bash;

BinOp::BinOp (Token* t) : Value(t, 0) {}

BinOp::~BinOp() {
    if (left)
        delete left;
    if (right)
        delete right;
}

std::string BinOp::to_string() {
    if (left && right) {
        if (token->type == Token::Type::PLUS)
            return " ( " + left->to_string() + "+" + right->to_string() + " ) ";
        if (token->type == Token::Type::MINUS)
            return " ( " + left->to_string() + "-" + right->to_string() + " ) ";
        if (token->type == Token::Type::MUL)
            return " ( " + left->to_string() + "*" + right->to_string() + " ) ";
        if (token->type == Token::Type::DIV)
            return " ( " + left->to_string() + "/" + right->to_string() + " ) ";
    } else 
        return "<empty binary operation>";
}

void BinOp::visit () {
    if (left && right) {
        if (token->type == Token::Type::PLUS)
            value = left->getValue() + "+" + right->getValue();
        if (token->type == Token::Type::MINUS)
            value = left->getValue() + "-" + right->getValue();
        if (token->type == Token::Type::MUL)
            value = left->getValue() + "*" + right->getValue();
        if (token->type == Token::Type::DIV)
            value = left->getValue() + "/" + right->getValue();
    }
}