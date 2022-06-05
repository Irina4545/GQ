//
// Created by sergei on 29.05.22.
//

#include "PredicateNode.h"

PredicateNode::PredicateNode(Token conditional_operator, ExpressionNode *left_node, ExpressionNode *right_node) {
	this->type_class = "PredicateNode";
	this->conditional_operator = conditional_operator;
	this->left_node = left_node;
	this->right_node = right_node;
}

PredicateNode::~PredicateNode() {
	if (left_node->get_type_class() == "NumberNode") {
		delete static_cast<NumberNode*>(left_node);
	} else if (left_node->get_type_class() == "VariableNode") {
		delete static_cast<VariableNode*>(left_node);
	}

	if (right_node->get_type_class() == "NumberNode") {
		delete static_cast<NumberNode*>(right_node);
	} else if (right_node->get_type_class() == "VariableNode") {
		delete static_cast<VariableNode*>(right_node);
	}

}

ExpressionNode *PredicateNode::get_left_node() {
	return left_node;
}

ExpressionNode *PredicateNode::get_right_node() {
	return right_node;
}

Token PredicateNode::get_token_operator() {
	return conditional_operator;
}
