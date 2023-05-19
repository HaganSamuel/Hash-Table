#include "program3.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

// Lesson: ARRAY_SIZE != HashTable Size.
int* hashTable;

int globalArraySize = 0; // Required as ARRAY_SIZE != table size.

int hashFunction1 = 0;
int hashFunction2 = 0;

int totalCollisions = 0; // Overall collisions since last call to SetHashTableSize. Collisions only occur when adding. Nowhere else.

int collisionsCount = 0; // Knowing the maximum collisions up to 5 within the finding has table.

int totalIntegersAdded = 0; // The number of values that were added to keep track if it surpasses the number of possible values.

bool validCallToHashTableSize = false;
bool removeTheIndex = false;

// fmod has to be used in replacement of "%" because modulus "%" only works with integers, not floats or doubles.

// Hashtable 1 Switch Case to sort it by method. (Helper Method)
// Where k = numberToBeHashed, and n = array size.
int hashFunctionOne(int numberToBeHashed) {
	switch (hashFunction1) {
	case 1:
		return (int)(53 * fmod((0.2897 * numberToBeHashed), 1));
		break;
	case 2:
		return numberToBeHashed % globalArraySize;
		break;
	case 3:
		return numberToBeHashed % 53;
		break;
	case 4:
		return numberToBeHashed % 48;
		break;
	case 5:
		return 1;
		break;
	}
}

// Keeps track of the # of steps required to 
int hashFunctionTwo(int numberToBeHashed) {
	switch (hashFunction2) {
	case 1:
		return (int)(52 * fmod((0.2897 * numberToBeHashed), 1));
		break;
	case 2:
		return numberToBeHashed % (globalArraySize - 1);
		break;
	case 3:
		return numberToBeHashed % 52;
		break;
	case 4:
		return numberToBeHashed % 47;
		break;
	case 5:
		return 0 + 0;
		break;
	}
}

// Finds the key in the hash table and returns its index.
int AddHashTableLocation(int key) {

	collisionsCount = 0;

	int currentIndex = hashFunctionOne(key);
	int currentIndex2 = hashFunctionTwo(key);

	// Reduce the size of the index value so that it can be indexed at a value less than or equal to the size.
	while (currentIndex > globalArraySize || currentIndex2 > globalArraySize) {
		if (currentIndex > globalArraySize) {
			currentIndex = currentIndex % globalArraySize;
		}
		if (currentIndex2 > globalArraySize) {
			currentIndex2 = currentIndex2 % globalArraySize;
		}
	}
	if (currentIndex2 == 0) {
		currentIndex2 += 1;
	}

	// If the index is empty, return the index location.
	if (hashTable[currentIndex] == 0) {
		return currentIndex;
	}

	// Otherwise use the second hashtable by using modulus size-1 (index % size-1).
	else {
		collisionsCount++;
		while (true) {
			// hash1(k) + j*hash2(k)
			int modifiedIndex = (currentIndex + (collisionsCount * currentIndex2)) % (globalArraySize); // Not entirely sure this will work. Needs to be elaborated.
			if (hashTable[modifiedIndex] == 0) {
				totalCollisions += collisionsCount;
				return modifiedIndex;
			}
			else {
				// Check if we maxxed out the collisisons possible.
				if (collisionsCount >= MAX_COLLISIONS) {
					totalCollisions += collisionsCount;
					return NO_LOCATION;
				}
			}
			collisionsCount++;
		}
	}
}

// Sets the size of the hash table.  Returns if it succeeded.
bool SetHashTableSize(int n) {
	totalCollisions = 0;

	if (n < 1) {
		validCallToHashTableSize = false;
		return false;
	}

	validCallToHashTableSize = true;

	hashTable = new int[n];

	for (int i = 0; i < n; i++) {
		hashTable[i] = 0;
	}

	globalArraySize = n;

	return true;
}

// Sets the primary and secondary hash functions for hashing.  Returns if it succeeded.
bool SetHashFunctions(int f, int s) {
	if (f > 0 && f < 6 && s > 0 && s < 6) {
		hashFunction1 = f;
		hashFunction2 = s;
		return true;
	}
	return false;
}

// Loads the data from the array into the hash table.  Returns the number of values added.
int LoadData(int a[ARRAY_SIZE]) {
	totalIntegersAdded = 0;

	if (validCallToHashTableSize == false) {
		return 0;
	}

	for (int i = 0; i <= ARRAY_SIZE; i++) {
		if (a[i] < 0) {
			return totalIntegersAdded;
		}
		else {
			bool isItTrueOrNot = AddValue(a[i]);
			if (isItTrueOrNot == true) {
				totalIntegersAdded++;
			}
		}
	}
	return totalIntegersAdded;
}

// Adds the key to the hash table.  Returns if it succeeded.
bool AddValue(int key) {

	if (validCallToHashTableSize == false || totalIntegersAdded >= globalArraySize || key < 0) {
		return false;
	}

	int indexLocation = AddHashTableLocation(key);

	// Put this after indexLocation initialization in order to get the max collision count.
	if (collisionsCount >= MAX_COLLISIONS) {
		return false;
	}

	if (indexLocation == NO_LOCATION || indexLocation < 0) {
		return false;
	}
	else {
		int modifiedLocation = indexLocation;

		// Reduce the size of the index value so that it can be indexed at a value less than or equal to the size.
		while (modifiedLocation > globalArraySize) {
			modifiedLocation = modifiedLocation % globalArraySize;
		}
		hashTable[modifiedLocation] = key;
		return true;
	}
}

// Removes the key from the hash table. Returns the index that the key was stored in.
int RemoveValue(int key) {

	if (key < 0) {
		return NO_LOCATION;
	}

	int indexPosition = GetHashTableLocation(key);

	if (validCallToHashTableSize == false || totalCollisions >= MAX_COLLISIONS || indexPosition == INVALID_CALL) {
		return INVALID_CALL;
	}

	else if (indexPosition == NO_LOCATION) {
		return NO_LOCATION;
	}

	else {
		int modifiedLocation = indexPosition;
		while (modifiedLocation > globalArraySize) {
			modifiedLocation = modifiedLocation % globalArraySize;
		}
		totalIntegersAdded--;
		hashTable[modifiedLocation] = 0;

		return modifiedLocation;
	}
}

// Finds the key in the hash table and returns its index.
int GetHashTableLocation(int key) {

	if (validCallToHashTableSize == false) {
		return INVALID_CALL;
	}

	int collisionsCountForFinding = 0;

	//cout << "So the key right now is: " << key << endl;

	int currentIndex = hashFunctionOne(key);
	int currentIndex2 = hashFunctionTwo(key);

	// Reduce the size of the index value so that it can be indexed at a value less than or equal to the size.
	while (currentIndex > globalArraySize || currentIndex2 > globalArraySize) {
		//cout << "Key is bigger than array size. Modifying the key from " << modifiedKey << " to " << modifiedKey % ARRAY_SIZE << endl;
		if (currentIndex > globalArraySize) {
			currentIndex = currentIndex % globalArraySize;
		}
		if (currentIndex2 > globalArraySize) {
			currentIndex2 = currentIndex2 % globalArraySize;
		}
	}

	if (currentIndex2 == 0) {
		currentIndex2 += 1;
	}

	//cout << "The indexes we want from Hashtable One is: " << currentIndex << " While the second hashtable wants: " << currentIndex2 << endl;

	// If the index is empty, return the index location.
	if (hashTable[currentIndex] == key) {
		return currentIndex;
	}

	// Otherwise use the second hashtable by using modulus size-1 (index % size-1).
	else {
		collisionsCountForFinding++;
		while (true) {
			// hash1(k) + j*hash2(k)
			int modifiedIndex = (currentIndex + (collisionsCountForFinding * currentIndex2)) % (globalArraySize);

			// Check if we maxxed out the collisisons possible.
			if (collisionsCountForFinding == MAX_COLLISIONS) {
				return NO_LOCATION;
			}
			else if (hashTable[modifiedIndex] == key) {
				return modifiedIndex;
			}
			else {
				collisionsCountForFinding++;
			}
		}
	}
}

// Returns the number of collisions that have occurred since the hash table was set up.
int GetNumberOfCollisions() {
	if (validCallToHashTableSize == true) {
		return totalCollisions;
	}
	else {
		return INVALID_CALL;
	}
}


// Printing helper function.
void printArray(int a[]) {
	for (int i = 0; i < globalArraySize; i++) {
		cout << a[i] << " ";
	}
}

//#endif