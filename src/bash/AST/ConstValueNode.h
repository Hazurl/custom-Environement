#ifndef __BASH_CST_VALUENODE__
#define __BASH_CST_VALUENODE__

#include "../Token.h"
#include "ValueNode.h"
#include <string>
#include <exception>
#include <stdexcept>

using namespace haz;

namespace bash {

class ConstValueNode : public ValueNode {
public:
    ConstValueNode (Value v, Token* t = nullptr);
    virtual ~ConstValueNode ();
    
    virtual void setValue(Context& ctx, Value v);
};

}; //namespace bash

#endif