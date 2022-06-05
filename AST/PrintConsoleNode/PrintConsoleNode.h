//
// Created by sergei on 28.05.22.
//

#ifndef PRINTCONSOLENODE_H
#define PRINTCONSOLENODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../VariableNode/VariableNode.h"
#include "../MethodCallNode/MethodCallNode.h"
#include "../NumberNode/NumberNode.h"
#include "../../Token/Token.h"

class PrintConsoleNode : public ExpressionNode {
private:
	Token the_operator;
	ExpressionNode* operand;
public:
	PrintConsoleNode(Token the_operation, ExpressionNode* operand);
	ExpressionNode* get_operand();
	~PrintConsoleNode();
};


#endif
