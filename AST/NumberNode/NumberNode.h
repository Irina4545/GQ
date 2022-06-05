#ifndef IRA_LANG_NUMBERNODE_H
#define IRA_LANG_NUMBERNODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../../Token/Token.h"

class NumberNode : public ExpressionNode {
private:
	Token number;
public:
	NumberNode(Token number);
	Token get_token();
};


#endif
