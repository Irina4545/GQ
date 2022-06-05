//
// Created by sergei on 01.06.22.
//

#include "ElseNode.h"

ElseNode::ElseNode(ExpressionNode *block) {
	this->p_block = block;
	this->type_class = "ElseNode";
}

ExpressionNode *ElseNode::get_p_block() {
	return p_block;
}

ElseNode::~ElseNode() {
	delete static_cast<BlockNode*>(p_block);
}
