#pragma once
#include "HashNode.h"

class HashTable{
private:
	HashNode** array;
	HashNode* dummy;
	int capacity, size;
	void resize();

public:
	HashTable();
	~HashTable();
	int hashCode(string);
	void insert(string, bool);
	bool del(string);
	int get(string);
	int sizeOfTable();
	bool isEmpty();
};
