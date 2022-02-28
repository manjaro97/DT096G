#include "parsetree.h"

ParseTreeClass::ParseTreeClass(std::vector<simpleparser::Token> t){
    tokens = t;
}

op* ParseTreeClass::program_parse(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    std::cout << "\nInside Program Parse\n" << std::endl;
    
    //If the regex is empty
	if (first == last) {
		return nullptr;
	}
	program* expr = new program;
	op* program_parse_child = regExp(first, last);
	expr->operands.push_back(program_parse_child);
	return expr;
}

op* ParseTreeClass::regExp(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    std::cout << "\nInside Reg Exp\n" << std::endl;

    //Create empty child node
	op* regExp_child = nullptr;

	op* program_parse_child = simple_expr(first, last);

	re* expr = new re;
	expr->operands.push_back(regExp_child);
	return expr;
}

op* ParseTreeClass::simple_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    std::vector<simpleparser::Token>::iterator start = first;

    //Create empty child node
	op* simple_expr_child = nullptr;

	simple_expr_child = basic_expr(first, last);

    //If basic_expr did not capture the whole expression, Try for concatenation
    if(first != last){
        first = start;
        simple_expr_child = concatenation_expr(first, last);
    }

    //If neither
    if(!simple_expr_child){
        first = start;
        return nullptr;
    }

	simple_re* expr = new simple_re;
	expr->operands.push_back(simple_expr_child);
	return expr;
}

op* ParseTreeClass::basic_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    //Create empty child node
	op* basic_expr_child = nullptr;

	//Check if <simple-RE>
	if (!basic_expr_child) {
	    basic_expr_child = any_expr(first, last);
	}

    if (!basic_expr_child) {
	    basic_expr_child = character_expr(first, last);
	}

	basic_re* expr = new basic_re;
	expr->operands.push_back(basic_expr_child);
	return expr;
}

op* ParseTreeClass::concatenation_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    std::vector<simpleparser::Token>::iterator start = first;

    //Create empty child node
	op* concatenation_expr_child_one = nullptr;
	op* concatenation_expr_child_two = nullptr;

    concatenation_expr_child_one = basic_expr(first, last);
    if(!concatenation_expr_child_one){
        first = start;
        return nullptr;
    }

    concatenation_expr_child_two = simple_expr(first, last);
    if(!concatenation_expr_child_two){
        first = start;
        return nullptr;
    }

	concatenation* expr = new concatenation;
	expr->operands.push_back(concatenation_expr_child_one);
	expr->operands.push_back(concatenation_expr_child_two);
	return expr;
}

op* ParseTreeClass::any_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	    
    //Get token
	simpleparser::Token thisToken = *first;

	//If token is <any>
	if(simpleparser::sTokenTypeStrings[thisToken.mType] == "ANY_SYMBOL"){
		any* expr = new any;
        first++;
        std::cout << "Found: " << thisToken.mText << std::endl;
		return expr;
	}

	//If token is not <any>
	return nullptr;
};

op* ParseTreeClass::character_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
    
    //Get token
	simpleparser::Token thisToken = *first;

	//If token is <character>
	if(simpleparser::sTokenTypeStrings[thisToken.mType] == "CHARACTER"){
		character* expr = new character;
        expr->_id.append(thisToken.mText);
        first++;
        std::cout << "Found: " << thisToken.mText << std::endl;
		return expr;
	}

	//If token is not <character>
	return nullptr;
};