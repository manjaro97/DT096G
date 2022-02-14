#include "Tokenizer.h"
#include <stdexcept>

namespace simpleparser{

    std::vector<Token> Tokenizer::parse(const std::string &inProgram){
        std::vector<Token> tokens; 
        Token currentToken;

        currentToken.mLineNumber = 1;

        for(char currCh: inProgram){

            if(currentToken.mType == STRING_ESCAPE_SEQUENCE){
                switch(currCh){
                    case 'n':
                        currentToken.mText.append(1, '\n'); 
                        break;
                    case 'r':
                        currentToken.mText.append(1, '\r'); 
                        break;
                    case 't':
                        currentToken.mText.append(1, '\t'); 
                        break;
                    case '\\':
                        currentToken.mText.append(1, '\\'); 
                        break;
                    default:
                        throw std::runtime_error(std::string("unknown escape sequence: \\") + std::string(1, currCh) + 
                        " in string on line" + std::to_string(currentToken.mLineNumber) + ".");
                }
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
                        currentToken.mType = INTERER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '.':
                    if (currentToken.mType == WHITESPACE){
                        currentToken.mType = INTERER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else if(){
                        currentToken.mType = INTERER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '{':
                case '}':
                case '(':
                case ')':
                case '=':
                case '-':
                case ',':
                case ';':
                    if (currentToken.mType != STRING_LITERAL){
                        endToken(currentToken);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case ' ':   
                case '\t':
                    endToken(currentToken, tokens);   
                    break;
                case '\r':   
                case '\n':
                    endToken(currentToken, tokens);   
                    ++currentToken.mLineNumber;   
                    break;
                case '"':
                    if (currentToken.mType != STRING_LITERAL){
                        endToken(currentToken, tokens);
                        currentToken.mType = STRING_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else if(currentToken.mType == STRING_LITERAL){
                        endToken(currentToken, tokens);
                    }
                    break;
                case '\\':
                    if (currentToken.mType == STRING_LITERAL){
                        currentToken.mType = STRING_ESCAPE_SEQUENCE;
                    }
                    else{
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    }
                    break;
                default:
                    break;

            }
        }

        return tokens;
    }

    void Tokenizer::endToken(Token &token, std::vector<Token> &tokens){
        if(token.mType != WHITESPACE){
            tokens.push_back(token);
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }
    

}