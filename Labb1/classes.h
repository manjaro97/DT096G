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
	virtual std::string id() = 0;
	std::vector<op*> operands;
};

struct program : op {
	
	std::string id() override {
		return "<program>";
	}
};

struct re : op {

	std::string id() override {
		return "<RE>";
	}
};

struct or_re : op {

	std::string id() override {
		return "<OR-RE>";
	}
};

struct simple_re : op {

	std::string id() override {
		return "<Simple-RE>";
	}
};

struct concatenation : op {

	std::string id() override {
		return "<Concatenation>";
	}
};

struct basic_re : op {

	std::string id() override {
		return "<Basic_re>";
	}
};

struct group : op {

	std::string id() override {
		return "<group>";
	}
};

struct repetition : op {

	std::string _id; //Identifier

	std::string id() override {
		return "<repetition> (" + _id + ")*";
	}
};

struct counter : op {

	std::string _id; //Identifier
	int _nr;  //amount

	std::string id() override {
		return "<counter> (" + _id + ")" + "{" + std::to_string(_nr) + "}";
	}

};

struct lowercase : op {
	
	std::string id() override {
		return "<lowercase>";
	}
};

struct output : op {

	std::string id() override {
		return "<output>";
	}
};

struct element : op {

	std::string id() override {
		return "<Element>";
	}
};

struct digit : op {

	int _nr;  //digit

	std::string id() override {
		return "<Digit> (" + std::to_string(_nr) + ")";
	}
};

struct any : op {

	std::string id() override {
		return "<Any>";
	}
};

struct character : op {

	std::string _id; //Identifier

	std::string id() override {
		return "<character> (" + _id + ")";
	}
};


#endif