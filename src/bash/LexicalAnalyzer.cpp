#include "LexicalAnalyzer.h"

using namespace bash;

LexicalAnalyzer::LexicalAnalyzer(std::string const& code) :
    code(code), len(code.size()), curLine(1), curPos(0) {
    
    tokenize();
}

LexicalAnalyzer::~LexicalAnalyzer () {}

void LexicalAnalyzer::tokenize() {
    this->reset();

    Logger::log("BEGIN TOKENIZE");
    for(curPos = 0; curPos < len; ++curPos) {
        Logger::info("NEXT TOKEN (" + std::to_string(curPos) + ")");
        Token* t = findNextToken();
        if (t) // not null
            this->push(t);
    }
}

Token* LexicalAnalyzer::findNextToken () {
    skipSpace();

    long startPos = curPos;
    char c = currentChar();
    std::string word;

    if (isDigit(c) || c == '.') { // NUMBER
        if (c == '.') word += "0.";
        else          word += c;

        bool hasDot = (c == '.');

        while(isDigit(c = next()) || (c == '.' && !hasDot)) {
            if(c == '.')
                hasDot = true;
            word += c;
        }

        if (previous() == '.') // we want to reverse the next() call used in the condition of the while
            word += '0';

        return new Token(word, startPos, curLine, Token::Type::NUMBER);
    }

    Logger::error("No token found");
    return nullptr;
}

void LexicalAnalyzer::skipSpace () {
    char c = currentChar();
    while (c == ' ' || c == '\t' || c == '\n') {
        if (c == '\n')
            curLine++;
        c = next();
    }
}

bool LexicalAnalyzer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char LexicalAnalyzer::currentChar() {
    if (curPos < len)
        return code[curPos];
    else
        return -1;
}

char LexicalAnalyzer::next() {
    if (++curPos < len)
        return code[curPos];
    else
        return -1;
}

char LexicalAnalyzer::previous() {
    if (--curPos >= 0)
        return code[curPos];
    else
        return -1;
}