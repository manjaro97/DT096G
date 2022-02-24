//cd "c:\Users\j_c_k\Desktop\DT096G\TestParser3\" ; if ($?) { g++ main.cpp Tokenizer.cpp Parser.cpp -o main } ; if ($?) { .\main }
//cd "c:\Users\Manjaro\Desktop\DT096G\TestParser3\" ; if ($?) { g++ main.cpp Tokenizer.cpp Parser.cpp -o main } ; if ($?) { .\main }

#include "Tokenizer.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

using namespace simpleparser;


int main(){
    std::cout << "simpleparser 0.1\n" << std::endl;

    std::string regularExpression = "ab(c+d)ef*.g.*h{3}\\I\\O{1}";
    
    std::cout << regularExpression << std::endl;

    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.parse(regularExpression);

    for(Token currToken : tokens){
        currToken.debugPrint();
    }

    return 0;
}