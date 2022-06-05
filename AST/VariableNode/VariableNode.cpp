#include "VariableNode.h"

VariableNode::VariableNode(Token variable) {
	this->variable = variable;
	type_class = "VariableNode";
}

Token VariableNode::get_token() {
	return variable;
}
