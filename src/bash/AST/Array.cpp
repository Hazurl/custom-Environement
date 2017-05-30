#include "Array.h"

using namespace bash;

using namespace haz;

Array::Array(Token* t) : Primitive(Value({}), t) {}

Array::~Array() {
    for (ValueNode* v : elems)
        delete v;
}

void Array::push (ValueNode* v) {
    elems.push_back(v);
}

std::string Array::to_string() {
    std::string s = "[";
    bool first = true;
    for (ValueNode* v : elems) {
        if (!first)
            s += ", ";
        else
            first = false;

        s += v->to_string();
    }

    return s + "]";
}

void Array::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    value.clearArray();
    for (ValueNode* v : elems)
        value.push_back(v->getValue(ctx));
    logger->EXITING("void");
}
