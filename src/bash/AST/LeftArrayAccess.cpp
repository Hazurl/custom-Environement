#include "LeftArrayAccess.h"

using namespace bash;

LeftArrayAccess::LeftArrayAccess(Token* t) : LeftValue(0, t) {}

LeftArrayAccess::~LeftArrayAccess () {
    if (var)
        delete var;
    
    if (key)
        delete key;
}

std::string LeftArrayAccess::to_string() {
    return var->to_string() + "[" + key->to_string() + "]";
}

void LeftArrayAccess::visit(Context& ctx) {
    value = var->getValue(ctx).at(key->getValue(ctx));
}

void LeftArrayAccess::setValue(Context& ctx, Value v_) {
    Value v = var->getValue(ctx);
    Logger::verb("getValue returns : " + v.to_string(true));
    v.setAt(key->getValue(ctx), v_);
    Logger::verb("after setAt : " + v.to_string());
    var->setValue(ctx, v);
}
