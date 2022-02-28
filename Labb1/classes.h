#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>

struct iter {
	std::string::iterator lhs;
	std::string::iterator rhs;
};

struct object {
	std::string::iterator lhs;
	std::string::iterator rhs;
	std::string::iterator end;
	size_t captured = 0;
	std::vector<iter> cap;
};

struct op {
	
	std::vector<op*> operands;
};

struct program : op {
	
};

struct re : op {

};

struct or_re : op {

};

struct simple_re : op {

};

struct concatenation : op {

};

struct basic_re : op {

};

struct group : op {

};

struct repetition : op {

std::string _id; //Identifier

};

struct counter : op {

std::string _id; //Identifier
int _nr;  //amount

};

struct lowercase : op {

};

struct output : op {

};

struct element : op {

};

struct digit : op {

int _nr;  //digit

};

struct any : op {

};

struct character : op {

std::string _id; //Identifier

};


#endif