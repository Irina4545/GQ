#ifndef LANGGG_METHODCALLNODE_H
#define LANGGG_METHODCALLNODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../StatementsNode/StatementsNode.h"
#include "../../Token/Token.h"

class MethodCallNode : public ExpressionNode {
private:
	Token name_struct;
	Token name_method;
	ExpressionNode* p_parameters; // statement*
public:
	MethodCallNode(Token name_struct, Token name_method, ExpressionNode* p_parameters);
	Token get_name_struct();
	Token get_name_method();
	ExpressionNode* get_parameters();
	~MethodCallNode();
};


#endif
