#include "text.h"
#include "node.h"
#include "lexer.h"
#include "input.h"
#include "builder.h"
#include "interface.h"
#include "calculator.h"
#include "filehandler.h"

Text text;
Lexer lexer;
Input input;
Interface UI;
Node treeRoot;
Builder builder;
Calculator calculator;
FileHandler fileHandler;

void main(int argc, char* argv[]) {
	try {
		input.checkArguments(argc, argv);
		UI.showInfo();
		if (!input.isPathFromConsole())
			input.getFileName();
		builder.loadExpression();
		input.getVariables();
		calculator.solveExpression();
	}
	catch (...) {}
	_getch();
}