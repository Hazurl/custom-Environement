#ifndef __BASH_LEXICAL__
#define __BASH_LEXICAL__

#include "Token.h"
#include "../../lib/Logger/src/Logger.h"
#include <vector>
#include <string>
#include <exception>

namespace bash {

class LexicalAnalyzer : public TokenFlow {
public:
    LexicalAnalyzer(std::string const& code);
    ~LexicalAnalyzer();

private:
    std::string code;
    long len;
    long curLine;
    long curPos;

    void tokenize();
    Token* findNextToken();
    void skipSpace();
    bool isDigit(char c);
    bool isOperator(char c);
    char next();
    char previous();
    char currentChar();
};

}; // namespace bash

#endif