#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

namespace simpleparser{

    enum TokenType {
        WHITESPACE, 
        IDENTIFIER, 
        INTEGER_LITERAL,
        OPERATOR,
        POTENTIAL_OPERATOR
    };

    static const char* sTokenTypeStrings[] = {
        "WHITESPACE", 
        "IDENTIFIER", 
        "INTEGER_LITERAL",
        "OPERATOR",
        "POTENTIAL_OPERATOR"
    };

    class Token{
    public: 
        enum TokenType mType{WHITESPACE};
        std::string mText;

        void debugPrint() const;

    private: 


    };

    class Tokenizer {
    public:
        std::vector<Token> parse(const std::string &inProgram);
    private: 
        void endToken(Token &token, std::vector<Token> &tokens);

    };

}

#endif