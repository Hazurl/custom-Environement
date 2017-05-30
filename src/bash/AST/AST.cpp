#include "AST.h"

using namespace bash;

using namespace haz;

AST::AST(Token* t) : token(t) {
    logger->setLevel(Level::WARNING);
}

AST::~AST() {}