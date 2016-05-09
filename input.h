#ifndef INPUT_H
#define INPUT_H

#include <conio.h>
#include <string>

using namespace std;

class Input {
public:

	void
		getFileName(),
		getVariables(),
		getExpression(),
		readLine(string &line),
		checkArguments(const int &argc, char* argv[]),
		getTabulation(const string &dialog, double &tabulation, const string &tabulationType);

	const double
		getX() const;

	const bool
		isPathFromConsole() const,
		isTabulationNeeded() const;

private:
	
	friend class Builder;
	friend class Calculator;

	bool
		arguments,
		isFromFile,
		needTabulation,
		pathFromConsole,
		isExpressionConstant;

	double
		X;
	
	string
		expression,
		fullPathToFile,
		shortPathToFile;

	struct Tabulation {
		double
			start, end, step;
	} tabulation;

};

extern Input input;

#endif