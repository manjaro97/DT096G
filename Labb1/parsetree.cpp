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

	regExp_child = simple_expr(first, last);

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

op* ParseTreeClass::basic_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
    //Create empty child node
	op* basic_expr_child = nullptr;

	//Check if <basic-RE>
	if (!basic_expr_child) {
	    basic_expr_child = group_expr(first, last);
	}

	if (!basic_expr_child) {
	    basic_expr_child = repetition_expr(first, last);
	}

	if (!basic_expr_child) {
	    basic_expr_child = counter_expr(first, last);
	}

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

op* ParseTreeClass::group_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
	//Get token
	simpleparser::Token thisToken = *first;

	//Declaring iterators
	std::vector<simpleparser::Token>::iterator GroupStart = first;
	std::vector<simpleparser::Token>::iterator GroupStop = last;

    //Create empty child node
	op* group_expr_child = nullptr;

	bool foundGroup = false;

	if(simpleparser::sTokenTypeStrings[thisToken.mType] == "LEFT_PARANTHESES"){
		std::cout << "\nFound: \"(\"\n";
		first++;
		GroupStart = first;

		int checkLeftParanthesis = 0;

		bool breakLoop = false;

		while(!breakLoop){
			thisToken = *first;
			std::cout << "lol: " << thisToken.mText << std::endl;

			if(simpleparser::sTokenTypeStrings[thisToken.mType] == "LEFT_PARANTHESES"){
				checkLeftParanthesis++;
			}
			else if(checkLeftParanthesis == 0 && simpleparser::sTokenTypeStrings[thisToken.mType] == "RIGHT_PARANTHESES"){
				std::cout << "\nFound: \")\"\n";
				GroupStop = first;
				foundGroup = true;
				breakLoop = true;
			}
			else if(simpleparser::sTokenTypeStrings[thisToken.mType] == "RIGHT_PARANTHESES"){
				checkLeftParanthesis--;
			}
			else if(first == last){
				std::cout << "--MISSING RIGHT PARANTHESIS--";
				breakLoop = true;
			}

			//if(!breakLoop){
			first++;
			//}
		}
	}
	else{
		return nullptr;
	}

	if (foundGroup) {
	    group_expr_child = regExp(GroupStart, GroupStop);
	}

	std::cout << "\n---------END OF GROUP---------\n";

	group* expr = new group;
	expr->operands.push_back(group_expr_child);
	return expr;
}

op* ParseTreeClass::repetition_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
	//Get token
	simpleparser::Token thisToken = *first;

	if(simpleparser::sTokenTypeStrings[thisToken.mType] == "REPETITION_VALUE"){
		std::cout << "\nFound Repeating: " << thisToken.mText << "\n";
		repetition* expr = new repetition;
        expr->_id.append(thisToken.mText);
        first+=2;
		return expr;
	}

	//If token is not <repetition>
	return nullptr;
	
}

op* ParseTreeClass::counter_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last) {
	
	//Get token
	simpleparser::Token thisToken = *first;

	if(simpleparser::sTokenTypeStrings[thisToken.mType] == "AMOUNT_VALUE"){
		std::cout << "\nFound Counter of: " << thisToken.mText << " with amount: ";
		counter* expr = new counter;
        expr->_id.append(thisToken.mText);
        first+=2;
		thisToken = *first;
		expr->_nr = std::stoi(thisToken.mText);
		first+=2;
		std::cout << thisToken.mText<< "\n";
		return expr;
	}

	//If token is not <counter>
	return nullptr;
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

//Print parse tree
void ParseTreeClass::print(op* op, size_t i) {
	
	//Prints space for indentation
	i++;
	for (size_t j = 0; j < i; j++) {
		std::cout << " |";
	}
	//Print class name
	std::cout << op->id() << " ";
	std::cout << std::endl;

	//Iterate into class operands
	for (size_t childNode = 0; childNode < op->operands.size(); childNode++) {
		print(op->operands[childNode], i);
	}
}

//Executes parse tree
void ParseTreeClass::execute(op* parse_tree, std::string source) {
	//Create new object of source string
	object* obj = new object;
	obj->lhs = source.begin();
	obj->rhs = source.begin();
	obj->end = source.end();

	//Evaluate parse tree on source string
	object* parse = parse_tree->eval(obj);

	//If we got a valid parse, print it
	if (parse != nullptr) {
		while (parse->lhs != parse->rhs) {
			std::cout << *parse->lhs;
			parse->lhs++;
		}
		std::cout << std::endl;
		std::cout << std::endl << "EXIT_SUCCESS" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cerr << std::endl << "EXIT_FAILURE" << std::endl;
	}
}