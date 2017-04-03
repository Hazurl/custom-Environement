#include "Assignment.h"

using namespace bash;

Assignment::Assignment (Token* t) : Instruction(t) {}

Assignment::~Assignment() {
    if (var)
        delete var;

    if (expr)
        delete expr;
}

void Assignment::visit() {

}

std::string Assignment::to_string() {
    return var->to_string() + " = " + expr->to_string();
}