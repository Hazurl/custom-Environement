#include "Block.h"

using namespace bash;

using namespace haz;

Block::Block (Token* t) : AST(t) {}

Block::~Block() {
    for (auto& i : instr)
        delete i;
}

void Block::visit(Context& ctx) {
    logger->ENTERING({"Context&"});
    for (auto i : instr)
        i->visit(ctx);
    logger->EXITING("void");
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
