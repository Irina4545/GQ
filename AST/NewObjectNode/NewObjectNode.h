#ifndef LANGGG_NEWOBJECTNODE_H
#define LANGGG_NEWOBJECTNODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../../Token/Token.h"

class NewObjectNode : public ExpressionNode {
private:
	Token token_name_object;
	Token token_type_object;
public:
	NewObjectNode(Token token_type, Token token_name);
	Token get_token_type();
	Token get_token_name();
};


#endif
