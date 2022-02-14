#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

namespace simpleparser{

    enum TokenType {
        WHITESPACE, 
        IDENTIFIER, 
        INTERER_LITERAL,
        STRING_LITERAL,
        OPERATOR,
        STRING_ESCAPE_SEQUENCE, 
        POTENTIAL_DOUBLE
    };

    class Token{
    public: 
        enum TokenType mType{WHITESPACE};
        std::string mText;
        size_t mStartOffset{0};
        size_t mEndOffset{0};
        size_t mLineNumber{0};
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