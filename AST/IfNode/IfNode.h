#ifndef IFNODE_H
#define IFNODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../PredicateNode/PredicateNode.h"
#include "../BinOperationNode/BinOperationNode.h"
#include "../BlockNode/BlockNode.h"
#include "../StatementsNode/StatementsNode.h"
#include "../ElseNode/ElseNode.h"

class IfNode : public ExpressionNode {
private:

	PredicateNode* p_predicate;
	ExpressionNode* p_block;
	ExpressionNode* p_block_next;

public:

	IfNode(PredicateNode* predicate, ExpressionNode* block, ExpressionNode* block_next);
	ExpressionNode* get_p_block();
	PredicateNode* get_p_predicate();
	~IfNode();

};


#endif
