#include "While_Node.h"

While_Node::While_Node(PredicateNode *predicate, ExpressionNode *block) {
	this->p_predicate = predicate;
	this->p_block = block;
	this->type_class = "While_Node";
}

PredicateNode *While_Node::get_p_predicate() {
	return p_predicate;
}

ExpressionNode *While_Node::get_p_block() {
	return p_block;
}

While_Node::~While_Node() {
	delete p_predicate;
	delete static_cast<BlockNode*>(p_block);
}