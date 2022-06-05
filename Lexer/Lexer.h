#ifndef LEXER_H
#define LEXER_H

#include <list>
#include <string>
#include <regex>
#include "../Token/Token.h"

class Lexer {
private:
	static std::list<Token> tokens; // лист токенов
	static const std::pair<std::string, std::regex> DESCRIPTION_LECHEMS[]; // массив пар из названия лексем и регулярных выражений
	static const size_t DESC_LECHEMS_SIZE;
	static std::string check_lexems(std::string); // проверка строки на регулярку
	static int num_line; // номер строки в данный момент времени
public:
	static void run(std::string);
	static std::list<Token>& get_list_token(); // ссылка на лист токенов
};

#endif
