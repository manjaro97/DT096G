#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Tokenizer.h"


namespace simpleparser{
    class Parser{
    public:
        void parse(std::vector<Token> &tokens);
    private:
        std::vector<Token>::iterator mCurrentToken;
        std::vector<Token>::iterator mEndToken;

    };
}


#endif