#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../../Token/Token.h"

class VariableNode : public ExpressionNode {
private:
	Token variable;
public:
	VariableNode(Token variable);
	Token get_token();
};


#endif
