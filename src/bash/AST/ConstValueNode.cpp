#include "ConstValueNode.h"

using namespace bash;

using namespace haz;

ConstValueNode::ConstValueNode (Value v, Token* t) : ValueNode(v, t) {}

ConstValueNode::~ConstValueNode () {}
    
void ConstValueNode::setValue(Context&, Value) {
    logger->THROWEXCEPTION(std::runtime_error, "Cannot set value of a constant one");
}
