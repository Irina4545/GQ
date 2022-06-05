#include "RootClass.h"


std::string RootClass::get_type_class() {
	return type_class;
}

RootClass::RootClass(std::string str) {
	this->type_class = std::move(str);
	//std::cout << "root constr " << type_class << '\n';
}

RootClass::RootClass(RootClass &other) {
	this->type_class = other.type_class;
}
