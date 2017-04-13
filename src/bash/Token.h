#ifndef __BASH_TOKEN__
#define __BASH_TOKEN__

#include "../../lib/Logger/src/Logger.h"

#include <vector>
#include <vector>
#include <map>
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
        BRACKET_LEFT, BRACKET_RIGHT,
        EQUAL, EQUAL_PLUS, EQUAL_MUL, EQUAL_DIV, EQUAL_MIN,
        EQUAL_EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, OR, AND,
        COLON, COMMA, 
        IDENT, NUMBER, STRING,
        IF, THEN, ELSE, ENDIF, // if
        WHILE, ENDWH, // while
        FOR, FROM, TO, STEP, ENDFOR, // for
        PRINT, // used to print value to standard output

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
            case Type::BRACKET_LEFT: return "Bracket left";
            case Type::BRACKET_RIGHT: return "Bracket right";
            case Type::EQUAL: return "Equal";
            case Type::EQUAL_PLUS: return "Plus-Equal";
            case Type::EQUAL_MUL: return "Mul-Equal";
            case Type::EQUAL_DIV: return "Div-Equal";
            case Type::EQUAL_MIN: return "Min-Equal";
            case Type::EQUAL_EQUAL: return "Equal-Equal";
            case Type::LESS: return "Less";
            case Type::LESS_EQUAL: return "Less-Equal";
            case Type::GREATER: return "Greater";
            case Type::GREATER_EQUAL: return "Greater-Equal";
            case Type::OR: return "Or";
            case Type::AND: return "And";
            case Type::COLON: return "Colon";
            case Type::COMMA: return "Comma";
            case Type::STRING: return "String";
            case Type::IDENT: return "Ident";
            case Type::NUMBER: return "Number";
            case Type::IF: return "If";
            case Type::THEN: return "Then";
            case Type::ELSE: return "Else";
            case Type::ENDIF: return "EndIf";
            case Type::WHILE: return "While";
            case Type::ENDWH: return "EndWhile";
            case Type::FOR: return "For";
            case Type::FROM: return "From";
            case Type::TO: return "To";
            case Type::STEP: return "Step";
            case Type::ENDFOR: return "EndFor";
            case Type::PRINT: return "Print";
            case Type::END: return "End";
            case Type::FREE: return "Free";

            default:
                throw std::runtime_error("type_to_string : unkknown type (" + std::to_string((int)type) + ")");
            break;
        }
    }
};

class TokenFlow {
protected:
    std::vector<Token*> tokens;
    std::map<Token::Type, Token*> fakes;
    long pos = 0;
    bool iteratorReset = true;

    void push(Token* token);
    Token* getAt(long p);
    void reset();

public:
    Token* current ();
    Token* next(long delta = 1);
    Token* previous(); // maybe useless
    bool isType(Token::Type type, long delta = 0);
    Token* fakeToken(Token::Type t, std::string startContent = "");

    Token* eat(Token::Type type = Token::Type::FREE);

    virtual ~TokenFlow();
};

}; // namespace bash

#endif