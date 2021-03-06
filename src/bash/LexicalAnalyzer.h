#ifndef __BASH_LEXICAL__
#define __BASH_LEXICAL__

#include "Token.h"
#include <logger.h>
#include <vector>
#include <string>
#include <exception>

using namespace haz;

namespace bash {

class LexicalAnalyzer : public TokenFlow {
public:
    LexicalAnalyzer(std::string const& code);
    ~LexicalAnalyzer();

private:
    Logger* logger = &Logger::get("#.LexicalAnalyzer");

    std::string code;
    long len;
    long curLine;
    long curPos;

    void tokenize();
    Token* findNextToken();
    void skipSpace();
    bool isOperator(char c);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphanum(char c);
    Token::Type getTypeOfIdent(std::string const& ident);
    char next();
    char previous();
    char currentChar();
};

}; // namespace bash

#endif