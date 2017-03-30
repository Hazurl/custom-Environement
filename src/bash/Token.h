#ifndef __BASH_TOKEN__
#define __BASH_TOKEN__

#include "../../lib/Logger/src/Logger.h"

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace bash {

class Token {
public:

    enum class Type;

    Token(std::string content, long charPos, long linePos, Type type);
    ~Token();

    std::string to_string(bool allowColor = false);

    std::string content;
    long charPos;
    long linePos;
    Type type;

    enum class Type {
        PLUS, MINUS, DIV, MUL,
        PARENTHESIS_LEFT, PARENTHESIS_RIGHT,
        NUMBER, // float
        END, FREE // used to eat a token who his type don't care 
    };

    static std::string type_to_string (Type type) {
        switch (type) {
            case Type::PLUS: return "Plus";
            case Type::MINUS: return "Minus";
            case Type::DIV: return "Divide";
            case Type::MUL: return "Multiply";
            case Type::PARENTHESIS_LEFT: return "Parenthesis left";
            case Type::PARENTHESIS_RIGHT: return "Parenthesis right";
            case Type::NUMBER: return "Number";
            case Type::END: return "End";
            case Type::FREE: return "Free";
        }
        throw std::runtime_error("type_to_string : unkknown type (" + std::to_string((int)type) + ")");
    }
};

class TokenFlow {
protected:
    std::vector<Token*> tokens;
    std::vector<Token*>::iterator cur;
    bool iteratorReset = true;

    void push(Token* token);
    void reset();

public:
    Token* current ();
    Token* next(long delta = 1);
    Token* previous(); // maybe useless

    Token* eat(Token::Type type = Token::Type::FREE);
};

}; // namespace bash

#endif