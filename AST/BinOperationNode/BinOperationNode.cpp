//
// Created by sergei on 28.05.22.
//

#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(Token the_operator, ExpressionNode* leftNode, ExpressionNode* rightNode) {
	this->the_operator = the_operator;
	this->leftNode = leftNode;
	this->rightNode = rightNode;
	this->type_class = "BinOperationNode";
}

BinOperationNode::~BinOperationNode() {
	if (leftNode->get_type_class() == "VariableNode") {
		delete static_cast<VariableNode*>(leftNode);
	} else if (leftNode->get_type_class() == "NumberNode") {
		delete static_cast<NumberNode*>(leftNode);
	}

	if (rightNode->get_type_class() == "VariableNode") {
		delete static_cast<VariableNode*>(rightNode);
	} else if (rightNode->get_type_class() == "NumberNode") {
		delete static_cast<NumberNode*>(rightNode);
	}
}

ExpressionNode *BinOperationNode::get_left_node() {
	return leftNode;
}

ExpressionNode *BinOperationNode::get_right_node() {
	return rightNode;
}

Token BinOperationNode::get_token_operator() {
	return the_operator;
}
