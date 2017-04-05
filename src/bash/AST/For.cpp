#include "For.h"

using namespace bash;

For::For (Token* t) : Instruction(t) {}

For::~For() {
    if(var)
        delete var;

    if(from)
        delete from;

    if(to)
        delete to;

    if(step)
        delete step;

    if(then)
        delete then;
}

void For::visit(Context& ctx) {
    if (from->getValue(ctx) < to->getValue(ctx))
        for(ctx.setVar(var->name, from->getValue(ctx));                             // init
            ctx.getVar(var->name) < to->getValue(ctx);                             // cond
            ctx.setVar(var->name, ctx.getVar(var->name) + (step ? step->getValue(ctx) : 1)))   // incrementation
                then->visit(ctx);
    else
        for(ctx.setVar(var->name, from->getValue(ctx));                             // init
            ctx.getVar(var->name) > to->getValue(ctx);                             // cond
            ctx.setVar(var->name, ctx.getVar(var->name) + (step ? step->getValue(ctx) : -1)))   // incrementation
                then->visit(ctx);

}

std::string For::to_string() {
    std::string s = "for " + var->to_string() + " from " + from->to_string() + " to " + to->to_string() + " ";
    if (step)
        s += "step " + step->to_string() + " then ";

    s += then->to_string();

    return s;
}