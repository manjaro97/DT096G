#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

namespace simpleparser{

    enum TokenType {
        NONTOKEN, 
        POTENTIAL_OPERATOR,
        CHARACTER,
        OR_SYMBOL,
        REPETITION_SYMBOL,
        REPETITION_VALUE,
        ANY_SYMBOL,
        LEFT_PARANTHESES,
        RIGHT_PARANTHESES,
        AMOUNT_VALUE,
        LEFT_BRACKET,
        DIGIT,
        RIGHT_BRACKET,
        IGNORE_SENSITIVITY,
        OUTPUT
    };

    static const char* sTokenTypeStrings[] = {
        "NONTOKEN", 
        "POTENTIAL_OPERATOR", 
        "CHARACTER",
        "OR_SYMBOL",
        "REPETITION_SYMBOL",
        "REPETITION_VALUE",
        "ANY_SYMBOL",
        "LEFT_PARANTHESES",
        "RIGHT_PARANTHESES",
        "AMOUNT_VALUE",
        "LEFT_BRACKET",
        "DIGIT",
        "RIGHT_BRACKET",
        "IGNORE_SENSITIVITY",
        "OUTPUT"
    };

    class Token{
    public: 
        enum TokenType mType{NONTOKEN};
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