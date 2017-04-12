#ifndef __BASH_LEFT_V__
#define __BASH_LEFT_V__

#include <string>
#include "../../../lib/Logger/src/Logger.h"
#include "ValueNode.h"

namespace bash {

class LeftValue : public ValueNode {
public:
    LeftValue(Value v, Token* t = nullptr);
    virtual ~LeftValue();
    virtual void setValue (Context& ctx, Value v) = 0;
};

}; // namespace bash

#endif
