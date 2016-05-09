#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "enum.h"

using namespace std;

struct Text {

	const string
		txt = ".txt",
		title = "Calculator project",
		task =
		"\n This program calculates expressions    \n\n",
		bnf = " Backus-Naur forms of permitted input:  \n",
		space = "\t\t\t\t\t\n",
		inputBnf[BNF_INPUT_SIZE] = {
		" <Expression>", "::=", " <Unary-Op>", "*","<Operand>   \n     ","(","<Binary-Op>","<Unary-Op>","*","<Operand>",")* \n",
		" <Operand>", "::=", "   <Constant>", "|","<Variable>   \n",
		" <Unary-Operator>", " ::=", " log"," | ","cos\t\t\n",
		" <Binary-Operator>", "::=", " *", " | ","+", " | ", "-\t\t\n" },
		bnfHint = "\n You can use white symbols and brackets anywhere \n",
		inputFileName = "\n Please, specify file name (simply press <ENTER> to input from console): \n",
		inputExpression = "\n Please, input expression: \n",
		inputVariable = "\n Please, input variable (simply press <ENTER> to tabulate function): \n",
		inputTabulationStart = "\n Please, input tabulation start: \n",
		inputTabulationEnd = "\n Please, input tabulation end: \n",
		inputTabulationStep = "\n Please, input tabulation step: \n",
		constantExpression = "\n Expression is constant, tabulation is impossible \n",
		openSuccess = "\n You successfully opened: ",
		openError = "\n\n Unfortunately, selected file can't be opened ",
		operators[OPERATORS_SIZE] = { "*", "+", "-" },
		separators[SEPARATORS_SIZE] = { "*", "+", "-", "(", ")", "x", "l", "c", "." },
		f = "f(",
		fx = "f(x) = ",
		x = "x = ",
		a = "a = ",
		b = "b = ",
		dx = "Delta x = ",
		fileName = "%filename%: ",
		ln = "ln(",
		cos = "cos(",
		equal = " = ",
		NotANumber = "not existing in R",
		builderErrors[15] = { 
		"Selected file can't be opened ", "Expression is empty ", "Wrong symbol was used ",
		"Missing operator or incorrect operator formatting ", "Wrong logariphm transcription ",
		"Wrong cosinus transcription ", "Unrecognized number was used ", "Wrong brackets formatting ",
		"Wrong operator placement "},
		backspace = "\b",
		brackets = "()",
		n = "\n",
		sound = "\a",
		error = "\n ERROR: ",
		result = "\n Your result is: ",
		argumentsErrors[4] = { "Incorrect number of arguments \n", "Unrecognized number was used \n", "Wrong tabulation limits \n", "Wrong tabulation step \n"},
		argumentsHelp = 
		" \n Usage:\n\n"
		" ...\\calculator.exe [path]\n"
		" ...\\calculator.exe [path] [value]\n"
		" ...\\calculator.exe [path] [start] [end] [step]\n\n"
		" ...\\calculator.exe JJ.txt\n"
		" ...\\calculator.exe JJ.txt 123.456\n"
		" ...\\calculator.exe JJ.txt -9.8765 .4321 0.1234\n\n"
		"  JJ.txt - file name to open or path to it\n"
		" 123.456 - variable value\n"
		" -9.8765 - tabulation start\n"
		"   .4321 - tabulation end\n"
		"  0.1234 - tabulation step\n ";

	const char
		dot = '.',
		minus = '-',
		backslash = '\\',
		whiteSpaces[WHITE_SPACES_SIZE] = { BELL, BACKSPACE, TAB, NEW_LINE, ENTER, SPACE };

	const int
		inputBnfTextColors[BNF_INPUT_SIZE] = {
		LIGHT_MAGENTA, DARK_GREY, BLUE, DARK_GREY, BLUE, DARK_GREY, BLUE, BLUE, DARK_GREY, BLUE, DARK_GREY,
		LIGHT_MAGENTA, DARK_GREY, BLUE, DARK_GREY, BLUE,
		LIGHT_MAGENTA, DARK_GREY, BLUE, DARK_GREY, BLUE,
		LIGHT_MAGENTA, DARK_GREY, BLUE, DARK_GREY, BLUE, DARK_GREY, BLUE };

};

extern Text text;

#endif