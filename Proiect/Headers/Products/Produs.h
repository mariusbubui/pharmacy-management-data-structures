#pragma once
#include "DataStructures/RBTree.h"
#include "DataStructures/HashTable.h"
#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::vector;
using std::string;

class RBTree;

/**
* Abstract implemenatation of a Produs
*
* Contains the name,price and the 
* manufacturer of the product.
*/
class Produs {
protected:
	string denumire, producator;
	int pret;

	/**
	 * Passes the data in a stream
	 * for a Produs object.
	 *
	 * @return stream containing data
	 * of an Produs `ostream&`
	 */
	virtual ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Produs with all
	* of its members.
	*/
	Produs(string den, string prod, int p) : denumire{ den }, producator{ prod }, pret{ p } {};

	/// Default destructor
	virtual ~Produs() {};

	/**
	 * Overloads the << operator
	 * for a Produs object.
	 *
	 * @relatesalso Produs
	 */
	friend ostream& operator<<(ostream&, const Produs&);

	/**
	* Loads the data from the
	* resource file in the given
	* data structures.
	* 
	* @param RBTree* the tree that
	* will store the products
	* @param HashTable* the structure
	* that will store the disponibility
	* of the products.
	*/
	static void initializare(RBTree*, HashTable*);

	/**
	* Adds a product to the
	* given data structures.
	*
	* @param RBTree* the tree in which
	* the product will be added
	* @param HashTable* the structure
	* in which the product will be added
	*/
	static void adaugare(RBTree*, HashTable*);

	/**
	* Modifies a product in the
	* given data structures.
	*
	* @param RBTree* the tree to which
	* the product belongs to
	* @param HashTable* the structure
	* to which the product belongs to
	*/
	static void modificare(RBTree*, HashTable*);

	/**
	* Deletes a product in the
	* given data structures.
	*
	* @param RBTree* the tree from which
	* the product is being deleted
	* @param HashTable* the structure
	* from which the product is being deleted
	*/
	static void stergere(RBTree*, HashTable*);

	/**
	* Prints the products from the
	* given data structures.
	*
	* @param RBTree* the tree that
	* contains the products
	* @param HashTable* the structure
	* that contains the products
	*/
	static void afisare(RBTree*, HashTable*);

	/**
	* Searches a product in the
	* given data structures.
	*
	* @param RBTree* the tree in which
	* the seacrh is being performed
	* @param HashTable* the structure
	* in which the seacrh is being performed
	*/
	static void cautare(RBTree*, HashTable*);

	/**
	* Checks the disponibility of a product
	* in the given data structure.
	*
	* @param HashTable* the structure
	* in which the disponibility is being checked
	*/
	static void disponibilitate(HashTable*);

	/**
	* Sorts the products of the
	* given tree using the given
	* comparator.
	* 
	* @param RBTree* the data structure
	* that contains the products that
	* will be sorted
	* @param bool(*)(Produs*, Produs*)
	* function that represents the
	* comparator
	*/
	static void sortare(RBTree*, bool (*comparator)(Produs*, Produs*));

	/**
	* Filters the products of the
	* given tree using the given
	* filter.
	*
	* @param RBTree* the data structure
	* that contains the products that
	* will be filtered
	* @param bool(*)(Produs*, string)
	* function that represents the
	* filter
	*/
	static bool filtrare(RBTree*, string, bool (*filter)(Produs*, string));

	/**
	* Saves the data from the
	* given data structures 
	* in the resource file.
	*
	* @param RBTree* the tree from
	* which the products are beign saved
	* @param HashTable* the structure
	* from which the products are beign saved
	*/
	static void salvare_date(RBTree*, HashTable*);

	/**
	* Provides a comparator for
	* sorting in ascending order
	* after price.
	* 
	* @param Produs* the objects
	* that are being compared
	*/
	static bool pret1(Produs*, Produs*);

	/**
	* Provides a comparator for
	* sorting in descending order
	* after price.
	*
	* @param Produs* the objects
	* that are being compared
	*/
	static bool pret2(Produs*, Produs*);

	/**
	* Provides a filter for
	* the manufacturer of product.
	*
	* @param Produs* the object
	* that is beign filtered
	* @param string the name of 
	* the manufacturer
	* 
	* @return true if the name of
	* the manufacturer is the give
	* string, false otherwise `bool`
	*/
	static bool filter_producator(Produs*, string);

	/**
	* Provides a filter for
	* the price of product.
	*
	* @param Produs* the object
	* that is beign filtered
	* @param string the price of
	* the product that will be
	* casted to integer
	*
	* @return true if the price of
	* the product is the give
	* string, false otherwise `bool`
	*/
	static bool filter_pret(Produs*, string);

	/**
	* Getter for denumire
	*
	* @return the name of the product `string`
	*/
	string getDenumire() const { return this->denumire; };

	/**
	* Getter for producator
	*
	* @return the manufacturer of the product `string`
	*/
	string getProducator() const { return this->producator; };

	/**
	* Getter for pret
	*
	* @return the price of the product `int`
	*/
	int getPret() const { return this->pret; };

	/**
	* Virtual getter for subsranta
	*
	* @return the active substance `string`
	*/
	virtual string getSubstanta() const { return ""; };

	/**
	* Virtual getter for eliberare
	*
	* @return the need for medical prescription `bool`
	*/
	virtual bool getEliberare() const { return false; };

	/**
	* Virtual getter for utilizare
	*
	* @return the use cases `string`
	*/
	virtual string getUtilizare() const { return ""; };

	/**
	* Virtual getter for zona_aplicare
	*
	* @return the application area `string`
	*/
	virtual string getZona()const { return ""; };

	/**
	* Virtual getter for gramaj
	*
	* @return the weight of the active
	* susbtance in grams `int`
	*/
	virtual int getGramaj() const { return -1; };

	/**
	* Virtual getter for concentratie
	*
	* @return the concentration of the Sirop in % `double`
	*/
	virtual double getConcentratie() const { return -1; };

	/**
	* Virtual getter for valabilitate
	*
	* @return the number of months the Unguent expires `int`
	*/
	virtual int getValabilitate() const { return -1; };
};
