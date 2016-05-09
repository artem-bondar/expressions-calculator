#include "input.h"
#include "interface.h"
#include "lexer.h"
#include "enum.h"
#include "filehandler.h"

void Input::checkArguments(const int &argc,  char* argv[])
{
	fullPathToFile = argv[0];
	fullPathToFile = fullPathToFile.substr(0, fullPathToFile.find_last_of(text.backslash) + 1);
	try {
		switch (argc) {
		case 1: // Just the path to .exe
		{
			arguments = false;
			break;
		}
		case 2: // + path to statement
		case 3: // + path to statement + variable value
		case 5: // + path to statement + tabulation: start, end, step
		{
			shortPathToFile = argv[1];
			fullPathToFile += shortPathToFile;
			pathFromConsole = isFromFile = true;
			switch (argc) {
			case 3:
			{
				lexer.isArgumentDouble(argv[2]);
				X = stod(argv[2]);
				needTabulation = false;
				arguments = true;
				break;
			}
			case 5:
			{
				for (unsigned int i = 2; i <= 4; i++)
					lexer.isArgumentDouble(argv[i]);
				tabulation.start = stod(argv[2]);
				tabulation.end = stod(argv[3]);
				if (tabulation.end < tabulation.start)
					throw unsigned int(TABULATION_LIMITS_ERROR);
				tabulation.step = stod(argv[4]);
				if (tabulation.step <= 0)
					throw unsigned int(TABULATION_STEP_ERROR);
				arguments = needTabulation = true;
			}
			}
			break;
		}
		default:
			throw unsigned int(ARGUMENT_AMOUNT_ERROR);
		}
		}
	catch(unsigned int errorCode) {
		print(text.error + text.argumentsErrors[errorCode] + text.sound, WHITE, RED);
		cout << text.argumentsHelp;
		throw true;
	}
}

void Input::readLine(string &line)
{
	// Provides extended input with workable Backspace

	char input;
	do {
		input = _getch();
		if (input == BACKSPACE) {
			if (line.size()) {
				cout << text.whiteSpaces[1] << text.whiteSpaces[5] << text.whiteSpaces[1];
				line.pop_back();
			}
		}
		else {
			cout << input;
			line += input;
		}
	} while (input != ENTER);
	line.pop_back();
}

void Input::getExpression()
{
	if (isFromFile) {
		getline(fileHandler.file, expression);
		fileHandler.file.close();
	} else {
		UI.clearInputField();
		UI.showInputDialog(text.inputExpression, text.fx);
		readLine(expression);
		cout << text.n;
	}
}

void Input::getFileName()
{
	UI.showInputDialog(text.inputFileName, text.fileName);
	readLine(shortPathToFile);
	lexer.clearWhiteCharacters(shortPathToFile);
	isFromFile = shortPathToFile.size();
	if (isFromFile)
		fullPathToFile += shortPathToFile;
	cout << text.n;
}

void Input::getVariables()
{
	if (!arguments && !isExpressionConstant) {
		UI.showInputDialog(text.inputVariable, text.x);
		string line;
		readLine(line);
		cout << text.n;
		try {
			if (line.size()) {
				needTabulation = false;
				lexer.isArgumentDouble(line);
				X = stod(line);
			}
		else {
			needTabulation = true;
			UI.clearInputField();
			getTabulation(text.inputTabulationStart, tabulation.start, text.a);
			getTabulation(text.inputTabulationEnd, tabulation.end, text.b);
			if (tabulation.end < tabulation.start)
				throw unsigned int(TABULATION_LIMITS_ERROR);
			getTabulation(text.inputTabulationStep, tabulation.step, text.dx);
			if (tabulation.step <= 0)
				throw unsigned int(TABULATION_STEP_ERROR);
		}
		}
		catch (unsigned int errorCode) {
			print(text.error + text.argumentsErrors[errorCode] + text.sound, WHITE, RED);
			throw true;
		}
	}
}

void Input::getTabulation(const string &dialog, double &tabulation, const string &tabulationType)
{
	string line;
	UI.showInputDialog(dialog, tabulationType);
	readLine(line);
	cout << text.n;
	lexer.isArgumentDouble(line);
	tabulation = stod(line);
}

const double Input::getX() const
{
	return X;
}

const bool Input::isPathFromConsole() const
{
	return pathFromConsole;
}

const bool Input::isTabulationNeeded() const
{
	return needTabulation;
}