#include "StatementsNode.h"

void StatementsNode::addNode(ExpressionNode* node) {
	this->code_strings.push_back(node);
	type_class = "StatementsNode";
}

StatementsNode::~StatementsNode() {
	for (int i = 0; i < code_strings.size(); i++) {
		if (code_strings[i]->get_type_class() == "VariableNode") {
			delete static_cast<VariableNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "NumberNode") {
			delete static_cast<NumberNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "PrintConsoleNode") {
			delete static_cast<PrintConsoleNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "BinOperationNode") {
			delete static_cast<BinOperationNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "IfNode") {
			delete static_cast<IfNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "While_Node") {
			delete static_cast<While_Node*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "BlockNode") {
			delete static_cast<BlockNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "StatementsNode") {
			delete static_cast<StatementsNode*>(code_strings[i]);
		} else if (code_strings[i]->get_type_class() == "NewObjectNode") {
			delete static_cast<NewObjectNode*>(code_strings[i]);
		}
	}
}

ExpressionNode* StatementsNode::get(int i) {
	return code_strings[i];
}

int StatementsNode::size() {
	return this->code_strings.size();
}
