//cd "c:\Users\j_c_k\Desktop\DT096G\Labb1\" ; if ($?) { g++ main.cpp Tokenizer.cpp parsetree.cpp -o main } ; if ($?) { .\main }
//cd "c:\Users\Manjaro\Desktop\DT096G\Labb1\" ; if ($?) { g++ main.cpp Tokenizer.cpp parsetree.cpp -o main } ; if ($?) { .\main }

#include "Tokenizer.h"
#include "classes.h"
#include "parsetree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace simpleparser;


int main(){
    std::cout << "simpleparser 0.1\n" << std::endl;

    std::string text = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    //std::string input = "ab(c+d)ef*.g.*h{3}\\I\\O{1}";
    //std::string input = "lo* could.{3}";
    std::string input = "wa";
    //std::string input = "Hello World";

    std::cout << input << std::endl;

    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.parse(input);

    for(Token currToken : tokens){
        currToken.debugPrint();
    }

    //Get iterators to begin and end of text
    std::vector<Token>::iterator begin = tokens.begin();
    std::vector<Token>::iterator end = tokens.end();

    std::cout << "\nCreating Parse Tree Class\n" << std::endl;
    ParseTreeClass Tree(tokens);
    std::cout << "\nRunning Parse Tree\n" << std::endl;
    op* parse_tree = Tree.program_parse(begin, end);
    
    Tree.print(parse_tree);

    //Print result of regex tree on text
	std::cout << "Result of executed regex:" << std::endl;
	Tree.execute(parse_tree, text);
	std::cout << std::endl;

    return 0;
}