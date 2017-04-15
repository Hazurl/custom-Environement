#include "ArrayAccess.h"

using namespace bash;

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
    auto v = var->getValue(ctx);
    value = v.at(key->getValue(ctx));
}

void ArrayAccess::setValue(Context& ctx, Value v_) {
    Value v = var->getValue(ctx);
    Logger::verb("getValue returns : " + v.to_string(true));
    v.setAt(key->getValue(ctx), v_);
    Logger::verb("after setAt : " + v.to_string());
    var->setValue(ctx, v);
}
