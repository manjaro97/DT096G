#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include <iostream>

struct object {
	std::string::iterator lhs;
	std::string::iterator rhs;
	std::string::iterator end;
};

struct op {
	virtual object* eval(object* obj) = 0;
	virtual std::string id() = 0;
	std::vector<op*> operands;
};

struct program : op {
	object* eval(object* obj) override {
		//While we have not reached the end of the text
		while (obj->rhs != obj->end) {
			object* re = operands[0]->eval(obj);

			//If we got valid result back
			if (re) {
				return re;
			}

			//Move to next character
			obj->lhs = ++obj->rhs;
		}
		return nullptr;
	}

	std::string id() override {
		return "<program>";
	}
};

struct re : op {
	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<RE>";
	}
};

struct or_re : op {
	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<OR-RE>";
	}
};

struct simple_re : op {
	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<Simple-RE>";
	}
};

struct concatenation : op {
	object* eval(object* obj) override {
		//Save pointers to start of <concatenation> which is <basic-RE>
		std::string::iterator basic_begin = obj->lhs;
		obj->lhs = obj->rhs;

		//Evaluate <basic-RE>
		object* basic_re = operands[0]->eval(obj);

		//If <basic-RE> failed, return nullptr
		if (!basic_re) {
			obj->lhs = obj->rhs = basic_begin;	//Reset iterators
			return nullptr;
		}

		//Save pointers at start of <simple-RE>
		std::string::iterator simple_begin = basic_re->lhs;
		basic_re->lhs = basic_re->rhs;

		//Evaluate <simple-RE>
		object* simple_re = operands[1]->eval(basic_re);

		//If <simple-RE> failed, return nullptr
		if (!simple_re) {
			obj->lhs = obj->rhs = basic_begin;	//Reset iterators
			return nullptr;
		}

		//Add the result of <basic-RE> to <simple-RE> and return it as <concatenation>
		simple_re->lhs = basic_begin;
		return simple_re;
	}

	std::string id() override {
		return "<Concatenation>";
	}
};

struct basic_re : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<Basic_re>";
	}
};

struct group : op {

	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<group>";
	}
};

struct repetition : op {

	std::string _id; //Identifier

	object* eval(object* obj) override {
		
		//Check if we reached end of string
		if (obj->rhs == obj->end) {
			return nullptr;
		}
		
		if(*obj->rhs != *_id.begin() && *_id.begin() != '.'){
			//No Match, Return nullptr
			return nullptr;
		}

		while(*obj->rhs == *_id.begin() || *_id.begin() == '.')
		{
			//Check if we reached end of string
			if (obj->rhs == obj->end) {
				return obj;
			}
			
			//Match, iterate
			obj->rhs++;
		}
		
		//No Match, Return nullptr
		return obj;
	}

	std::string id() override {
		return "<repetition> (" + _id + ")*";
	}
};

struct counter : op {

	std::string _id; //Identifier
	int _nr;  //amount

	object* eval(object* obj) override {

		for (int iter = 0; iter < _nr; iter++)
		{
			//Check if we reached end of string
			if (obj->rhs == obj->end) {
				return nullptr;
			}

			//If not match
			if (*obj->rhs != *_id.begin() && *_id.begin() != '.') {
				return nullptr;
			}
			
			//Match, iterate
			obj->rhs++;
		}
		
		//Match, Return
		return obj;

	}

	std::string id() override {
		return "<counter> (" + _id + ")" + "{" + std::to_string(_nr) + "}";
	}

};

struct lowercase : op {

	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}
	
	std::string id() override {
		return "<lowercase>";
	}
};

struct output : op {

	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<output>";
	}
};

struct any : op {

	object* eval(object* obj) override {
		//Check if we reached end of string
		if (obj->rhs == obj->end) {
			return nullptr;
		}

		//Match, return character
		obj->rhs++;
		return obj;

	}

	std::string id() override {
		return "<Any>";
	}
};

struct character : op {

	std::string _id; //Identifier

	object* eval(object* obj) override {
		//Check if we reached end of string
		if (obj->rhs == obj->end) {
			return nullptr;
		}

		//If not match
		if (*obj->rhs != *_id.begin()) {
			return nullptr;
		}

		//Match, return character
		obj->rhs++;
		return obj;

	}

	std::string id() override {
		return "<character> (" + _id + ")";
	}
};


#endif