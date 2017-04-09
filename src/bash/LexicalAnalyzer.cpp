#include "LexicalAnalyzer.h"

using namespace bash;

LexicalAnalyzer::LexicalAnalyzer(std::string const& code) :
    code(code), len(code.size()), curLine(1), curPos(0) {
    
    tokenize();
}

LexicalAnalyzer::~LexicalAnalyzer () {}

void LexicalAnalyzer::tokenize() {
    this->reset();

    for(curPos = 0; curPos < len; ++curPos) {
        //Logger::info("NEXT TOKEN (" + std::to_string(curPos) + ")");
        Token* t = findNextToken();
        if (t) { // not null
            this->push(t);
            Logger::verbose( t->to_string(true) );
        }
    }
}

Token* LexicalAnalyzer::findNextToken () {
    skipSpace();

    long startPos = curPos;
    char c = currentChar();
    if (c == -1) // EOF
        return nullptr;

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

    if (isOperator(c)) { // OPERATOR
        if (c == '+')
            return new Token(std::string(1, c), curPos, curLine, Token::Type::PLUS);
        if (c == '*')
            return new Token(std::string(1, c), curPos, curLine, Token::Type::MUL);
        if (c == '-')
            return new Token(std::string(1, c), curPos, curLine, Token::Type::MINUS);
        if (c == '/')
            return new Token(std::string(1, c), curPos, curLine, Token::Type::DIV);
    }

    if (isAlpha(c)) {
        do
            word += c;
        while(isAlphanum(c = next()));

        previous();

        return new Token(word, startPos, curLine, getTypeOfIdent(word));
    }

    if (c == '"' || c == '\'') {
        bool escape = false;
        if (c == '"') {
            while ((c = next()) != '"' || escape) {
                if (escape) {
                    escape = false;
                    if (c == 'n')
                        word += '\n';
                    else if (c == 't')
                        word += '\t';
                    else 
                        word += c;
                } else
                    if (!(escape = (c == '\\')))
                        word += c;
            }
        } else {
            while ((c = next()) != '\'' || escape) {
                if (escape && c == 'n') {
                    escape = false;
                    word += '\n';
                } else 
                    if (!(escape = (c == '\\')))
                        word += c;
            }
        }

        return new Token(word, startPos, curLine, Token::Type::STRING);
    }

    // OTHER

    if (c == '(')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::PARENTHESIS_LEFT);
    if (c == ')')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::PARENTHESIS_RIGHT);
    if (c == '[')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::BRACKET_LEFT);
    if (c == ']')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::BRACKET_RIGHT);
    if (c == '=')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::EQUAL);
    if (c == ':')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::COLON);
    if (c == ',')
        return new Token (std::string(1, c), curPos, curLine, Token::Type::COMMA);

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

bool LexicalAnalyzer::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
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

bool LexicalAnalyzer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool LexicalAnalyzer::isAlphanum(char c) {
    return isAlpha(c) || isDigit(c);
}

Token::Type LexicalAnalyzer::getTypeOfIdent(std::string const& ident) {
    if (ident == "if")
        return Token::Type::IF;
    if (ident == "endif")
        return Token::Type::ENDIF;
    if (ident == "while")
        return Token::Type::WHILE;
    if (ident == "endwh")
        return Token::Type::ENDWH;
    if (ident == "for")
        return Token::Type::FOR;
    if (ident == "endfor")
        return Token::Type::ENDFOR;
    if (ident == "print")
        return Token::Type::PRINT;
    if (ident == "then")
        return Token::Type::THEN;
    if (ident == "else")
        return Token::Type::ELSE;
    if (ident == "from")
        return Token::Type::FROM;
    if (ident == "to")
        return Token::Type::TO;
    if (ident == "step")
        return Token::Type::STEP;

    return Token::Type::IDENT;
}

