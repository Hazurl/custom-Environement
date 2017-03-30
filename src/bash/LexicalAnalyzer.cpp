#include "LexicalAnalyzer.h"

using namespace bash;

LexicalAnalyzer::LexicalAnalyzer(std::string const& code) :
    code(code), curLine(1), curChar(0) {
    
    tokenize();
}

LexicalAnalyzer::~LexicalAnalyzer () {}

void LexicalAnalyzer::tokenize() {
    
}

Token* LexicalAnalyzer::findNextToken () {

}