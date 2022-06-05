#include "Lexer.h"

const std::pair<std::string, std::regex> Lexer::DESCRIPTION_LECHEMS[] = {
		std::make_pair("WHILE", std::regex(("(while)"))),
		std::make_pair("LIB", std::regex(("(lib)"))),
		std::make_pair("SPACE_NAME", std::regex(("(:)"))),
		std::make_pair("DOT", std::regex((R"(\.)"))),
		std::make_pair("LIST", std::regex((R"(list)"))),
		std::make_pair("IF", std::regex(("(if)"))),
		std::make_pair("ELIF", std::regex(("(elif)"))),
		std::make_pair("ELSE", std::regex(("(else)"))),
		std::make_pair("PRINT", std::regex((R"(print)"))),
		std::make_pair("RETURN", std::regex(("(return)"))),
		std::make_pair("BOOL", std::regex(("(true|false)"))),
		std::make_pair("SPACE", std::regex((R"(([ ]|(\t)))"))),
		std::make_pair("L_BRACKET", std::regex(("([(])"))),
		std::make_pair("R_BRACKET", std::regex(("([)])"))),
		std::make_pair("L_BRACER", std::regex(("([{])"))),
		std::make_pair("R_BRACER", std::regex(("([}])"))),
		std::make_pair("ENUM_SEPARATE", std::regex(("(,)"))),
		std::make_pair("SEMICOLON", std::regex(("(;)"))),
		std::make_pair("VAR", std::regex(("([a-zA-Z_][A-Za-z0-9_]*)"))),
		std::make_pair("DIGIT", std::regex(("(([0-9])|([1-9][0-9]*))"))),
		std::make_pair("ASSIGN_OP", std::regex(("(=)"))),
		std::make_pair("OP", std::regex((R"([\+\-\*\/])"))),
		std::make_pair("CONDITIONAL_OP", std::regex((R"(([<>=][=]?)|([!][=]?))"))),
};

const size_t Lexer::DESC_LECHEMS_SIZE = sizeof(DESCRIPTION_LECHEMS) / sizeof(std::pair<std::string, std::regex>);

std::list<Token> Lexer::tokens{};

std::string Lexer::check_lexems(std::string lechema) {
	for (int j = 0; j < DESC_LECHEMS_SIZE; j++) {
		if (std::regex_match(lechema.data(), DESCRIPTION_LECHEMS[j].second)) {
			return DESCRIPTION_LECHEMS[j].first;
		}
	}
	return "";
}


int Lexer::num_line = 1;

void Lexer::run(std::string expression) {
	if (expression[expression.size() - 1] == '\n' || expression[expression.size() - 1] == '\r') {
		expression[expression.size() - 1] = ' ';
	} else {
		expression += " ";
	}

	std::string lechema = "";
	std::string type_of_current_lechema; // текущая лексема
	std::string check_lex = "";

	for (int i = 0; i < expression.size(); i++) {
		lechema += expression[i];
		type_of_current_lechema = check_lexems(lechema);

		if (type_of_current_lechema == "SPACE") {
			lechema = "";
			continue;
		}

		if (type_of_current_lechema == "" && lechema.size() == 1) {
			throw std::string("ошибка в граматике, строка ") + std::to_string(num_line);
		} else if (type_of_current_lechema == "") {
			--i; // value+ чтобы обработать и value и +

			// [0, last)
			check_lex = check_lexems(lechema.substr(0, lechema.size() - 1));
			tokens.emplace_back(Token(check_lex, lechema.substr(0, lechema.size() - 1), num_line));
			lechema = "";

		}

	}

	if (type_of_current_lechema == "STRING") {
		throw std::string("незаконченная строка");
	}

	num_line++;
}

std::list<Token>& Lexer::get_list_token() {
	return tokens;
}
