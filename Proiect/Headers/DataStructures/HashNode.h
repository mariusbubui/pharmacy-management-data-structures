#pragma once
#include<string>
using std::string;

/**
 * Implementation of a hash table node
 *
 * The HashNode contains pointers to the 
 * actual key and it`s value.
 */
class HashNode{
public:
	string key;
	bool value;

    /**
	* Constructor
	*
	* Initializes a HashNode with all
	* of its members.
	*/
	HashNode(string k, bool v) : key(k), value(v) {};
};

