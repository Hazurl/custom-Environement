#ifndef __BASH_LEXICAL__
#define __BASH_LEXICAL__

#include "Token.h"
#include <vector>
#include <string>

namespace bash {

class LexicalAnalyzer : public TokenFlow {
public:
    LexicalAnalyzer(std::string const& code);
    ~LexicalAnalyzer();

private:
    std::string code;
    long curLine;
    long curChar;

    void tokenize();
    Token* findNextToken();
};

}; // namespace bash

#endif