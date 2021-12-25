#pragma once
#include "HashNode.h"

/**
 * Implementation of a hash table
 *
 * The HashNode contains the actual
 * array, a dummy node for delete,
 * the capacity and the current size.
 */
class HashTable{
private:
	HashNode** array;
	HashNode* dummy;
	int capacity, size;

	/**
	* Resizes the array if
	* the capacity is reached.
	*/
	void resize();

public:

	/// Default constructor
	HashTable();

	/// Default destructor
	~HashTable();

	/**
	* Computes the hash code
	* for a given string.
	* 
	* @param string that is being proccesed
	* 
	* @return the hash used to get the
	* position in the array `int`
	*/
	int hashCode(string);

	/**
	* Inserts the key values pair
	* in the hash table.
	* 
	* @param string key to be inserted
	* @param bool value of the key
	* that is inserted
	*/
	void insert(string, bool);

	/**
	* Delete the key value
	* pair from the hash table
	* 
	* @param string key to be deleted
	*
	* @return the deleted value or NULL `bool`
	*/
	bool del(string);

	/**
	* Computes the value for the given key.
	* 
	* @param string for which the value is searched
	* 
	* @return the value of string, -1 if 
	* it is not present in the table `int`
	*/
	int get(string);

	/**
	* @ return the current size of the table `int`
	*/
	int sizeOfTable();

	/**
	* @ return true is the hast table is empty,
	* false otherwise `bool`
	*/
	bool isEmpty();
};
