#ifndef INTERFACE_H
#define INTERFACE_H

#include <Windows.h>
#include <iostream>

#include "text.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;

class Interface {
public:

	void
		showInfo() const,
		clearInputField() const,
		showInputDialog(const string &name, const string &inputType) const;

};

extern Interface UI;

template <class TypeClass> void print(const TypeClass text, const int textColor, const int backgroundColor = BLACK) {
	SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | textColor));
	cout << text;
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GREY));
}

#endif