#include "Parser.h"

Parser::Parser(std::list<Token> &tokens) {
	this->p_tokens = &tokens;
}

bool Parser::go() {
	std::list<Token>::iterator it = p_tokens->begin();

	returned_value = nullptr;

	return lang(it);
}

bool Parser::step(std::list<Token>::iterator &it) {
	++it;
	if (it == p_tokens->end()) {
		return false;
	}
	return true;
}

bool Parser::lang(std::list<Token>::iterator &it) {
	// если зашли в expr или в decribe хоть раз то будет true
	bool result = true;

	while (it != p_tokens->end()) {
		if (!result) {
			throw std::string("неизвестная конструкция, строка ") + std::to_string(it->get_num_line());
		}

		result = false;

		while (expr(it)) {
			result = true;
		}
	}

	return true;
}

bool Parser::expr(std::list<Token>::iterator &it) {
	if (!EXPR_IF_ELSE(it)) {
		if (!EXPR_CYCLE(it)) {
			if (!EXPR_PRINT(it)) {
				if (!EXPR_ASSIGN(it)) {
					if (!LIB_CREATE(it)) {
						if (!METHOD_CALL(it)) {
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

bool Parser::EXPR_PRINT(std::list<Token>::iterator & it) {
	if (it->get_type() != "PRINT") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!METHOD_CALL(it)) {
		if (!VALUE(it)) {
			return false;
		}
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "R_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	step(it);

	return true;
}

bool Parser::EXPR_CYCLE(std::list<Token>::iterator &it) {
	if (!EXPR_WHILE(it)) {
		return false;
	}

	return true;
}

bool Parser::EXPR_IF_ELSE(std::list<Token>::iterator &it) {
	if (it->get_type() != "IF") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXPR_PREDICATE(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACER") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXEC_BLOCK(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACER") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		return true;
	}

	while (EXPR_ELIF(it));

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	EXPR_ELSE(it);

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	return true;
}

bool Parser::EXPR_WHILE(std::list<Token>::iterator &it) {
	if (it->get_type() != "WHILE") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXPR_PREDICATE(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACER") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXEC_BLOCK(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACER") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	step(it);

	return false;
}

bool Parser::EXPR_ASSIGN(std::list<Token>::iterator &it) {
	if (it->get_type() != "VAR") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "ASSIGN_OP") {
		--it;
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!VALUE(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it != p_tokens->end()) {
		while (it->get_type() == "OP") {
			if (!step(it)) {
				throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
			}

			if (!VALUE(it)) {
				throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
			}
		}
	}

	return true;
}

bool Parser::EXPR_ELIF(std::list<Token>::iterator &it) {
	if (it->get_type() != "ELIF") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXPR_PREDICATE(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACKET") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACER") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXEC_BLOCK(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACER") {
		return false;
	}

	step(it);

	return true;
}

bool Parser::EXPR_ELSE(std::list<Token>::iterator &it) {
	if (it->get_type() != "ELSE") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACER") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!EXEC_BLOCK(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "R_BRACER") {
		return false;
	}

	step(it);

	return true;
}

bool Parser::LIB_CREATE(std::list<Token>::iterator &it) {
	if (it->get_type() != "LIB") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "SPACE_NAME") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "LIST") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "VAR") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	step(it);

	return true;
}

bool Parser::METHOD_CALL(std::list<Token>::iterator &it) {
	if (it->get_type() != "VAR") {
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "DOT") {
		--it;
		return false;
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "VAR") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	PARAMETERS(it);

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	if (it->get_type() != "R_BRACKET") {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	step(it);

	return true;
}

bool Parser::PARAMETERS(std::list<Token>::iterator &it) {
	if (!VALUE(it)) {
		return true;
	}

	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	while (it->get_type() == "ENUM_SEPARATE") {
		if (!step(it)) {
			return false;
		}

		if (!VALUE(it)) {
			return false;
		}

		if (it == p_tokens->end()) {
			throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
		}
	}

	return true;
}


bool Parser::VALUE(std::list<Token>::iterator &it) {
	FORMULA(it);
	return true;
}

bool Parser::FORMULA(std::list<Token>::iterator &it) {
	if (!FORMULA2(it)) {
		if (!FORMULA3(it)) {
			return false;
		}
	}

	return true;
}

bool Parser::FORMULA2(std::list<Token>::iterator &it) {
	if (it->get_type() != "VAR") {
		if (it->get_type() != "DIGIT") {
			if (it->get_type() != "STRING") {
				return false;
			}
		}
	}

	if (!step(it)) {
		throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
	}

	while (it->get_type() == "OP") {
		if (!step(it)) {
			throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
		}

		if (!FORMULA2(it)) {
			if (!FORMULA3(it)) {
				return false;
			}
		}
	}

	return true;
}

bool Parser::FORMULA3(std::list<Token>::iterator &it) {
	if (it == p_tokens->end()) {
		throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
	}

	if (it->get_type() != "L_BRACKET") {
		return false;
	}

	if (!step(it)) {
		return false;
	}

	FORMULA(it);

	if (it == p_tokens->end()) {
		return false;
	}

	if (it->get_type() != "R_BRACKET") {
		return false;
	}

	step(it);

	return true;
}

bool Parser::EXEC_BLOCK(std::list<Token>::iterator &it) {
	while (expr(it));
	return true;
}

bool Parser::EXPR_PREDICATE(std::list<Token>::iterator &it) {
	if (it->get_type() != "BOOL") {
		VALUE(it);

		if (it == p_tokens->end()) {
			throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
		}

		if (it->get_type() == "CONDITIONAL_OP") {
			if (it == p_tokens->end()) {
				throw std::string("незаконченная конструкция: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
			}

			if (!step(it)) {
				throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
			}

			if (!VALUE(it)) {
				throw std::string("незаконченная конструкция, строка ") + std::to_string(it->get_num_line());
			}
		}

		return true;
	}

	step(it);

	return true;
}




void Parser::parse_code() {
	std::list<Token>::iterator it = p_tokens->begin();
	root = new StatementsNode();

	while (it != p_tokens->end()) {
		root->addNode(parse_expression(it));
	}
}

ExpressionNode *Parser::parse_expression(std::list<Token>::iterator& it) {
	if (it->get_type() == "VAR") {
		ExpressionNode* left_node = new VariableNode(*it);
		Token token_left_node(*it);
		++it;

		if (it->get_type() == "DOT") { // parse method_call
			Token name_struct = token_left_node;
			++it;
			Token name_method(*it);
			++it;
			ExpressionNode* parameters = parse_parameters(it);
			return new MethodCallNode(name_struct, name_method, parameters);
		} else {
			Token the_operator(*it);
			if (the_operator.get_type() == "ASSIGN_OP" || the_operator.get_type() == "OP") {
				++it;
				ExpressionNode* right_node = parse_formula(it);
				ExpressionNode* bin_node = new BinOperationNode(the_operator, left_node, right_node);
				return bin_node;
			} else {
				return  left_node;
			}
		}
	} else if (it->get_type() == "IF") {
		return parse_if(it);
	} else if (it->get_type() == "DIGIT") {
		NumberNode* result = new NumberNode(*it);
		++it;
		return result;
	} else if (it->get_type() == "PRINT") {
		return parse_print(it);
	} else if (it->get_type() == "WHILE") {
		return parse_while(it);
	} else if (it->get_type() == "R_BRACER" || it->get_type() == "R_BRACKET") {
		++it;
		return parse_expression(it);
	} else if (it->get_type() == "LIB") {
		++it;
		++it;

		if (it->get_type() == "LIST") {
			return parse_list(it);
		}
	} else {
		return nullptr;
	}
}

ExpressionNode* Parser::parse_list(std::list<Token>::iterator &it) {
	Token type(*it);
	++it;
	Token name(*it);
	++it;
	return new NewObjectNode(type, name);
}

ExpressionNode* Parser::parse_if(std::list<Token>::iterator &it) {
	Token the_operator = *it;
	++it; // скобка
	++it; // внутри скобок

	PredicateNode* p_predicate = parse_conditional(it);
	BlockNode* p_block = parse_block(it);

	IfNode* p_if_node = new IfNode(p_predicate, p_block, nullptr);

	return p_if_node;
}

BlockNode* Parser::parse_block(std::list<Token>::iterator &it) {
	++it;
	BlockNode* p_block_node = new BlockNode();
	ExpressionNode* p_temp_expression;

	while (true) {
		p_temp_expression = parse_expression(it);

		if (p_temp_expression == nullptr) {
			break;
		}

		p_block_node->add_node(p_temp_expression);
	}

	//++it;

	return p_block_node;
}

PredicateNode* Parser::parse_conditional(std::list<Token>::iterator &it) {
	ExpressionNode *left_node = parse_variable(it);
	Token the_operator = *it;
	++it;
	ExpressionNode *right_node = parse_variable(it) ;
	++it;

	return new PredicateNode(the_operator, left_node, right_node);
}

ExpressionNode* Parser::parse_while(std::list<Token>::iterator &it) {
	Token the_operator = *it;
	++it; // скобка
	++it; // внутри скобок

	PredicateNode* p_predicate = parse_conditional(it);
	BlockNode* p_block = parse_block(it);

	While_Node* p_while = new While_Node(p_predicate, p_block);

	return p_while;

	return nullptr;
}

ExpressionNode *Parser::parse_variable(std::list<Token>::iterator &it) {
	Token token = *it;

	if (it->get_type() == "DIGIT") {
		++it;
		return new NumberNode(token);
	} else if (it->get_type() == "VAR") {
		++it;
		return new VariableNode(token);
	}

	throw std::string("Ошибка: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
}

ExpressionNode *Parser::parse_formula(std::list<Token>::iterator &it) {
	ExpressionNode *left_node = parse_variable(it);
	Token the_operator(*it);

	if (the_operator.get_type() == "OP") {
		++it;
		ExpressionNode *right_node = parse_variable(it);
		left_node = new BinOperationNode(the_operator, left_node, right_node);
		the_operator = *it;
	}

	return left_node;
}

ExpressionNode *Parser::parse_print(std::list<Token>::iterator &it) {
	Token the_operator = *it;
	if (the_operator.get_type() == "PRINT") {
		++it; // скобка
		++it; // аргумент
		PrintConsoleNode* result = new PrintConsoleNode(the_operator, parse_expression(it));
		++it; // за скобкой
		return result;
	}

	throw std::string("Ошибка: ") + std::string("строка ") + std::to_string((--it)->get_num_line());
}

ExpressionNode* Parser::run(ExpressionNode *node) {
	if (node->get_type_class() == "NumberNode") {
		return node;
	}

	if (node->get_type_class() == "BinOperationNode") {
		BinOperationNode* p_bin_operation_node = static_cast<BinOperationNode*>(node);

		if (p_bin_operation_node->get_token_operator().get_type() == "ASSIGN_OP") {
			VariableNode* p_variable_node_left = static_cast<VariableNode*>(p_bin_operation_node->get_left_node());

			if (p_bin_operation_node->get_right_node()->get_type_class() == "BinOperationNode") {
				auto it = all_var.find(p_variable_node_left->get_token().get_value());
				if (it != all_var.end()) {

					delete it->second;
					int a = count(p_bin_operation_node->get_right_node());
					it->second = new IntClass(a);
					//std::cout << a << " = a\n";
				} else {
					int a = count(p_bin_operation_node->get_right_node());
					all_var.emplace(p_variable_node_left->get_token().get_value(), new IntClass(a));
					//std::cout << a << " = a\n";
				}

				return nullptr;
			} else {
				auto it = all_var.find(p_variable_node_left->get_token().get_value());
				if (it == all_var.end()) {
					if (p_bin_operation_node->get_right_node()->get_type_class() == "VariableNode") {
						VariableNode* p_variable_node_right = static_cast<VariableNode*>(p_bin_operation_node->get_right_node());
						auto it1 = all_var.find(p_variable_node_right->get_token().get_value());
						if (it1 != all_var.end()) {
							all_var.emplace(p_variable_node_left->get_token().get_value(), new IntClass((static_cast<IntClass*>(it1->second))->get_str_num()));
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_bin_operation_node->get_right_node());
						all_var.emplace(p_variable_node_left->get_token().get_value(), new IntClass(p_number_node->get_token().get_value()));
					}
				} else {
					delete it->second;
					if (p_bin_operation_node->get_right_node()->get_type_class() == "VariableNode") {
						VariableNode* p_variable_node_right = static_cast<VariableNode*>(p_bin_operation_node->get_right_node());
						auto it1 = all_var.find(p_variable_node_right->get_token().get_value());
						if (it1 != all_var.end()) {
							it->second = new IntClass((static_cast<IntClass*>(it1->second))->get_str_num());
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_bin_operation_node->get_right_node());
						it->second = new IntClass(p_number_node->get_token().get_value());
					}
				}
				return nullptr;
			}
		}
	}

	if (node->get_type_class() == "NewObjectNode") {
		NewObjectNode* p_new_obj_node = static_cast<NewObjectNode*>(node);

		if (p_new_obj_node->get_token_type().get_type() == "LIST" && all_var.find(p_new_obj_node->get_token_name().get_value()) == all_var.end()) {
			all_var.emplace(p_new_obj_node->get_token_name().get_value(), new ListClass());
		}

		return nullptr;
	}

	if (node->get_type_class() == "PrintConsoleNode") {
		PrintConsoleNode* p_print_console_node = static_cast<PrintConsoleNode*>(node);

		if (p_print_console_node->get_operand()->get_type_class() == "VariableNode") {
			VariableNode* p_var = static_cast<VariableNode*>(p_print_console_node->get_operand());

			auto it = all_var.find(p_var->get_token().get_value());

			if (it != all_var.end()) {
				std::cout << (static_cast<IntClass*>(it->second))->get_num() << std::endl;
			}
		} else if (p_print_console_node->get_operand()->get_type_class() == "BinOperationNode") {
			std::cout << count(static_cast<BinOperationNode*>(p_print_console_node->get_operand())) << std::endl;
		} else if (p_print_console_node->get_operand()->get_type_class() == "NumberNode") {
			NumberNode* p_number_node = static_cast<NumberNode*>(p_print_console_node->get_operand());
			std::cout << p_number_node->get_token().get_value() << std::endl;
		} else if (p_print_console_node->get_operand()->get_type_class() == "MethodCallNode") {
			MethodCallNode* p_method_node = static_cast<MethodCallNode*>(p_print_console_node->get_operand());
			run(p_method_node);

			if (returned_value != nullptr) {
				if (returned_value->get_type_class() == "IntClass") {
					std::cout << static_cast<IntClass*>(returned_value)->get_num() << '\n';
					delete static_cast<IntClass*>(returned_value);
				}

				returned_value = nullptr;
			}

			return nullptr;
		}

		return nullptr;
	}

	if (node->get_type_class() == "MethodCallNode") {
		MethodCallNode* p_statement_node = static_cast<MethodCallNode*>(node);

		auto it = all_var.find(p_statement_node->get_name_struct().get_value());

		if (it != all_var.end()) {
			if (it->second->get_type_class() == "ListClass") {
				ListClass* p_using_list = static_cast<ListClass*>(it->second);

				if (p_statement_node->get_name_method().get_value() == "push_back") {
					StatementsNode* p_parameters = static_cast<StatementsNode*>(p_statement_node->get_parameters());
					ExpressionNode* p_parameter = p_parameters->get(0);

					if (p_parameter->get_type_class() == "VariableNode") {
						VariableNode* p_var = static_cast<VariableNode*>(p_parameter);
						auto it1 = all_var.find(p_var->get_token().get_value());
						if (it1 != all_var.end()) {
							p_using_list->push_back(new IntClass(static_cast<IntClass*>(it->second)->get_str_num()));
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_parameter);
						p_using_list->push_back(new IntClass(p_number_node->get_token().get_value()));
					}

					return nullptr;
				}

				if (p_statement_node->get_name_method().get_value() == "get") {
					StatementsNode* p_parameters = static_cast<StatementsNode*>(p_statement_node->get_parameters());
					ExpressionNode* p_parameter = p_parameters->get(0);

					if (returned_value != nullptr) {
						if (returned_value->get_type_class() == "IntClass") {
							delete static_cast<IntClass*>(returned_value);
						} else if (returned_value->get_type_class() == "ListClass") {
							delete static_cast<ListClass*>(returned_value);
						}
					}

					if (p_parameter->get_type_class() == "VariableNode") {
						VariableNode* p_var = static_cast<VariableNode*>(p_parameter);
						auto it1 = all_var.find(p_var->get_token().get_value());
						if (it1 != all_var.end()) {
							if (it->second->get_type_class() == "IntClass") {
								returned_value = new IntClass(*static_cast<IntClass*>(p_using_list->get(static_cast<IntClass*>(it->second)->get_num())));
							}
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_parameter);
						returned_value = new IntClass(*static_cast<IntClass*>(p_using_list->get(IntClass::to_int(p_number_node->get_token().get_value()))));
					}
				}

				if (p_statement_node->get_name_method().get_value() == "pop") {
					StatementsNode* p_parameters = static_cast<StatementsNode*>(p_statement_node->get_parameters());
					ExpressionNode* p_parameter = p_parameters->get(0);

					if (returned_value != nullptr) {
						if (returned_value->get_type_class() == "IntClass") {
							delete static_cast<IntClass*>(returned_value);
						} else if (returned_value->get_type_class() == "ListClass") {
							delete static_cast<ListClass*>(returned_value);
						}
					}

					if (p_parameter->get_type_class() == "VariableNode") {
						VariableNode* p_var = static_cast<VariableNode*>(p_parameter);
						auto it1 = all_var.find(p_var->get_token().get_value());
						if (it1 != all_var.end()) {
							if (it->second->get_type_class() == "IntClass") {
								p_using_list->pop(static_cast<IntClass*>(it->second)->get_num());
							}
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_parameter);
						p_using_list->pop(IntClass::to_int(p_number_node->get_token().get_value()));
					}

					return nullptr;
				}

				if (p_statement_node->get_name_method().get_value() == "size") {
					StatementsNode* p_parameters = static_cast<StatementsNode*>(p_statement_node->get_parameters());

					if (returned_value != nullptr) {
						if (returned_value->get_type_class() == "IntClass") {
							delete static_cast<IntClass*>(returned_value);
						} else if (returned_value->get_type_class() == "ListClass") {
							delete static_cast<ListClass*>(returned_value);
						}
					}

					returned_value = new IntClass(p_using_list->get_size());

					return nullptr;
				}

				if (p_statement_node->get_name_method().get_value() == "insert") {
					StatementsNode* p_parameters = static_cast<StatementsNode*>(p_statement_node->get_parameters());
					ExpressionNode* p_parameter = p_parameters->get(0);
					ExpressionNode* p_non_class_obj = p_parameters->get(1);
					RootClass* p_obj;

					if (p_non_class_obj->get_type_class() == "VariableNode") {
						VariableNode* p_temp_var = static_cast<VariableNode*>(p_non_class_obj);

						auto it3 = all_var.find(p_temp_var->get_token().get_value());

						if (it3 != all_var.end()) {
							p_obj = new IntClass(static_cast<IntClass*>(it3->second)->get_str_num());
						}
					}

					if (returned_value != nullptr) {
						if (returned_value->get_type_class() == "IntClass") {
							delete static_cast<IntClass*>(returned_value);
						} else if (returned_value->get_type_class() == "ListClass") {
							delete static_cast<ListClass*>(returned_value);
						}
					}

					if (p_parameter->get_type_class() == "VariableNode") {
						VariableNode* p_var = static_cast<VariableNode*>(p_parameter);
						auto it1 = all_var.find(p_var->get_token().get_value());
						if (it1 != all_var.end()) {
							if (it->second->get_type_class() == "IntClass") {
								p_using_list->insert(p_obj, static_cast<IntClass*>(it->second)->get_num());
							}
						}
					} else {
						NumberNode* p_number_node = static_cast<NumberNode*>(p_parameter);
						p_using_list->insert(p_obj, IntClass::to_int(p_number_node->get_token().get_value()));
					}
				}
			}
		} else {

		}

		return nullptr;
	}

	if (node->get_type_class() == "StatementsNode") {
		StatementsNode* p_statement_node = static_cast<StatementsNode*>(node);

		for (int i = 0; i < p_statement_node->size(); i++) {
			run(p_statement_node->get(i));
		}

		return nullptr;
	}

	if (node->get_type_class() == "BlockNode") {
		BlockNode* p_block_node = static_cast<BlockNode*>(node);

		for (int i = 0; i < p_block_node->size(); i++) {
			run(p_block_node->get(i));
		}

		return nullptr;
	}

	if (node->get_type_class() == "IfNode") {
		IfNode* p_if_node = static_cast<IfNode*>(node);

		if (check_predicate(p_if_node->get_p_predicate())) {
			run(p_if_node->get_p_block());
		}

		return nullptr;
	}

	if (node->get_type_class() == "While_Node") {
		While_Node* p_while_node = static_cast<While_Node*>(node);

		while (check_predicate(p_while_node->get_p_predicate())) {
			run(p_while_node->get_p_block());
		}
	}

	return nullptr;
}

void Parser::intepretation() {
	parse_code();
	run(root);
}

Parser::~Parser() {
	delete static_cast<StatementsNode*>(root);
}

bool Parser::check_predicate(PredicateNode *p_predicate) {
	IntClass* p_left_operand;
	IntClass* p_right_operand;
	int left, right;

	if (p_predicate->get_left_node()->get_type_class() == "NumberNode") {
		NumberNode* p_number_node = static_cast<NumberNode*>(p_predicate->get_left_node());
		p_left_operand = new IntClass(p_number_node->get_token().get_value());
	} else if (p_predicate->get_left_node()->get_type_class() == "VariableNode") {
		VariableNode* p_var = static_cast<VariableNode*>(p_predicate->get_left_node());

		auto it = all_var.find(p_var->get_token().get_value());

		if (it != all_var.end()) {
			p_left_operand = new IntClass(*(static_cast<IntClass*>(it->second)));
		}
	}

	if (p_predicate->get_right_node()->get_type_class() == "NumberNode") {
		NumberNode* p_number_node = static_cast<NumberNode*>(p_predicate->get_right_node());
		p_right_operand = new IntClass(p_number_node->get_token().get_value());
	} else if (p_predicate->get_right_node()->get_type_class() == "VariableNode") {
		VariableNode* p_var = static_cast<VariableNode*>(p_predicate->get_right_node());

		auto it = all_var.find(p_var->get_token().get_value());

		if (it != all_var.end()) {
			p_right_operand = new IntClass(*(static_cast<IntClass*>(it->second)));
		}
	}

	bool result = false;

	if (p_predicate->get_token_operator().get_value() == "==") {
		if (p_left_operand->get_num() == p_right_operand->get_num()) {
			result = true;
		}
	}

	if (p_predicate->get_token_operator().get_value() == "<=") {
		if (p_left_operand->get_num() <= p_right_operand->get_num()) {
			result = true;
		}
	}

	if (p_predicate->get_token_operator().get_value() == ">=") {
		if (p_left_operand->get_num() >= p_right_operand->get_num()) {
			result = true;
		}
	}

	if (p_predicate->get_token_operator().get_value() == "<") {
		if (p_left_operand->get_num() < p_right_operand->get_num()) {
			result = true;
		}
	}

	if (p_predicate->get_token_operator().get_value() == ">") {
		if (p_left_operand->get_num() > p_right_operand->get_num()) {
			result = true;
		}
	}

	delete p_left_operand;
	delete p_right_operand;

	return result;
}

int Parser::count(ExpressionNode *node) {
	if (node->get_type_class() == "BinOperationNode") {
		BinOperationNode* p_bin = static_cast<BinOperationNode*>(node);

		if (p_bin->get_left_node()->get_type_class() == "VariableNode") {
			VariableNode* p_var = static_cast<VariableNode*>(p_bin->get_left_node());
			auto it = all_var.find(p_var->get_token().get_value());

			if (it != all_var.end()) {
				if (p_bin->get_token_operator().get_value() == "+") {
					return static_cast<IntClass*>(it->second)->get_num() + count(p_bin->get_right_node());
				}

				if (p_bin->get_token_operator().get_value() == "-") {
					return static_cast<IntClass*>(it->second)->get_num() - count(p_bin->get_right_node());
				}

				if (p_bin->get_token_operator().get_value() == "*") {
					return static_cast<IntClass*>(it->second)->get_num() * count(p_bin->get_right_node());
				}

				if (p_bin->get_token_operator().get_value() == "/") {
					return static_cast<IntClass*>(it->second)->get_num() / count(p_bin->get_right_node());
				}
			}
		} else if (p_bin->get_left_node()->get_type_class() == "NumberNode") {
			NumberNode* p_num = static_cast<NumberNode*>(p_bin->get_left_node());

			if (p_bin->get_token_operator().get_value() == "+") {
				return IntClass::to_int(p_num->get_token().get_value()) + count(p_bin->get_right_node());
			}

			if (p_bin->get_token_operator().get_value() == "-") {
				return IntClass::to_int(p_num->get_token().get_value()) - count(p_bin->get_right_node());
			}

			if (p_bin->get_token_operator().get_value() == "*") {
				return IntClass::to_int(p_num->get_token().get_value()) * count(p_bin->get_right_node());
			}

			if (p_bin->get_token_operator().get_value() == "/") {
				return IntClass::to_int(p_num->get_token().get_value()) / count(p_bin->get_right_node());
			}
		} else if (node->get_type_class() == "NumberNode") {
			NumberNode* p_num = static_cast<NumberNode*>(node);
			return IntClass::to_int(p_num->get_token().get_value());
		} else if (node->get_type_class() == "VariableNode") {
			VariableNode* p_var = static_cast<VariableNode*>(node);
			auto it = all_var.find(p_var->get_token().get_value());

			if (it != all_var.end()) {
				return static_cast<IntClass*>(it->second)->get_num();
			}
		}
	} else {
		if (node->get_type_class() == "VariableNode") {
			VariableNode* p_var = static_cast<VariableNode*>(node);
			auto it = all_var.find(p_var->get_token().get_value());

			return static_cast<IntClass*>(it->second)->get_num();
		} else {
			NumberNode* p_num = static_cast<NumberNode*>(node);
			return IntClass::to_int(p_num->get_token().get_value());

		}
	}

	return 0;
}

void Parser::clear_name_space() {
	for (auto it = all_var.begin(); it != all_var.begin(); ++it) {
		if (it->second->get_type_class() == "IntClass") {
			delete static_cast<IntClass*>(it->second);
		} else if (it->second->get_type_class() == "ListClass") {
			delete static_cast<ListClass *>(it->second);
		}
	}
}

ExpressionNode *Parser::parse_parameters(std::list<Token>::iterator &it) {
	++it;
	if (it->get_type() == "R_BRACKET") {
		++it;
		return new StatementsNode();
	}

	StatementsNode *p_statements = new StatementsNode;

	if (it->get_type() == "VAR") {
		p_statements->addNode(new VariableNode(*it));
	} else if (it->get_type() == "DIGIT") {
		p_statements->addNode(new NumberNode(*it));
	}
	++it;

	while (it->get_type() == "ENUM_SEPARATE") {
		++it;
		if (it->get_type() == "VariableNode") {
			p_statements->addNode(new VariableNode(*it));
		} else if (it->get_type() == "NumberNode") {
			p_statements->addNode(new NumberNode(*it));
		}
	}

	return p_statements;
}






