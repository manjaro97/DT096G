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
                        currentToken.mType = IGNORE_SENSITIVITY;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                        break;
                    case 'O':
                        currentToken.mType = OUTPUT;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                        break;
                    default: 
                        std::cout << currCh << std::endl;
                        throw std::runtime_error(std::string("Unknown Operation: \\") + std::string(1, currCh));
                }
                continue;
            }
            else if(currentToken.mType == CHARACTER || currentToken.mType == ANY_SYMBOL){
                switch(currCh){
                    case '*':
                        currentToken.mType = REPETITION_VALUE;
                        endToken(currentToken, tokens);
                        break;
                    case '{':
                        currentToken.mType = AMOUNT_VALUE;
                        endToken(currentToken, tokens);
                        break;
                }
            }
            if(currentToken.mType == LEFT_BRACKET){
                switch(currCh){
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
                        endToken(currentToken, tokens);
                        currentToken.mType = DIGIT;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                        continue;
                }
            }
        
            switch(currCh) {
                case '+':
                    endToken(currentToken, tokens);
                    currentToken.mType = OR_SYMBOL;
                    currentToken.mText.append(1, currCh);
                    break;
                case '*':
                    endToken(currentToken, tokens);
                    currentToken.mType = REPETITION_SYMBOL;
                    currentToken.mText.append(1, currCh);
                    break;
                case '(':
                    endToken(currentToken, tokens);
                    currentToken.mType = LEFT_PARANTHESES;
                    currentToken.mText.append(1, currCh);
                    break;
                case ')':
                    endToken(currentToken, tokens);
                    currentToken.mType = RIGHT_PARANTHESES;
                    currentToken.mText.append(1, currCh);
                    break;
                case '.':
                    endToken(currentToken, tokens);
                    currentToken.mType = ANY_SYMBOL;
                    currentToken.mText.append(1, currCh);
                    break;
                case '{':
                    endToken(currentToken, tokens);
                    currentToken.mType = LEFT_BRACKET;
                    currentToken.mText.append(1, currCh);
                    break;
                case '}':
                    endToken(currentToken, tokens);
                    currentToken.mType = RIGHT_BRACKET;
                    currentToken.mText.append(1, currCh);
                    break;
                case '\\':
                    endToken(currentToken, tokens);
                    currentToken.mType = POTENTIAL_OPERATOR;
                    currentToken.mText.append(1, currCh);
                    break;
                default:
                    endToken(currentToken, tokens);
                    currentToken.mType = CHARACTER;
                    currentToken.mText.append(1, currCh);
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