#include "IntClass.h"

IntClass::IntClass(std::string str_num) : RootClass(std::string("IntClass")) {
	//this->type_class = "IntClass";
	this->str_num = str_num;
	this->num = 0;

	if (str_num[0] == '-') {
		for (int i = 1; i < str_num.size(); i++) {
			num *= 10;
			num -= str_num[i] - '0';
		}
	} else {
		num = to_int(str_num);
	}
}

int IntClass::get_num() {
	return this->num;
}

std::string IntClass::get_str_num() {
	return str_num;
}

int IntClass::to_int(std::string str_num) {
	int num1 = 0;

	if (str_num[0] == '-') {
		for (int i = 1; i < str_num.size(); i++) {
			num1 *= 10;
			num1 -= str_num[i] - '0';
		}
	} else {
		for (int i = 0; i < str_num.size(); i++) {
			num1 *= 10;
			num1 += str_num[i] - '0';
		}
	}
	return num1;
}

IntClass::IntClass(int num) : RootClass(std::string("IntClass")) {
	//this->type_class = "IntClass";
	str_num = std::to_string(num);
	this->num = num;
}

IntClass::IntClass(IntClass &other_obj) : RootClass("IntClass"){
	this->num = other_obj.num;
	this->str_num = other_obj.str_num;
}

std::ostream& operator<<(std::ostream &os, IntClass& num) {
	os << num.get_num();
	return os;
}