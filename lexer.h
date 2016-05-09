#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

class Lexer {
public:
	
	Lexer() : position(0) {}

	void
		clearWhiteCharacters(string &line),
		isArgumentDouble(const string &line);

private:

	friend class Builder;

	void 
		loadExpression(const string &Expression);

	const unsigned int
		getLexem(double &buffer, unsigned int &lexemAttached);

	size_t position;

	string expression;

};

extern Lexer lexer;

#endif