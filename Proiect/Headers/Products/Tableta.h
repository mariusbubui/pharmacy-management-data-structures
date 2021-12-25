#pragma once
#include "Medicament.h"

/**
* Abstract implemenatation of a Tableta
*
* It is a subclass of Medicament.
*/
class Tableta : public Medicament{
	int gramaj;

	/**
	 * Passes the data in a stream
	 * for a Tableta object.
	 *
	 * @return stream containing data
	 * of an Tableta `ostream&`
	 */
	ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Tableta with all
	* of its members and the superclass
	* members.
	*/
	Tableta(string den, string prod, int p, string subs, bool e, int g) : Medicament(den, prod, p, subs, e), gramaj{ g }{};
	
	/**
	 * Overloads the << operator
	 * for a Tableta object.
	 *
	 * @relatesalso Tableta
	 */
	friend ostream& operator<<(ostream&, const Tableta&);

	/**
	* Getter for gramaj
	*
	* @return the weight of the active
	* susbtance in grams `int`
	*/
	int getGramaj() const { return this->gramaj; };
};

