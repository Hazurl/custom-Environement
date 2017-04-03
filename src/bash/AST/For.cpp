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

    for (auto& i : block)
        delete i;
}

void For::visit() {

}

std::string For::to_string() {
    std::string s = "for " + var->to_string() + " from " + from->to_string() + " to " + to->to_string() + " ";
    if (step)
        s += "step " + step->to_string() + " then ";
    for (auto& i : block)
        s += i->to_string() + "; ";

    return s;
}