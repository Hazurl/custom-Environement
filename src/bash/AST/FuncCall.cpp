#include "FuncCall.h"

using namespace bash;

using namespace haz;

FuncCall::FuncCall (Token* t) : Instruction(t) {}

FuncCall::~FuncCall() {
    if (func)
        delete func;

    for (auto arg : args)
        delete arg;
}

void FuncCall::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    std::vector<Value> vs;
    for (auto arg : args)
        vs.push_back(arg->getValue(ctx));
    ctx.call(func->name, vs);
    logger->EXITING("void");
}

std::string FuncCall::to_string() {
    std::string str = func->name + ": ";
    for (auto arg : args)
        str += arg->to_string();
    return str;
}
