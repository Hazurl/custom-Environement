#ifndef __BASH_ARRAY_ACC__
#define __BASH_ARRAY_ACC__

#include "../Token.h"
#include "ValueNode.h"
#include <string>

using namespace haz;

namespace bash {

class ArrayAccess : public ValueNode {
public:
    ArrayAccess (Token* t = nullptr);
    virtual ~ArrayAccess ();
    
    virtual std::string to_string();
    virtual void visit(Context& ctx);
    virtual void setValue(Context& ctx, Value v);

    ValueNode* var = nullptr;
    ValueNode* key = nullptr;
};

}; // namespace bash

#endif