char *tombstone = new char[32];
char *null = new char[32];

#include "dictionary.h"

bool equalChar(char arr1[], char arr2[])
{
	for (int i = 0; arr1[i] != '\0' || arr2[i] != '\0'; i++)
		if (arr1[i] != arr2[i])
			return false;
	return true;
}

Dictionary::Dictionary()
{
	N = 100;
	A = new Entry[N];
}

int Dictionary::hashValue(char key[])
{
	long p = 3, pow = 1;
	int hash = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{
		hash = (hash + (key[i] - 'A') * pow) % N;
		pow = pow * p;
	}
	return hash;
}

int Dictionary::findFreeIndex(char key[])
{
	int hash = hashValue(key);
	for (int i = hash; true; i = (i + 1) % N)
	{
		if (A[i].key == null || A[i].key == tombstone)
			return i;
		if (i == (hash - 1 + N) % N)
			return -1;
	}
}

struct Entry *Dictionary::get(char key[])
{
	int hash = hashValue(key);
	for (int i = hash; true; i = (i + 1) % N)
	{
		if (equalChar(A[i].key, key))
			return &(A[i]);
		if (A[i].key == null || i == (hash - 1 + N) % N)
			return nullptr;
	}
	return nullptr;
}

bool Dictionary::put(struct Entry e)
{
	int index = findFreeIndex(e.key);
	if (index == -1)
		return false;
	char **temp = new char *(e.key);
	A[index].key = *temp;
	A[index].value = e.value;
	return true;
}

bool Dictionary::remove(char key[])
{
	int hash = hashValue(key);
	for (int i = hash; true; i = (i + 1) % N)
	{
		if (equalChar(A[i].key, key))
		{
			delete[] A[i].key;
			A[i].key = tombstone;
			return true;
		}
		if (A[i].key == null || i == (hash - 1 + N) % N)
			return false;
	}
}
