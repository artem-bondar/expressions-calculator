#ifndef IMPLEMENTS_H
#define IMPLEMENTS_H

#include <math.h>

template <class TypeClass> inline bool checkElementInArray(const TypeClass element, const TypeClass* array, const int arraySize) {
	for (int i = 0; i < arraySize; i++)
		if (element == array[i])
			return true;
	return false;
}

template <class TypeClass> inline string operator*(TypeClass words, int number) {
	string output;
	if (number) {
		for (int i = 0; i < number; i++)
			output += words;
	}
	return output;
}

#endif