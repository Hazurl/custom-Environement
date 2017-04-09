#ifndef __BASH_ARRAY__
#define __BASH_ARRAY__

#include "../Token.h"
#include "../Value.h"
#include "Primitive.h"

#include <string>
#include <vector>

namespace bash {

class Array : public Primitive {
public:

    Array(Token* t = nullptr);
    ~Array();

    void push (ValueNode* v);
    virtual std::string to_string();
    virtual void visit(Context& ctx);

    std::vector<ValueNode*> elems;
};

} // namespace bash

#endif