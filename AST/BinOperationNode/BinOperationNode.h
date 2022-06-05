#ifndef BINOPERATIONNODE_H
#define BINOPERATIONNODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../VariableNode/VariableNode.h"
#include "../NumberNode/NumberNode.h"
#include "../../Token/Token.h"

class BinOperationNode : public ExpressionNode {
private:
	Token the_operator;
	ExpressionNode* leftNode;
	ExpressionNode* rightNode;
public:
	BinOperationNode(Token the_operator, ExpressionNode* leftNode, ExpressionNode* rightNode);
	ExpressionNode* get_left_node();
	ExpressionNode* get_right_node();
	Token get_token_operator();
	~BinOperationNode();
};


#endif
