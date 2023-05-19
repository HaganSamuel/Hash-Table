#ifndef PROGRAM3_H
#define PROGRAM3_H

// Constants that should be used when implementing your code.
#define ARRAY_SIZE	8	// Maximum size of the array (originally 100)
#define MAX_COLLISIONS	5	// Maximum number of collisions allowed before giving up
#define NO_LOCATION	-1	// Value to use to indicate no location in the hash table
#define INVALID_CALL	-2	// Function call was invalid because initialization still needs to be done

// Sets the size of the hash table.  Returns if it succeeded.
bool SetHashTableSize(int n);

// Sets the primary and secondary hash functions for hashing.  Returns if it succeeded.
bool SetHashFunctions(int f, int s);

// Loads the data from the array into the hash table.  Returns the number of values added.
int LoadData(int a[ARRAY_SIZE]);

// Adds the key to the hash table.  Returns if it succeeded.
bool AddValue(int key);

// Removes the key from the hash table.  Returns the index that the key was stored in.
int RemoveValue(int key);

// Finds the key in the hash table and returns its index.
int GetHashTableLocation(int key);

// Returns the number of collisions that have occurred since the hash table was set up.
int GetNumberOfCollisions();

void printArray(int a[]);

#endif
