#ifndef CLASSES_H
#define CLASSES_H

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

};

struct counter : op {

};

struct lowercase : op {

};

struct output : op {

};

struct element : op {

};

struct digit : op {

};

struct any : op {

};

struct character : op {

};


#endif