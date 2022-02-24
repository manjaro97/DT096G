//cd "c:\Users\Manjaro\Desktop\DT096G\BuildTree\" ; if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }

#include <iostream>
#include <string>
#include <vector>
#include "classes.h"

op* program_parse(std::string::iterator& first, std::string::iterator& last);
op* regExp(std::string::iterator& first, std::string::iterator& last);
op* simple_regExp(std::string::iterator& first, std::string::iterator& last);
void print(op* op, size_t i);


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

op* program_parse(std::string::iterator& first, std::string::iterator& last) {
	//If the regex is empty
	if (first == last) {
		return nullptr;
	}
	program* expr = new program;
	op* program_parse_child = regExp(first, last);
	expr->operands.push_back(program_parse_child);
	return expr;
}
op* regExp(std::string::iterator& first, std::string::iterator& last) {
	//Create empty child node
	op* regExp_child = nullptr;

	//TODO substitute rule
	//op* substitute_or_simple = substitute_expr(first, last);

	//Check if <simple-RE>
	if (!regExp_child) {
	    regExp_child = simple_regExp(first, last);
	}

	re* expr = new re;
	expr->operands.push_back(regExp_child);
	return expr;
}

op* simple_regExp(std::string::iterator& first, std::string::iterator& last) {
	//Save iterator pointing at first
	std::string::iterator start = first;
    
    //Create empty child node
	op* simple_regExp_child = nullptr;

    //Check if basic-RE first
	simple_regExp_child = basic_regExp(first, last);

	//If <basic-RE> did not enclose the whole expression
	//Try for <concatenation>
	if (first != last) {
		first = start;
		simple_regExp_child = concatenation_regExp(first, last);
	}

    //If neither
	if (!simple_regExp_child) {
		first = start;
		return nullptr;
	}

	simple_re* expr = new simple_re;
	expr->operands.push_back(simple_regExp_child);
	return expr;
}

op* basic_regExp(std::string::iterator& first, std::string::iterator& last) {
	//Save iterator pointing at first
	std::string::iterator start = first;
    
    //Create empty child node
	op* simple_regExp_child = nullptr;

    

	re* expr = new re;
	expr->operands.push_back(simple_regExp_child);
	return expr;
}

op* concatenation_regExp(std::string::iterator& first, std::string::iterator& last) {
	//Save iterator pointing at first
	std::string::iterator start = first;
    
    //Create empty child node
	op* simple_regExp_child = nullptr;


	re* expr = new re;
	expr->operands.push_back(simple_regExp_child);
	return expr;
}

//Print parse tree
void print(op* op, size_t i) {

	//Prints space for indentation
	i++;
	for (size_t j = 0; j < i; j++) {
		std::cout << " |";
	}

	//Print class name
	std::cout << op->id() << " ";
	//std::cout << op->operands.size();
	std::cout << std::endl;

	//Iterate into class operands
	for (size_t childNode = 0; childNode < op->operands.size(); childNode++) {
		print(op->operands[childNode], i);
	}
}