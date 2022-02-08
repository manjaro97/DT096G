#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "parser.h"

// cd "c:\Users\Manjaro\Desktop\DT096G\Labb1\" ; if ($?) { g++ main.cpp parser.cpp -o main } ; if ($?) { .\main }

int main() {

	std::vector<char> text, input;

	std::cout << std::endl << "Reading from Input file..." << std::endl;
	std::string line;
  	std::ifstream myfile ("input.txt");
  	if (myfile.is_open())
  	{
  	  while ( std::getline (myfile,line) )
  	  {
		for(auto c: line){
			text.push_back(c);
		}
  	  }
  	  myfile.close();
  	}
  	else std::cout << "Unable to open file"; 

	std::cout << std::endl << "Parsing text: ";
	for(auto c : text){
		std::cout << c;
	}
	
	std::cout << std::endl << std::endl << "---Regex Parser Started---" << std::endl << std::endl;
	
	std::string inputStr, runProgram;

	while(true){
		std::cout << std::endl << "Write 1 to continue or 0 to exit: ";
		std::cin >> runProgram;

		if(runProgram != "1"){
			return 0;
		}

		std::cout << std::endl << "Write parse Expression: ";
		std::cin >> inputStr;
		input.clear();
		for(auto c: inputStr){
			input.push_back(c);
		}

		std::cout << parser();

	}

	return 0;
}