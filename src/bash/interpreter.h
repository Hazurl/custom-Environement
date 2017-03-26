#ifndef __BASH_INTERPRETER__
#define __BASH_INTERPRETER__

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "../../lib/Logger.h"

namespace bash {

#define INTERACTIVE_PREFIXE "~> "
#define INTERACTIVE_EXIT_CMD "$"

class Interpreter {
public: 
                            Interpreter                 ();
                            ~Interpreter                ();

    void                    interactive                 ();
    void                    runTest                     ();
    std::string             run                         (std::string code);
private:  

    enum class CharType {
        ALPHA, NUM, OTHER, SPACE
    };

class Token {
public:
    enum class              Type;

                            Token                       (std::string content, long position, Type type);

    std::string             content;
    long                    position;
    Token::Type             type;

    enum class Type {
        PLUS, MINUS, DIV, MUL, MOD,
        PARENTHESIS_LEFT, PARENTHESIS_RIGHT,
        FLOAT, INTEGER,

        END_OF_FILE, ALL
    };

    static std::string type_to_string (Type t) {
        switch(t) { case Type::PLUS : return "PLUS"; break;
                    case Type::MINUS : return "MINUS"; break;
                    case Type::DIV : return "DIV"; break;
                    case Type::MUL : return "MUL"; break;
                    case Type::MOD : return "MOD"; break;
                    case Type::PARENTHESIS_LEFT : return "PARENTHESIS_LEFT"; break;
                    case Type::PARENTHESIS_RIGHT : return "PARENTHESIS_RIGHT"; break;
                    case Type::FLOAT : return "FLOAT"; break;
                    case Type::INTEGER : return "INTEGER"; break;
                    case Type::ALL : return "ALL"; break;
                    case Type::END_OF_FILE : return "EOF"; break;}
    }
}; // class Token

//              FORWARD CLASS DECLARATION

    class                   AST;
    class                   InstructionNode;
    class                   ExpressionNode;
    class                   BinOpNode;
    class                   ValueNode;

    long                    tok_pos                     = 0;
    std::vector<Token*>     tokens;
    InstructionNode*        ast                         = nullptr;

//              TOKENIZE
    CharType                getCharType                 (char c);
    void                    validToken                  (std::string content, long pos, bool isFloat);
    void                    tokenize                    (std::string code);

//              PARSER
    Token*                  getNextToken                (unsigned int delta = 1);
    Token*                  eat                         (Interpreter::Token::Type type = Interpreter::Token::Type::ALL);
    ValueNode*              eatTerm                     ();
    InstructionNode*        eatInstruction              ();
    ExpressionNode*         eatExpression               ();
    void                    parse                       ();

//              EXECUTE
    std::string             evaluate                    ();



class AST {
public:
    virtual                 ~AST                        ();
    virtual void            visit                       () = 0;

    Token*                  token;

}; // class AST

class ValueNode : public AST {
public:
    float                   value;

    virtual float           getValue                    ();
    virtual void            visit                       ();
    virtual                 ~ValueNode                  ();
}; // class ValueNode

class BinOpNode : public ValueNode {
public:
    ValueNode*              leftValue;
    ValueNode*              rightValue;

    virtual void            visit                       ();
    virtual                 ~BinOpNode                  ();
}; // class BinOpNode

class ExpressionNode : public ValueNode {
public:
    ValueNode*              valueNode;

    virtual void            visit                       ();
    virtual                 ~ExpressionNode             ();
}; // class ExpressionNode

class InstructionNode : public AST {
public:
    ExpressionNode*         expr;

    virtual void            visit                       ();
    virtual                 ~InstructionNode            ();
}; // class InstructionNode

}; // class Interpreter

}; // namespace bash

#endif