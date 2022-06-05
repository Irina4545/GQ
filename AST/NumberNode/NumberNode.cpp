//
// Created by sergei on 28.05.22.
//

#include "NumberNode.h"

NumberNode::NumberNode(Token number) {
	type_class = "NumberNode";
	this->number = number;
}

Token NumberNode::get_token() {
	return this->number;
}
