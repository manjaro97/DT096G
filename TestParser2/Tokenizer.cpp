#include "Tokenizer.h"
#include <stdexcept>
#include <iostream>

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
                currentToken.mType = STRING_LITERAL;
                continue;
            }
            else if(currentToken.mType == POTENTIAL_COMMENT && currCh != '/'){
                currentToken.mType = OPERATOR;
                endToken(currentToken, tokens);
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
                        currentToken.mType = INTERER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else if (currentToken.mType == POTENTIAL_DOUBLE){
                        currentToken.mType = DOUBLE_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '.':
                    if (currentToken.mType == WHITESPACE){
                        currentToken.mType = POTENTIAL_DOUBLE;
                        currentToken.mText.append(1, currCh);
                    }
                    else if(currentToken.mType == INTERER_LITERAL){
                        currentToken.mType = INTERER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else if(currentToken.mType == STRING_LITERAL){
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
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
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    }
                    else{
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case ' ':   
                case '\t':
                    if(currentToken.mType == STRING_LITERAL || currentToken.mType == COMMENT){
                        currentToken.mText.append(1, currCh);
                    }else{
                        endToken(currentToken, tokens);
                    }   
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
                case '/':
                    if(currentToken.mType == STRING_LITERAL){
                        currentToken.mText.append(1, currCh);
                    }
                    else if(currentToken.mType == POTENTIAL_COMMENT){
                        currentToken.mType = COMMENT;
                        currentToken.mText.erase();
                    }
                    else{
                        currentToken.mType = POTENTIAL_COMMENT;
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                default:
                    if(currentToken.mType == WHITESPACE || currentToken.mType == INTERER_LITERAL 
                                                        || currentToken.mType == DOUBLE_LITERAL){
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
        if(token.mType == COMMENT){
            std::cout << "Ignoring Comment " << token.mText << std::endl;
        }
        else if(token.mType != WHITESPACE){
            tokens.push_back(token);
        }
        if(token.mType == POTENTIAL_DOUBLE){
            if(token.mText.compare(".") == 0){
                token.mType = OPERATOR;
            }
            else{
                token.mType = DOUBLE_LITERAL;
            }
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }

    void Token::debugPrint() const{
        std::cout << "Token(" << sTokenTypeStrings[mType] << ", \"" << mText << "\", " << mLineNumber << ")" << std::endl;
    }
    

}