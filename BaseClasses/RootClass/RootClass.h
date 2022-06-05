#ifndef ROOTCLASS_H
#define ROOTCLASS_H

#include "../../AST/ExpressionNode/ExpressionNode.h"
#include "../../AST/NumberNode/NumberNode.h"
#include "../../AST/VariableNode/VariableNode.h"
#include "string"
#include <iostream>

class RootClass {
protected:
	std::string type_class;
public:
	RootClass(RootClass& other);
	RootClass(std::string str);
	std::string get_type_class();
};


#endif
