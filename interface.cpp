#include "interface.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Getting console output descriptor and saving it in "hStdOut" identifier
CONSOLE_SCREEN_BUFFER_INFO csbi; // (On initialization is empty)
								 // CSBI-typedef variable for saving different info about console in it's fields like:
								 // - dwCursorPosition, that stores coordinates of cursor in COORD-typedef
								 // Isn't a dynamic variable
								 // - dwSize - sizes of console
								 // - etc.

void Interface::clearInputField() const {
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD binBuffer;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 4 * csbi.dwSize.X, { 0, csbi.dwCursorPosition.Y - 4 }, &binBuffer);
	FillConsoleOutputAttribute(hStdOut, BLACK, 4 * csbi.dwSize.X, { 0, csbi.dwCursorPosition.Y - 4 }, &binBuffer);
	SetConsoleCursorPosition(hStdOut, { 0, csbi.dwCursorPosition.Y - 4 });
}

void Interface::showInfo() const {
	SetConsoleTitle((LPCSTR)text.title.c_str());
	SetConsoleScreenBufferSize(hStdOut, { 100, 300});
	print(text.task, WHITE, MAGENTA);
	print(text.bnf, WHITE, CYAN);
	print(text.space, WHITE, WHITE);
	for (unsigned int i = 0; i < BNF_INPUT_SIZE; i++)
		print(text.inputBnf[i], text.inputBnfTextColors[i], WHITE);
	print(text.space, WHITE, WHITE);
	print(text.bnfHint, LIGHT_GREY, BLUE);
}

void Interface::showInputDialog(const string &name, const string &inputType) const {
	print(name, BLUE, LIGHT_GREY);
	cout << text.whiteSpaces[3] << text.whiteSpaces[5] << inputType;
}