#include "HashTable.h"

void HashTable::resize(){
	capacity *= 2;
	HashNode** newArray = new HashNode * [capacity];

	memcpy(newArray, array, capacity * sizeof(HashNode*) / 2);

	for (int i = 0; i < size; i++)
		delete array[i];
	delete[] array;

	array = newArray;
}

HashTable::HashTable(){
	capacity = 20; size = 0;
	array = new HashNode * [capacity];
	dummy = new HashNode("", false);

	for (int i = 0; i < capacity; i++) {
		array[i] = nullptr;
	}
}

HashTable::~HashTable(){
	for (int i = 0; i < capacity; i++)
		delete array[i];

	delete[] array;
	delete dummy;
}

int HashTable::hashCode(string key){
	return std::hash<string>{}(key) % capacity;
}

void HashTable::insert(string key, bool value){
	if (capacity == size) {
		resize();
	}

	HashNode* tmp = new HashNode(key, value);
	int index = hashCode(key);

	while (array[index] && array[index]->key != key && array[index]->key != "") {
		index++;
		index %= capacity;
	}

	array[index] = tmp;
	size++;
}

bool HashTable::del(string key){
	int index = hashCode(key), k = 0;

	while (array[index]) {
		if (k++ > capacity)
			return NULL;

		if (array[index]->key == key) {
			HashNode* tmp = array[index];
			array[index] = dummy;
			size--;
			return tmp->value;
		}
		index++;
		index %= capacity;
	}
}

int HashTable::get(string key){
	int index = hashCode(key), k = 0;

	while (array[index]) {
		if (k++ > capacity)
			return -1;

		if (array[index]->key == key)
			return array[index]->value;

		index++;
		index %= capacity;
	}

	return -1;
}

int HashTable::sizeOfTable(){
	return size;
}

bool HashTable::isEmpty(){
	return size == 0;
}
