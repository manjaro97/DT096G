#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

namespace simpleparser{

    enum TokenType {
        WHITESPACE, 
        IDENTIFIER, 
        INTERER_LITERAL,
        DOUBLE_LITERAL,
        STRING_LITERAL,
        OPERATOR,
        STRING_ESCAPE_SEQUENCE, 
        POTENTIAL_DOUBLE,
        POTENTIAL_COMMENT,
        COMMENT
    };

    static const char* sTokenTypeStrings[] = {
        "WHITESPACE", 
        "IDENTIFIER", 
        "INTERER_LITERAL",
        "DOUBLE_LITERAL",
        "STRING_LITERAL",
        "OPERATOR",
        "STRING_ESCAPE_SEQUENCE", 
        "POTENTIAL_DOUBLE",
        "POTENTIAL_COMMENT",
        "COMMENT"
    };

    class Token{
    public: 
        enum TokenType mType{WHITESPACE};
        std::string mText;
        size_t mLineNumber{0};

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