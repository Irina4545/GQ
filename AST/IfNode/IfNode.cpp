
#include "IfNode.h"

IfNode::IfNode(PredicateNode *predicate, ExpressionNode *block, ExpressionNode* block_next) {
	this->p_predicate = predicate;
	this->p_block = block;
	this->p_block_next = block_next;
	this->type_class = "IfNode";
}

PredicateNode *IfNode::get_p_predicate() {
	return p_predicate;
}

ExpressionNode *IfNode::get_p_block() {
	return p_block;
}

IfNode::~IfNode() {
	delete p_predicate;
	delete static_cast<BlockNode*>(p_block);

	if (p_block_next != nullptr && p_block_next->get_type_class() == "ElseNode") {
		delete static_cast<ElseNode*>(p_block_next);
	}
}


