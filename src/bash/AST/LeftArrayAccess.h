#ifndef __BASH_AST_LEFT_ARRAY__
#define __BASH_AST_LEFT_ARRAY__

#include "../Token.h"
#include "LeftValue.h"
#include "Ident.h"
#include <string>
#include <vector>

namespace bash {

class LeftArrayAccess : public LeftValue {
public:
    LeftArrayAccess(Token* t = nullptr);
    virtual ~LeftArrayAccess ();

    virtual std::string to_string();
    virtual void visit(Context& ctx);
    virtual void setValue(Context& ctx, Value v);

    LeftValue* var;
    ValueNode* key;
};

}; // namespace bash

#endif