#include "Token.h"

using namespace bash;

Token::~Token() {}

Token::Token(std::string content, long charPos, long linePos, Type type) :
    content(content), charPos(charPos), linePos(linePos), type(type) {}


Token* TokenFlow::current () {
    if (iteratorReset) {
        iteratorReset = false;
        if (tokens.empty()) {
            push(new Token("", -1, -1, Token::Type::END));
        }
        cur = tokens.begin();
    } else if (cur == tokens.end()) {
        push(new Token("", -1, -1, Token::Type::END));
        return tokens.back();
    }
    
    return *cur;
}

Token* TokenFlow::next(long delta) {
    if (iteratorReset) {
        iteratorReset = false;
        if (tokens.empty()) {
            push(new Token("", -1, -1, Token::Type::END));
            cur = tokens.begin();
            return *cur;
        }
        cur = tokens.begin();
    }

    if ((cur + delta) == tokens.end()) {
        push(new Token("", -1, -1, Token::Type::END));
        return tokens.back();
    }

    return *(cur + delta);
}

Token* TokenFlow::previous() {
    return next(-1);
}

Token* TokenFlow::eat(Token::Type type) {
    Token* t = current();

    if (t->type != type && type != Token::Type::FREE)
        throw std::runtime_error("Excepted type " + Token::type_to_string(type) + " and found " + Token::type_to_string(t->type));

    cur++;
    return t;
}

void TokenFlow::push(Token* token) {
    tokens.push_back(token);
}

void TokenFlow::reset() {
    for(Token* t : tokens) 
        delete t;
    tokens.clear();

    iteratorReset = true;
}

