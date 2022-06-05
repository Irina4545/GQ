#ifndef BLOCKNODE_H
#define BLOCKNODE_H

#include "../IfNode/IfNode.h"
#include "../ExpressionNode/ExpressionNode.h"
#include "../VariableNode/VariableNode.h"
#include "../NumberNode/NumberNode.h"
#include "../BinOperationNode/BinOperationNode.h"
#include "../PrintConsoleNode/PrintConsoleNode.h"
#include "../NewObjectNode/NewObjectNode.h"
#include <vector>


class BlockNode : public ExpressionNode {
private:
	std::vector<ExpressionNode*> all_block_nodes;
public:
	BlockNode();
	void add_node(ExpressionNode*);
	ExpressionNode* get(int i);
	int size();
	~BlockNode();
};


#endif
