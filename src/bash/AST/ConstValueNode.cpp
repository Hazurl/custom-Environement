#include "ConstValueNode.h"

using namespace bash;

ConstValueNode::ConstValueNode (Value v, Token* t) : ValueNode(v, t) {}

ConstValueNode::~ConstValueNode () {}
    
void ConstValueNode::setValue(Context&, Value) {
    throw std::runtime_error("Cannot set value of a constant one");
}
