#include "filehandler.h"
#include "interface.h"
#include "enum.h"

void FileHandler::tryToOpenFile(const string &fullFileName, const string &shortFileName)
{
	file.open(fullFileName);
	if (file.is_open()) {
		print(text.openSuccess + shortFileName + text.whiteSpaces[5] + text.whiteSpaces[3], WHITE, GREEN);
	}
	else {
		file.open(fullFileName + text.txt);
		if (file.is_open()) {
			print(text.openSuccess + shortFileName + text.txt + text.whiteSpaces[5] + text.whiteSpaces[3], WHITE, GREEN);
		}
		else
			throw unsigned int(FILE_OPEN_ERROR);
	}
}