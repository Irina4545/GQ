//
// Created by sergei on 29.05.22.
//

#ifndef PREDICATENODE_H
#define PREDICATENODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../NumberNode/NumberNode.h"
#include "../VariableNode/VariableNode.h"
#include "../../Token/Token.h"

class PredicateNode : public ExpressionNode {
private:
	ExpressionNode* left_node;
	ExpressionNode* right_node;
	Token conditional_operator;
public:
	PredicateNode(Token conditional_operator, ExpressionNode* left_node, ExpressionNode* right_node);
	ExpressionNode* get_left_node();
	ExpressionNode* get_right_node();
	Token get_token_operator();
	~PredicateNode();
};


#endif
