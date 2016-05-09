#include "lexer.h"
#include "text.h"
#include "enum.h"
#include "implements.h"

void Lexer::clearWhiteCharacters(string &line) {
	string output;
	for (char i : line)
		if (!checkElementInArray(i, text.whiteSpaces, WHITE_SPACES_SIZE)) output += i;
	line = output;
}

void Lexer::loadExpression(const string &Expression)
{
	expression = Expression;
}

const unsigned int Lexer::getLexem(double &buffer, unsigned int &lexemAttached)
{
	if (position >= expression.size())
		return END_OF_EXPRESSION;
	string input;
	input = expression[position];
	if (!checkElementInArray(input, text.separators, SEPARATORS_SIZE) && !isdigit(input[0]))
		throw unsigned int(UNRECOGNIZED_CHARACTER_ERROR);
	position++;
	unsigned int index(DIGIT);
	for (unsigned int i = 0; i < SEPARATORS_SIZE; i++)
		if (input == text.separators[i])
			index = i;
	switch (index) {
	case OPEN_BRACKET:  
	{
		if (position == expression.size())
			lexemAttached = END_OF_EXPRESSION;
		else
		{
			string charCell;
			charCell = expression[position];
			if (charCell == text.separators[CLOSE_BRACKET])
				throw unsigned int(BRACKETS_FORMATTING_ERROR);
		}
		return LEFT_BRACKET;
	}
	case CLOSE_BRACKET:
	{
		if (position == expression.size())
			lexemAttached = END_OF_EXPRESSION;
		else
		{
			string charCell;
			charCell = expression[position];
			if (charCell != text.separators[CLOSE_BRACKET])
			{
				position++;
				if (!checkElementInArray(charCell, text.operators, OPERATORS_SIZE))
					throw unsigned int(MISSING_OPERATOR_ERROR);
				if (charCell == text.separators[STAR])
					lexemAttached = MULTIPLICATION;
				if (charCell == text.separators[PLUS])
					lexemAttached = ADDITION;
				if (charCell == text.separators[MINUS])
					lexemAttached = SUBSTRACTION;
			}
		}
		return RIGHT_BRACKET;
	}
	case X:
	{
		if (position == expression.size())
			lexemAttached = END_OF_EXPRESSION;
		else
		{
			string charCell;
			charCell = expression[position];
			if (charCell != text.separators[CLOSE_BRACKET])
			{
				position++;
				if (!checkElementInArray(charCell, text.operators, OPERATORS_SIZE))
					throw unsigned int(MISSING_OPERATOR_ERROR);
				if (charCell == text.separators[STAR])
					lexemAttached = MULTIPLICATION;
				if (charCell == text.separators[PLUS])
					lexemAttached = ADDITION;
				if (charCell == text.separators[MINUS])
					lexemAttached = SUBSTRACTION;
			}
		}
		return VARIABLE;
	}
	case L:
	{
		if (position + 1 >= expression.size())
			throw unsigned int(LOGARIPHM_FORMATTING_ERROR);
		input += expression.substr(position, 2);
		if (input != text.ln)
			throw unsigned int(LOGARIPHM_FORMATTING_ERROR);
		position += 2;
		return LOGARIPHM;
	}
	case C:
	{
		if (position + 2 >= expression.size())
			throw unsigned int(COSINUS_FORMATTING_ERROR);
		input += expression.substr(position, 3);
		if (input != text.cos)
			throw unsigned int(COSINUS_FORMATTING_ERROR);
		position += 3;
		return COSINUS;
	}
	case DOT:
	case DIGIT:
	{
		size_t end = expression.find_first_of(text.separators[0] + text.separators[1] + text.separators[2] + text.separators[4], position);
		input += expression.substr(position, end - position);
		position += end - position;
		try {
			isArgumentDouble(input);
			buffer = stod(input);
			if (position >= expression.size())
				lexemAttached = END_OF_EXPRESSION;
			else
			{
				string charCell;
				charCell = expression[position];
				if (charCell != text.separators[CLOSE_BRACKET])
				{
					position++;
					if (!checkElementInArray(charCell, text.operators, OPERATORS_SIZE))
						throw unsigned int(MISSING_OPERATOR_ERROR);
					if (charCell == text.separators[STAR])
						lexemAttached = MULTIPLICATION;
					if (charCell == text.separators[PLUS])
						lexemAttached = ADDITION;
					if (charCell == text.separators[MINUS])
						lexemAttached = SUBSTRACTION;
				}
			}
			return INVARIABLE;
		}
		catch (unsigned int) {
			throw unsigned int(UNRECOGNIZED_NUMBER_ERROR);
		}
	}
	default:
		throw unsigned int(OPERATOR_FORMATTING_ERROR);
	}
}

void Lexer::isArgumentDouble(const string &line)
{
	bool dot = false;
	if ((line[0] != text.minus && !isdigit(line[0])) ||
		(line[0] == text.minus && line.size() == 1))
		if (line[0] == text.dot && line.size() > 1)
			dot = true;
		else
			throw unsigned int(NUMBER_FORMAT_ERROR);
	unsigned int i;
	i = (line[0] == text.minus || line[0] == text.dot);
	for (i; i < line.size(); i++) {
		if (line[i] == text.dot)
			if (dot) throw true;
			else dot = true;
		else
			if (!isdigit(line[i]))
				throw unsigned int(NUMBER_FORMAT_ERROR);
	}
}