#include "Tokenizer.h"
#include <stdexcept>
#include <iostream>

namespace simpleparser{

    std::vector<Token> Tokenizer::parse(const std::string &inProgram){
        std::vector<Token> tokens; 
        Token currentToken;

        for(char currCh: inProgram){

            if(currentToken.mType == POTENTIAL_OPERATOR){
                switch(currCh){
                    case 'I':
                    case 'O':
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                        break;
                    default: 
                        std::cout << currCh << std::endl;
                        throw std::runtime_error(std::string("Unknown Operation: \\") + std::string(1, currCh));
                }
                continue;
            }
        
            switch(currCh) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (currentToken.mType == WHITESPACE){
                        currentToken.mType = INTEGER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '+':
                case '*':
                case '(':
                case ')':
                case '.':
                case '{':
                case '}':
                    endToken(currentToken, tokens);
                    currentToken.mType = OPERATOR;
                    currentToken.mText.append(1, currCh);
                    endToken(currentToken, tokens);
                    break;
                case '\\':
                    endToken(currentToken, tokens);
                    currentToken.mType = POTENTIAL_OPERATOR;
                    currentToken.mText.append(1, currCh);
                    break;
                default:
                    if(currentToken.mType == WHITESPACE || currentToken.mType == INTEGER_LITERAL){
                        endToken(currentToken, tokens);
                        currentToken.mType = IDENTIFIER;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;

            }
        }

        endToken(currentToken, tokens);

        return tokens;
    }

    void Tokenizer::endToken(Token &token, std::vector<Token> &tokens){
        if(token.mType != WHITESPACE){
            tokens.push_back(token);
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }

    void Token::debugPrint() const{
        std::cout << "Token(" << sTokenTypeStrings[mType] << ", \"" << mText << "\")" << std::endl;
    }
    

}