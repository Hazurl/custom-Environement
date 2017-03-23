#ifndef __BASH_INTERPRETER__
#define __BASH_INTERPRETER__

#include <string>
#include <iostream>
#include <vector>

namespace bash {

#define INTERACTIVE_PREFIXE "~> "
#define INTERACTIVE_EXIT_CMD "exit"

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

    struct                  Token;
    class                   AST;

    std::vector<Token>      tokens;
    AST*                    ast                         = nullptr;

    CharType                getCharType                 (char c);

    void                    tokenize                    (std::string code);
    void                    parse                       ();
    std::string             evaluate                    ();



struct Token {
public:
    enum class              Type;

    Token::Type             type;
    std::string             content;
    unsigned long           position;

    enum class Type {
        PLUS, MINUS, DIV, MUL, MOD,
        PARENTHESIS_LEFT, PARENTHESIS_RIGHT
    };
}; // struct Token

class AST {

}; // class AST

}; // class Interpreter

}; // namespace bash

#endif