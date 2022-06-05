#include "PrintConsoleNode.h"

PrintConsoleNode::PrintConsoleNode(Token the_operation, ExpressionNode *operand) {
	this->the_operator = the_operation;
	this->operand = operand;
	type_class = "PrintConsoleNode";
}

PrintConsoleNode::~PrintConsoleNode() {
	if (operand->get_type_class() == "VariableNode") {
		delete static_cast<VariableNode *>(operand);
	} else if (operand->get_type_class() == "NumberNode") {
		delete static_cast<NumberNode *>(operand);
	} else if (operand->get_type_class() == "MethodCallNode") {
		delete static_cast<MethodCallNode *>(operand);
	}

}

ExpressionNode *PrintConsoleNode::get_operand() {
	return operand;
}
