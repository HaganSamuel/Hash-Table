#include "program3.h"

#include <iostream>

using namespace std;

/* You may use this file to test your program.
	This file will not be submitted, as a different test3.cpp will be used. */
int main(int argv, char** argc) {
	int arrayA[8] = { 55, 23, 106, 82, 5, 44, 33, 101 };

	SetHashFunctions(4, 3);

	SetHashTableSize(8);

	printArray(arrayA);

	LoadData(arrayA);

	RemoveValue(101);

	cout << "\n The # of collisions are: " << GetNumberOfCollisions() << endl;
}