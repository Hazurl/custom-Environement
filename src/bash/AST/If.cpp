#include "If.h"

using namespace bash;

If::If (Token* t) : Instruction(t) {}

If::~If() {
    if(cond)
        delete cond;

    for (auto& i : thenBlock)
        delete i;

    for (auto& i : elseBlock)
        delete i;
}

void If::visit() {

}

std::string If::to_string() {
    std::string s = "if " + cond->to_string() + " then ";
    for (auto& i : thenBlock)
        s += i->to_string() + "; ";

    if (!elseBlock.empty()) {
        s += "else ";
        for (auto& i : elseBlock)
            s += i->to_string() + "; ";
    }

    return s;
}