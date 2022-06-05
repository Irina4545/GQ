//
// Created by sergei on 04.06.22.
//

#include "NewObjectNode.h"

NewObjectNode::NewObjectNode(Token token_type, Token token_name) {
	this->type_class = "NewObjectNode";
	this->token_name_object = token_name;
	this->token_type_object = token_type;
}

Token NewObjectNode::get_token_type() {
	return token_type_object;
}

Token NewObjectNode::get_token_name() {
	return token_name_object;
}
