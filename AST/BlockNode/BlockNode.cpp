//
// Created by sergei on 29.05.22.
//

#include "BlockNode.h"

BlockNode::BlockNode() {
	this->type_class = "BlockNode";
}

void BlockNode::add_node(ExpressionNode* node) {
	all_block_nodes.push_back(node);
}

BlockNode::~BlockNode() {
	for (int i = 0; i < all_block_nodes.size(); i++) {
		if (all_block_nodes[i]->get_type_class() == "VariableNode") {
			delete static_cast<VariableNode*>(all_block_nodes[i]);
		} else if (all_block_nodes[i]->get_type_class() == "NumberNode") {
			delete static_cast<NumberNode*>(all_block_nodes[i]);
		} else if (all_block_nodes[i]->get_type_class() == "PrintConsoleNode") {
			delete static_cast<PrintConsoleNode*>(all_block_nodes[i]);
		} else if (all_block_nodes[i]->get_type_class() == "BinOperationNode") {
			delete static_cast<BinOperationNode*>(all_block_nodes[i]);
		} else if (all_block_nodes[i]->get_type_class() == "IfNode") {
			delete static_cast<IfNode*>(all_block_nodes[i]);
		} else if (all_block_nodes[i]->get_type_class() == "NewObjectNode") {
			delete static_cast<NewObjectNode*>(all_block_nodes[i]);
		}
	}
}

ExpressionNode *BlockNode::get(int i) {
	return all_block_nodes[i];
}

int BlockNode::size() {
	return all_block_nodes.size();
}




