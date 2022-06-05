#ifndef WHILE_NODE_H
#define WHILE_NODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../PredicateNode/PredicateNode.h"
#include "../BinOperationNode/BinOperationNode.h"
#include "../BlockNode/BlockNode.h"
#include "../StatementsNode/StatementsNode.h"

class While_Node : public  ExpressionNode {
private:

	PredicateNode* p_predicate;
	ExpressionNode* p_block;

public:

	While_Node(PredicateNode* predicate, ExpressionNode* block);
	ExpressionNode* get_p_block();
	PredicateNode* get_p_predicate();
	~While_Node();

};


#endif
