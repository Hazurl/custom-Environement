#include "ValueNode.h"

using namespace bash;

ValueNode::ValueNode(Value v, Token* t) : AST(t), value(v) {}
ValueNode::~ValueNode() {};

Value ValueNode::getValue(Context& ctx) {
    this->visit(ctx);
    return value;
}
