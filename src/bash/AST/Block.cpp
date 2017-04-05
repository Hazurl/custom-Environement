#include "Block.h"

using namespace bash;

Block::Block (Token* t) : AST(t) {}

Block::~Block() {
    for (auto& i : instr)
        delete i;
}

void Block::visit(Context& ctx) {
    for (auto i : instr)
        i->visit(ctx);
}

std::string Block::to_string() {
    std::string s = "";
    for (auto& i : instr)
        s += i->to_string() + "; ";

    return s;
}

void Block::push(Instruction* i) {
    instr.push_back(i);
}
