#ifndef PARSETREE_H
#define PARSETREE_H

#include "classes.h"
#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"

class ParseTreeClass{
    public:
        std::vector<simpleparser::Token> tokens;
        ParseTreeClass(std::vector<simpleparser::Token> t);
        op* program_parse(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* regExp(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* or_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* concatenation_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* simple_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* basic_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* group_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* repetition_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* counter_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* any_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);
        op* character_expr(std::vector<simpleparser::Token>::iterator& first, std::vector<simpleparser::Token>::iterator& last);

        //Prints parse tree
        void print(op* op, size_t i = 0);

        //Executes parsing of text with parsetree
        void execute(op* parse_tree, std::string source);
};

#endif