#ifndef LANGGG_TOKEN_H
#define LANGGG_TOKEN_H


#include <string>
#include <ostream>

class Token {
private:
	std::string type;
	std::string value;
	int num_line;
public:
	Token();
	Token(std::string, std::string, int);
	Token(Token const &other_token);
	std::string get_type();
	std::string get_value();
	int get_num_line();

	Token& operator=(Token const &other_token);
};

std::ostream& operator<<(std::ostream&, Token&);



#endif
