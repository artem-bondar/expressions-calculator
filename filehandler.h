#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>

using namespace std;

class FileHandler {

	friend class Builder;
	friend class Input;

	void
		tryToOpenFile(const string &filename, const string &shortFileName);

	ifstream file;

};

extern FileHandler fileHandler;

#endif