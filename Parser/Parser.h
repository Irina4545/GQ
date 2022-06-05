#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <iostream>
#include <map>
#include <set>
#include "../Token/Token.h"
#include "../AST/ExpressionNode/ExpressionNode.h"
#include "../AST/StatementsNode/StatementsNode.h"
#include "../AST/NumberNode/NumberNode.h"
#include "../AST/VariableNode/VariableNode.h"
#include "../AST/BinOperationNode/BinOperationNode.h"
#include "../AST/PrintConsoleNode/PrintConsoleNode.h"
#include "../BaseClasses/IntClass/IntClass.h"
#include "../AST/BlockNode/BlockNode.h"
#include "../AST/IfNode/IfNode.h"
#include "../BaseClasses/ListClass/ListClass.h"
#include "../AST/NewObjectNode/NewObjectNode.h"
#include "../AST/MethodCallNode/MethodCallNode.h"


class Parser {
private:
	bool lang(std::list<Token>::iterator&);
	bool expr(std::list<Token>::iterator&);
	bool EXPR_CYCLE(std::list<Token>::iterator&);
	bool EXPR_IF_ELSE(std::list<Token>::iterator&);
	bool EXPR_WHILE(std::list<Token>::iterator&);
	bool EXPR_ASSIGN(std::list<Token>::iterator&);
	bool EXPR_ELIF(std::list<Token>::iterator&);
	bool EXPR_ELSE(std::list<Token>::iterator&);
	bool VALUE(std::list<Token>::iterator&);
	bool FORMULA(std::list<Token>::iterator&);
	bool FORMULA2(std::list<Token>::iterator&);
	bool FORMULA3(std::list<Token>::iterator&);
	bool EXEC_BLOCK(std::list<Token>::iterator&);
	bool EXPR_PREDICATE(std::list<Token>::iterator&);
	bool EXPR_PRINT(std::list<Token>::iterator&);
	bool LIB_CREATE(std::list<Token>::iterator&);
	bool METHOD_CALL(std::list<Token>::iterator&);
	bool PARAMETERS(std::list<Token>::iterator&);



	bool step(std::list<Token>::iterator&);


	void parse_code();
	ExpressionNode* parse_expression(std::list<Token>::iterator&);
	ExpressionNode* parse_variable(std::list<Token>::iterator&);
	ExpressionNode* parse_formula(std::list<Token>::iterator&);
	ExpressionNode* parse_print(std::list<Token>::iterator&);
	ExpressionNode* parse_if(std::list<Token>::iterator&);
	BlockNode* parse_block(std::list<Token>::iterator&);
	ExpressionNode* parse_while(std::list<Token>::iterator&);
	PredicateNode* parse_conditional(std::list<Token>::iterator&);
	ExpressionNode* parse_list(std::list<Token>::iterator&);
	ExpressionNode* parse_parameters(std::list<Token>::iterator&);

	RootClass* returned_value;

	std::map<std::string, RootClass*> all_var;

	ExpressionNode* run(ExpressionNode* root);
	bool check_predicate(PredicateNode* p_predicate);
	int count(ExpressionNode*);

	void clear_name_space();
	//std::map<std::string, RootClass*>::iterator current_num;

	std::list<Token>* p_tokens;
	StatementsNode* root;
public:
	Parser(std::list<Token>&);
	bool go();
	void intepretation();
	~Parser();
};


#endif
