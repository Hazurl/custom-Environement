#include "ValueNode.h"

using namespace bash;

ValueNode::ValueNode(double v, Token* t) : AST(t), value(v) {}

double ValueNode::getValue(Context& ctx) {
    this->visit(ctx);
    return value;
}
