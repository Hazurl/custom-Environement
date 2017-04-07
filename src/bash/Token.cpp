#include "Token.h"

using namespace bash;

Token::~Token() {}

Token::Token(std::string content, long charPos, long linePos, Type type) :
    content(content), charPos(charPos), linePos(linePos), type(type) {}

std::string Token::to_string(bool allowColor) {
    if (allowColor)
        return "At line " + std::to_string(linePos) + "(" + std::to_string(charPos) + ") \"\033[34m" 
         + content + "\033[0m\" : \033[33m" + bash::Token::type_to_string(type) + "\033[0m";
    return "At line " + std::to_string(linePos) + "(" + std::to_string(charPos) + ") \"" 
        + content + "\" : " + bash::Token::type_to_string(type) + "";
}


TokenFlow::~TokenFlow() {
    for(Token* t : tokens) 
        delete t;
    for(auto p : fakes) 
        delete p.second;
}

Token* TokenFlow::current () { return next(0); }
Token* TokenFlow::previous() { return next(-1); }

Token* TokenFlow::next(long delta) {
    Token* t = getAt(pos + delta);
    if (!t)
        return fakeToken(Token::Type::END);

    return t;
}

bool TokenFlow::isType(Token::Type type, long delta) {
    return next(delta)->type == type;
}

Token* TokenFlow::eat(Token::Type type) {
    Token* t = current();

    if (t->type != type && type != Token::Type::FREE)
        throw std::runtime_error("Excepted type " + Token::type_to_string(type) + " and found " + Token::type_to_string(t->type));

    pos++;
    return t;
}

void TokenFlow::push(Token* token) {
    tokens.push_back(token);
}

void TokenFlow::reset() {
    for(Token* t : tokens) 
        delete t;
    tokens.clear();

    pos = 0;
}

Token* TokenFlow::getAt(long p) {
    try {
        return tokens.at(p);
    } catch (std::out_of_range const& e) {
        return nullptr;
    }
}

Token* TokenFlow::fakeToken(Token::Type t) {
    if (fakes.find(t) == fakes.end())
        return fakes[t] = new Token("", -1, -1, t);
    return fakes[t];
}