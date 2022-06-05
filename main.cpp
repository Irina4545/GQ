#include <iostream>
#include <fstream>
#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"

int main() {

	std::fstream file;
	file.open("/home/sergei/CLionProjects/gosling/langgg/code.txt");

	if (file.is_open()) {
		std::string line;
		while (!file.eof()) {
			std::getline(file, line);
			try {
				Lexer::run(line);
			} catch (std::string exc) {
				std::cout << exc << '\n';
				return 0;
			}
		}


		std::list<Token>::iterator it_tokens = Lexer::get_list_token().begin();

		std::cout << "Lexer:\n";
		for (;it_tokens != Lexer::get_list_token().end(); ++it_tokens) {
			std::cout << *it_tokens << '\n';
		}




		Parser parser(Lexer::get_list_token());

		std::cout << "\n\nParser:\n";
		try {
			if (parser.go()) {
				std::cout << "успешно проверено\n";
			}
		} catch (std::string exc) {
			std::cout << exc << '\n';
			return 0;
		}

		std::cout << "\n\noutput:\n";
		try {
			parser.intepretation();
		} catch (std::string exc) {
			std::cout << exc << '\n';
			return 0;
		}


	} else {
		std::cout << "файл c кодом не найден\n";
	}

	return 0;
}
