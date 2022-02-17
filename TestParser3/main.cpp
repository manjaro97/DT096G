//cd "c:\Users\j_c_k\Desktop\DT096G\TestParser3\" ; if ($?) { g++ main.cpp Tokenizer.cpp -o main } ; if ($?) { .\main }

#include "Tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace simpleparser;

int main(){
    std::cout << "simpleparser 0.1\n" << std::endl;

    FILE * fh = fopen("C:\\Users\\j_c_k\\Desktop\\DT096G\\TestParser3\\test.myc", "r");
    if(!fh){    std::cerr << "Can't find file. " << std::endl;    }
    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    std::string fileContents(fileSize, ' ');
    fread(fileContents.data(), 1, fileSize, fh);

    std::cout << fileContents << std::endl;

    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.parse(fileContents);

    for(Token currToken : tokens){
        currToken.debugPrint();
    }

    return 0;
}