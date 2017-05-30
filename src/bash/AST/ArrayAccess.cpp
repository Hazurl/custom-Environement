#include "ArrayAccess.h"

using namespace bash;

using namespace haz;

ArrayAccess::ArrayAccess(Token* t) : ValueNode(0, t) {}

ArrayAccess::~ArrayAccess() {
    if (var)
        delete var;
    if (key)
        delete key;
}

std::string ArrayAccess::to_string() {
    return var->to_string() + "[" + key->to_string() + "]";
}

void ArrayAccess::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    auto v = var->getValue(ctx);
    value = v.at(key->getValue(ctx));
    logger->EXITING("void");
}

void ArrayAccess::setValue(Context& ctx, Value v_) {
    Value v = var->getValue(ctx);
    v.setAt(key->getValue(ctx), v_);
    var->setValue(ctx, v);
}
