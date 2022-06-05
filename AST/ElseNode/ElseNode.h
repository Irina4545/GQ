//
// Created by sergei on 01.06.22.
//

#ifndef ELSENODE_H
#define ELSENODE_H

#include "../ExpressionNode/ExpressionNode.h"
#include "../PredicateNode/PredicateNode.h"
#include "../BinOperationNode/BinOperationNode.h"
#include "../BlockNode/BlockNode.h"
#include "../StatementsNode/StatementsNode.h"

class ElseNode : public ExpressionNode {
private:
	ExpressionNode* p_block;
public:
	ElseNode(ExpressionNode* block);
	ExpressionNode* get_p_block();
	PredicateNode* get_p_predicate();
	~ElseNode();
};


#endif
