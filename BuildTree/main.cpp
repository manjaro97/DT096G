//cd "c:\Users\Manjaro\Desktop\DT096G\BuildTree\" ; if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }

#include <iostream>
#include <string>
#include <vector>
#include "classes.h"




int main(){
    std::cout << "Hello World\n" << std::endl;
    
    std::string text = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "Waterloo";

    std::string::iterator begin = input.begin();
    std::string::iterator end = input.end();

    /*
    //Create a Parse Tree
    op* result = program_parse(begin, end);

    //Print regex tree
	std::cout << "Parse tree:" << std::endl;
	print(result, 0);
	std::cout << std::endl;*/


    return 0;
}
