//
// Created by sergei on 04.06.22.
//

#include "MethodCallNode.h"

MethodCallNode::MethodCallNode(Token name_struct, Token name_method,
							   ExpressionNode *p_parameters) {
	this->type_class = "MethodCallNode";
	this->name_method = name_method;
	this->name_struct = name_struct;
	this->p_parameters = p_parameters;

}

Token MethodCallNode::get_name_struct() {
	return name_struct;
}

Token MethodCallNode::get_name_method() {
	return name_method;
}

ExpressionNode *MethodCallNode::get_parameters() {
	return p_parameters;
}

MethodCallNode::~MethodCallNode() {
	delete static_cast<StatementsNode*>(p_parameters);
}

